#version 330 core

out vec4 FragColor;

struct Material 
{
   // vec3 ambient;
    
    
    float shininess;
    float alpha;
   
}; 

uniform sampler2D diffuse;
uniform  sampler2D specular;  
uniform sampler2D alphaMask;

struct sLight
{
    vec3 position;			
	vec4 diffuse;	// Colour of the light (used for diffuse)
	vec4 specular;	// rgb = highlight colour, w = power
		
	vec3 direction;	// Spot, directional lights
	int lightType;	// x = lightType, y = inner angle, z = outer angle, w = TBD
	        
                   // 0 = pointlight
    float constant;
    float linear;
    float quadratic;	
    
    // 1 = spot light
					// 2 = directional light
    vec4 ambient;

     float cutOff;
    float outerCutOff;
    vec4 color;
    
};


in vec3 FragPosition;  
in vec3 Normal;  
in vec2 TextureCoordinates;
in vec4 meshColour;

uniform vec3 viewPos;
uniform Material material;
uniform bool isMasking;
uniform bool isCutout;

uniform int DIRECTION_LIGHT_ID =0;
uniform int POINT_LIGHT_ID =1;
uniform int SPOTLIGHT_ID =2;
const int LIGHTCOUNT = 15;
uniform sLight lights[LIGHTCOUNT];
float temp;

vec4 CalculateLight(vec3 norm, vec3 viewDir );
float near = 0.1; 
float far  = 100.0; 

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

uniform bool isDepthBuffer;
uniform samplerCube skybox;

void main()
{    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPosition);

    vec3 R = reflect(-viewDir, norm);

    vec4 result = CalculateLight(norm,viewDir);
  
     vec4 cutOff = texture(diffuse, TextureCoordinates);
 
     //float maskSample = texture(material.alphaMask, TextureCoordinates).r;

     //vec4 finalColor = vec4(result, isCutout ? 1.0f : maskSample);

     

    

      if (isCutout)
     {
      
         if (cutOff.a < 0.1)
        {
            discard;
        }
        FragColor = result*cutOff.a; 
     
     }
     

     if(isDepthBuffer)
     {

          float depth = LinearizeDepth(gl_FragCoord.z) / far;
          FragColor = vec4(vec3(depth), 1.0); 
      }
      else
      {
          //float depth = LinearizeDepth(gl_FragCoord.z) / far;
         // FragColor = vec4(result.xyz + vec3(depth * 0.75f) + texture(skybox, R).rgb *  0.75, 1.0);
          FragColor = result;
      }


     

    //FragColor = vec4( temp,temp, temp,1.0);
     
    

}

  


vec4 CalculateLight(vec3 norm, vec3 viewDir )
{

    vec4 result = vec4(0,0,0,0);
  

    for( int index = 0; index < LIGHTCOUNT; index++)
    {


       int LightType = lights[index].lightType;

       if(LightType == DIRECTION_LIGHT_ID)
       {
          vec3 lightDir = normalize(-lights[index].direction);
          float diff = max(dot(norm, lightDir), 0.0);
         vec3 reflectDir = reflect(-lightDir, norm);
         float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

         vec4 ambient = lights[index].ambient   *         meshColour * texture(diffuse, TextureCoordinates);
         vec4 diffuse = lights[index].diffuse   * diff  * meshColour * texture(diffuse, TextureCoordinates);
         vec4 specular = lights[index].specular * spec  * meshColour * texture(specular, TextureCoordinates);


//          vec3 ambient = lights[index].ambient * meshColour.rgb;
//         vec3 diffuse =  lights[index].diffuse * diff * meshColour.rgb;
//         vec3 specular =  lights[index].specular * spec *meshColour.rgb;

         vec4 finalValueforDir =(ambient+diffuse+specular);
         result+=finalValueforDir*lights[index].color;
        
       }
       if(LightType ==POINT_LIGHT_ID)
       {
        vec3 lightDir = normalize(lights[index].position - FragPosition);
        // diffuse shading
        float diff = max(dot(norm, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        // attenuation
        float distance = length(lights[index].position - FragPosition);
        float attenuation = 1.0 / (lights[index].constant + lights[index].linear * distance + lights[index].quadratic * (distance * distance));    
        // combine results
         vec4 ambient = lights[index].ambient   *         meshColour * texture(diffuse, TextureCoordinates);
         vec4 diffuse = lights[index].diffuse   * diff  * meshColour * texture(diffuse, TextureCoordinates);
         vec4 specular = lights[index].specular * spec  * meshColour * texture(specular, TextureCoordinates);

        
//          vec3 ambient = lights[index].ambient * meshColour.rgb;
//         vec3 diffuse =  lights[index].diffuse * diff * meshColour.rgb;
//         vec3 specular =  lights[index].specular * spec *meshColour.rgb;

        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;
         vec4 finalValueforDir= (ambient + diffuse + specular)*lights[index].color;
          result+=finalValueforDir;
       }

       if(LightType == SPOTLIGHT_ID)
       {
                vec3 lightDir = normalize(lights[index].position - FragPosition);
         // diffuse shading
         float diff = max(dot(norm, lightDir), 0.0);
         // specular shading
         vec3 reflectDir = reflect(-lightDir, norm);
         float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
         // attenuation
         float distance = length(lights[index].position - FragPosition);
         float attenuation = 1.0 / (lights[index].constant + lights[index].linear * distance + lights[index].quadratic * (distance * distance));    
         // spotlight intensity
         float theta = dot(lightDir, normalize(-lights[index].direction)); 
         float epsilon = lights[index].cutOff - lights[index].outerCutOff;
         float intensity = clamp((theta - lights[index].outerCutOff) / epsilon, 0.0, 1.0);
         // combine results
         vec4 ambient = lights[index].ambient   *         meshColour * texture(diffuse, TextureCoordinates);
         vec4 diffuse = lights[index].diffuse   * diff  * meshColour * texture(diffuse, TextureCoordinates);
         vec4 specular = lights[index].specular * spec  * meshColour * texture(specular, TextureCoordinates);

//
//                vec3 ambient = lights[index].ambient * meshColour.rgb;
//         vec3 diffuse =  lights[index].diffuse * diff * meshColour.rgb;
//         vec3 specular =  lights[index].specular * spec *meshColour.rgb;

         ambient *= attenuation * intensity;
         diffuse *= attenuation * intensity;
         specular *= attenuation * intensity;
         vec4 finalValueforDir= (ambient + diffuse + specular)*lights[index].color;
          result+=finalValueforDir;
       }

    }
     if (isMasking)
     {
    // temp = texture(alphaMask, TextureCoordinates).r;
       result.w = texture(alphaMask, TextureCoordinates).r;
     
     }
    
      return result;
}