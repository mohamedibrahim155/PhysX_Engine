#version 330 core

out vec4 FragColor;

struct Material 
{
   // vec3 ambient;
    
    vec4 baseColor;
	vec4 ambientColor;
	float specularValue;
    float shininess;
    float alpha;
   
}; 

uniform sampler2D diffuse_Texture;
uniform  sampler2D specular_Texture;  
uniform sampler2D opacity_Texture;

struct sLight
{
    vec3 position;			
	//vec4 diffuse;	// Colour of the light (used for diffuse)
	//vec4 specular;	// rgb = highlight colour, w = power
		
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

uniform int ShaderBlend;
uniform bool ObjectBlend;
uniform float alphaCutOffThreshold;

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
  
     vec4 cutOff = texture(diffuse_Texture, TextureCoordinates);
 
     //float maskSample = texture(material.alphaMask, TextureCoordinates).r;

     //vec4 finalColor = vec4(result, isCutout ? 1.0f : maskSample);

     

     if(ShaderBlend ==1)
     {
       result.w = 1.0;
     }
     else if(ShaderBlend == 3)
     {
        if(result.w <alphaCutOffThreshold)
        {
         discard;
        }
     }
    

//      if (isCutout)
//     {
//      
//         if (cutOff.a < 0.1)
//        {
//            discard;
//        }
//        FragColor = result*cutOff.a; 
//     
//     }
     

     if(isDepthBuffer)
     {

          float depth = LinearizeDepth(gl_FragCoord.z) / far;
          FragColor = vec4(vec3(depth), 1.0); 
      }
      else
      {
          //float depth = LinearizeDepth(gl_FragCoord.z) / far;
        //  FragColor = texture(specular_Texture, TextureCoordinates);
          FragColor = result;
      }


     

    //FragColor = vec4( temp,temp, temp,1.0);
     
    

}

  


