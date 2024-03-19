#version 330 core

in vec2 s_TexCoord;

uniform sampler2D diffuse;


uniform float Time;

out vec4 out_FragColor;

void main()
{
   
   out_FragColor = texture( diffuse, vec2(s_TexCoord.x + Time, s_TexCoord.y) );
}