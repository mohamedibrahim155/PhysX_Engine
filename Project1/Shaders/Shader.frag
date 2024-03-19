#version 330 core
out vec4 FragColor;

struct Material {
  
   
    sampler2D diffuse1;
    sampler2D specular1;    
   // sampler2D emission1;    
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emissive;
};

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoord;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;


   
void main()
{
   
     vec3 ambient = light.ambient * texture(material.diffuse1, TexCoord).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse1, TexCoord).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  

   // vec3 halfway = normalize(viewDir + lightDir);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular1, TexCoord).rgb;  

  //  vec3 emission = light.emissive * texture(material.emission1, TexCoord).rgb;
        
    vec3 result = ambient + diffuse + specular ;
    FragColor = vec4(result, 1.0);

   
   
} 


//#version 330 core
//out vec4 FragColor;
//
////in vec3 ourColor;
//in vec2 TexCoord;
//
//
//// texture samplers
//uniform sampler2D texture_diffuse1;
//
//
//in vec3 FragPos;	
//void main()
//{
//	FragColor = texture(texture_diffuse1, TexCoord);
//}