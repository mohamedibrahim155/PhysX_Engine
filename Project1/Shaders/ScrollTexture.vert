
#version 330 core
in vec4 in_Vertex;
in vec4 in_TexCoord;

uniform mat4 model;
uniform mat4 ProjectionMatrix;
uniform mat4 view;

out vec2 s_TexCoord;

void main()
{
     gl_Position = ProjectionMatrix * view * model * in_Vertex;

     s_TexCoord = vec2( in_TexCoord );
}