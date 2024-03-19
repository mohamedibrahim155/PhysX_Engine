#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 aColor;
layout (location = 4) in vec4 aBoneID;
layout (location = 5) in vec4 aBoneWeight;

const int MAX_BONES = 200;

 out vec3 FragPosition;
 out vec3 Normal;
 out vec2 TextureCoordinates;
 out vec4 meshColour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform bool isBones;
uniform mat4 BoneMatrices[MAX_BONES];

// function prototypes

void main()
{
   

  //  FragPosition = vec3(model * vec4(aPos, 1.0));
    FragPosition = aPos;

	vec4 totalPosition = vec4(FragPosition,1);
    if (isBones)
	{
		//ex_BoneId = in_BoneIds;
		mat4 boneTransform = BoneMatrices[int(aBoneID[0])] * aBoneWeight[0];
		boneTransform += BoneMatrices[int(aBoneID[1])] * aBoneWeight[1];
		boneTransform += BoneMatrices[int(aBoneID[2])] * aBoneWeight[2];
		boneTransform += BoneMatrices[int(aBoneID[3])] * aBoneWeight[3];

		totalPosition = boneTransform * vec4(FragPosition,1.0f);
	}
    Normal =  mat3(transpose(inverse(model))) * aNormal;
	
	
	  TextureCoordinates = aTexCoords;
	
	 meshColour = aColor;
	//gl_Position = projection * view * model;
		gl_Position = projection * view * model * totalPosition;
}