vec4 CalculateLight(vec3 norm, vec3 viewDir )
{

    vec4 result = vec4(0,0,0,0);
  
    vec4 diffuseColor = texture(diffuse_Texture, TextureCoordinates);

    vec4 textureColor = diffuseColor * meshColour * material.baseColor;

    for( int index = 0; index < LIGHTCOUNT; index++)
    {


       int LightType = lights[index].lightType;

       vec4 ambientColor = lights[index].ambient * material.ambientColor;
		ambientColor *= textureColor;

       if(LightType == DIRECTION_LIGHT_ID)
       {
          vec3 lightDir = normalize(-lights[index].direction);
          float diff = max(dot(norm, lightDir), 0.0);


          vec4 diffuse = diff * lights[index].color;
	       diffuse *= textureColor;

           vec4 specularColor = texture(specular_Texture, TextureCoordinates);
           vec3 reflectDir = reflect(-lightDir, norm);


         float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);

        	vec4 specular = vec4(spec * material.specularValue * lights[index].color.rgb * (specularColor.r),lights[index].color.w);



         //vec4 ambient = lights[index].ambient   *         meshColour * texture(diffuse, TextureCoordinates);
        // vec4 diffuse = lights[index].diffuse   * diff  * meshColour * texture(diffuse, TextureCoordinates);
        // vec4 specular = lights[index].specular * spec  * meshColour * texture(specular, TextureCoordinates);


//          vec3 ambient = lights[index].ambient * meshColour.rgb;
//         vec3 diffuse =  lights[index].diffuse * diff * meshColour.rgb;
//         vec3 specular =  lights[index].specular * spec *meshColour.rgb;

         vec4 finalValueforDir =(ambientColor+diffuse+specular);
         //vec4 finalValueforDir = material.baseColor;

        // result+=finalValueforDir*lights[index].color;
         result += finalValueforDir;
        
       }
       if(LightType ==POINT_LIGHT_ID)
       {
     
        // attenuation
        float distance = length(lights[index].position - FragPosition);
        float attenuation = 1.0 / (lights[index].constant + lights[index].linear * distance + lights[index].quadratic * (distance * distance));    
        // combine results
        	ambientColor.xyz *= attenuation;


           vec3 lightDir = normalize(lights[index].position - FragPosition);
        // diffuse shading
        float diff = max(dot(norm, lightDir), 0.0);
        vec4 diffuse = diff * lights[index].color;
        diffuse *= textureColor * attenuation;

        vec4 specularColor = texture(specular_Texture, TextureCoordinates);
        vec3 reflectDir = reflect(-lightDir, norm);

        // specular shading
        
        float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
        vec4 specular = spec * material.specularValue * lights[index].color * (specularColor.r);
         
         
         //vec4 ambient = lights[index].ambient   *         meshColour * texture(diffuse, TextureCoordinates);
        // vec4 diffuse = lights[index].diffuse   * diff  * meshColour * texture(diffuse, TextureCoordinates);
        // vec4 specular = lights[index].specular * spec  * meshColour * texture(specular, TextureCoordinates);

        
//          vec3 ambient = lights[index].ambient * meshColour.rgb;
//         vec3 diffuse =  lights[index].diffuse * diff * meshColour.rgb;
//         vec3 specular =  lights[index].specular * spec *meshColour.rgb;

       // ambient *= attenuation;
       // diffuse *= attenuation;
       // specular *= attenuation;


        // vec4 finalValueforDir= (ambient + diffuse + specular)*lights[index].color;
         vec4 finalValueforDir= (ambientColor + diffuse + specular);

          result += finalValueforDir;
       }

       if(LightType == SPOTLIGHT_ID)
       {
          vec3 lightDir = normalize(lights[index].position - FragPosition);

         float distance1 = length(lights[index].position - FragPosition);
         float attenuation = 1.0 / (lights[index].constant + lights[index].linear * distance1 + lights[index].quadratic * (distance1 * distance1));    
        

         
        
         // attenuation
         // spotlight intensity
         float theta = dot(lightDir, normalize(-lights[index].direction)); 
         float epsilon = lights[index].cutOff - lights[index].outerCutOff;
         float intensity = clamp((theta - lights[index].outerCutOff) / epsilon, 0.0, 1.0);
         
         	ambientColor *= attenuation * intensity;

             // diffuse shading
            float diff = max(dot(norm, lightDir), 0.0);
            vec4 diffuse = diff * lights[index].color;
            diffuse *= textureColor * attenuation * intensity;

             // specular shading
         vec4 specularColor = texture(specular_Texture, TextureCoordinates);
         vec3 reflectDir = reflect(-lightDir, norm);

         float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
         vec4 specular = spec * material.specularValue * lights[index].color * (specularColor.r);
         	specular *= attenuation * intensity;

         // combine results
         //vec4 ambient = lights[index].ambient   *         meshColour * texture(diffuse, TextureCoordinates);
        // vec4 diffuse = lights[index].diffuse   * diff  * meshColour * texture(diffuse, TextureCoordinates);
         //vec4 specular = lights[index].specular * spec  * meshColour * texture(specular, TextureCoordinates);

//
//                vec3 ambient = lights[index].ambient * meshColour.rgb;
//         vec3 diffuse =  lights[index].diffuse * diff * meshColour.rgb;
//         vec3 specular =  lights[index].specular * spec *meshColour.rgb;

//         ambient *= attenuation * intensity;
//         diffuse *= attenuation * intensity;
//         specular *= attenuation * intensity;



         //vec4 finalValueforDir= (ambient + diffuse + specular)*lights[index].color;
        
        
        vec4 finalValueforDir = (ambientColor + diffuse + specular);

          result += finalValueforDir;
       }

    }
     if (ObjectBlend)
     {
    // temp = texture(alphaMask, TextureCoordinates).r;
       result.w = texture(opacity_Texture, TextureCoordinates).r;
     
     }
     else
     {
        result.w =  material.baseColor.w;
     }
    
      return result;
}