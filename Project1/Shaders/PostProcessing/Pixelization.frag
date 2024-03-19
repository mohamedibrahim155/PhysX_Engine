
#version 330 core

const int 	fps 	= 15;
const float delta 	= 1.0f / float(fps);

in vec2 uv;
out vec4 FragColor;

uniform sampler2D sceneTexture;
//uniform float aberration;
uniform float time;

float Random(float t)
{
    return fract(
        sin(
            dot(vec2(t, t), vec2(12.9898, 78.233))
    	)* 43758.5453123
    );
}

float getTickedTime() 
{
    float iTime 	= time;
    float garbage = mod(iTime, delta); 
    return iTime - garbage;
}

void main() 
{
  
  vec2 uv1 = uv;
    float glitchStep = mix(4.0f, 32.0f, Random(getTickedTime()));

    vec4 screenColor = texture(sceneTexture, uv1);
    
    uv1.x = round(uv1.x * glitchStep ) / glitchStep;
    vec4 glitchColor = texture(sceneTexture, uv1);
    
    FragColor = mix(screenColor, glitchColor, vec4(0.3f));
}