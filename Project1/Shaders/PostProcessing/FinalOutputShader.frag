#version 330 core
in vec2 uv;
out vec4 FragColor;

uniform sampler2D sceneTexture;
uniform sampler2D effectTexture;

float mixfactor =1;
void main()
{

    vec2 uv2 = uv;
    vec3 scenecolor =  texture(sceneTexture, uv2).rgb;
    vec3 effectColor =  texture(effectTexture, uv2).rgb;

	//vec3 result = (scenecolor) + (effectColor);

	vec3 result = mix(scenecolor, effectColor, mixfactor);
	
    FragColor = vec4(result,1);
}