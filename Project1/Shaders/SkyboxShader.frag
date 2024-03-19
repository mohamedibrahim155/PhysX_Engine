#version 330 core
out vec4 FragColor;

in vec3 s_TexCoords;

uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, s_TexCoords);
}