#include "SkinnedMeshRenderer.h"
#include "GraphicsRender.h"


SkinnedMeshRenderer::SkinnedMeshRenderer(std::string const& path, bool isLoadTexture, bool isDebugModel)
{
    this->isLoadTexture = isLoadTexture;
    this->LoadModel(path, this->isLoadTexture, isDebugModel);
}
std::shared_ptr<Mesh> SkinnedMeshRenderer::ProcessMesh(aiMesh* mesh, const aiScene* scene)

{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*> textures;

    std::vector<BoneWeightInfo> boneWeightInfos;


    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;



        // normals
        if (mesh->HasNormals())
        {

            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;


        }
        else
        {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        }

        if (mesh->HasVertexColors(0))
        {
            aiColor4D color = mesh->mColors[0][i];
            vertex.vRgb = glm::vec4(color.r, color.g, color.b, color.a);
        }
        else
        {
            vertex.vRgb = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        }

       // vertex.BoneID = glm::vec4(0);
       // vertex.BoneWeight = glm::vec4(0.0f);

        SetDefaultVertexBoneData(vertex);


        vertices.push_back(vertex);
    }


    unsigned int vertArrayIndex = 0;

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    if (scene->mNumAnimations > 0)
    {

        aiAnimation* animation = scene->mAnimations[0];

        std::string animation_name = animation->mName.C_Str();
        double animation_Duration = animation->mDuration;
        double tickesPerSecond = animation->mTicksPerSecond;

        for (int i = 0; i < animation->mNumChannels; i++)
        {
            aiNodeAnim* assimpNodeAnim = animation->mChannels[i];

            for (int i = 0; i < assimpNodeAnim->mNumPositionKeys; i++)
            {
                aiVectorKey& p = assimpNodeAnim->mPositionKeys[i];
            }

            for (int i = 0; i < assimpNodeAnim->mNumScalingKeys; ++i)
            {
                aiVectorKey& s = assimpNodeAnim->mScalingKeys[i];
            }

            for (int i = 0; i < assimpNodeAnim->mNumRotationKeys; ++i)
            {
                aiQuatKey& q = assimpNodeAnim->mRotationKeys[i];
            }
        }

    }


    ExtractBoneWeightForVertices(vertices, mesh, scene);


    aiColor4D baseColor(1.0f, 1.0f, 1.0f, 1.0f);

    BaseMaterial* baseMeshMaterial = new Material();

    if (mesh->mMaterialIndex >= 0)
    {
        if (isLoadTexture)
        {
            // baseMeshMaterial = new Material();
            aiMaterial* m_aiMaterial = scene->mMaterials[mesh->mMaterialIndex];

            baseMeshMaterial->material()->diffuseTexture = LoadMaterialTexture(m_aiMaterial, aiTextureType_DIFFUSE, "diffuse_Texture");
            baseMeshMaterial->material()->specularTexture = LoadMaterialTexture(m_aiMaterial, aiTextureType_SPECULAR, "specular_Texture");
            baseMeshMaterial->material()->alphaTexture = LoadMaterialTexture(m_aiMaterial, aiTextureType_OPACITY, "opacity_Texture");

            Texture* materialTexture = (Texture*)baseMeshMaterial->material()->alphaTexture;

            if (materialTexture->path != alphaTextureDefaultPath)
            {
                baseMeshMaterial->material()->useMaskTexture = true;
            }

            baseMeshMaterial->material()->SetBaseColor(glm::vec4(baseColor.r, baseColor.g, baseColor.b, baseColor.a));
        }
        else
        {

            baseMeshMaterial = new UnLitMaterial();
            baseMeshMaterial->unLitMaterial()->SetBaseColor(glm::vec4(baseColor.r, baseColor.g, baseColor.b, baseColor.a));
        }
    }
    else
    {
        baseMeshMaterial = new UnLitMaterial();
        baseMeshMaterial->unLitMaterial()->SetBaseColor(glm::vec4(baseColor.r, baseColor.g, baseColor.b, baseColor.a));
    }



    return std::make_shared<Mesh>(vertices, indices, baseMeshMaterial);
}

BoneNode* SkinnedMeshRenderer::GenerateBoneHierarchy(aiNode* ainode, const int depth)
{
    BoneNode* node = CreateNode(ainode);
    aiMatrix4x4& transformation = ainode->mTransformation;
    aiVector3D position;
    aiQuaternion rotation;
    aiVector3D scaling;
    transformation.Decompose(scaling, rotation, position);

    glm::mat4 glmMatrix;
    AssimpToGLM(transformation, glmMatrix);

    boneNodeMap[node->name] = node;

    for (int i = 0; i < ainode->mNumChildren; ++i)
    {
        node->children.emplace_back(GenerateBoneHierarchy(ainode->mChildren[i], depth + 1));
    }
    return node;


}

BoneNode* SkinnedMeshRenderer::CreateNode(aiNode* node)
{
    BoneNode* newNode = new BoneNode(node->mName.C_Str());
    AssimpToGLM(node->mTransformation, newNode->transformation);
    return newNode;
}

void SkinnedMeshRenderer::LoadModel(std::string const& path, bool isLoadTexture, bool isDebugModel)
{
	this->isLoadTexture = isLoadTexture;
	this->modelPath = path;

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);


	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);

    rootBoneNode = GenerateBoneHierarchy(scene->mRootNode);

    //globalInverseTransformedMatrix = glm::inverse(rootBoneNode->transformation);

	std::cout << " Loaded  Model file  : " << directory << " Mesh count : " << scene->mNumMeshes << std::endl;

	SetModelName();

	if (isDebugModel) return;
	InitializeEntity(this);
}

void SkinnedMeshRenderer::ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene)
{

    for (int boneIndex = 0; boneIndex < mesh->mNumBones; boneIndex++)
    {
        int boneID = -1;

        std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();

        if (boneInfoMap.find(boneName) == boneInfoMap.end())
        {
            BoneInfo newBoneInfo;
            newBoneInfo.id = boneCount;
           
            AssimpToGLM(mesh->mBones[boneIndex]->mOffsetMatrix, newBoneInfo.boneOffset);
            listOfBoneInfo.emplace_back(newBoneInfo);
            boneInfoMap[boneName] = newBoneInfo;

            boneID = boneCount;
            boneCount++;
        }
        else
        {
            boneID = boneInfoMap[boneName].id;
        }

        assert(boneID != -1);

        aiVertexWeight* weights = mesh->mBones[boneIndex]->mWeights;
        int numWeights = mesh->mBones[boneIndex]->mNumWeights;

        for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
        {
            int vertexId = weights[weightIndex].mVertexId;
            float weight = weights[weightIndex].mWeight;
            assert(vertexId <= vertices.size());
            SetVertexBoneData(vertices[vertexId], boneID, weight);
        }

    }

}

void SkinnedMeshRenderer::SetVertexBoneData(Vertex& vertex, int boneID, float weight)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
    {
        if (vertex.BoneID[i] < 0)
        {
            vertex.BoneWeight[i] = weight;
            vertex.BoneID[i] = boneID;
            break;
        }
    }
}

void SkinnedMeshRenderer::UpdateMeshRendererBones()
{
    glm::mat4 rootTransformation = glm::mat4(1.0f);

    CalculateMatrices( rootBoneNode, rootTransformation);
}

void SkinnedMeshRenderer::CalculateMatrices( BoneNode* node, const glm::mat4& parentTransformationMatrix)
{
    std::string nodeName(node->name);

    glm::mat4 transformationMatrix = node->transformation;

    glm::mat4 globalTransformation = parentTransformationMatrix * transformationMatrix;


    std::map<std::string, BoneInfo> ::iterator boneMapIt  = boneInfoMap.find(nodeName);
    if (boneMapIt != boneInfoMap.end())
    {
        BoneInfo& boneInfo = listOfBoneInfo[boneMapIt->second.id];
        boneInfo.finalTransformation = /*model->globalInverseTransformedMatrix **/ globalTransformation * boneInfo.boneOffset;
        boneInfo.globalTransformation = globalTransformation;
    }

    for (int i = 0; i < node->children.size(); i++)
    {
        CalculateMatrices(node->children[i], globalTransformation);
    }

}

void SkinnedMeshRenderer::SetDefaultVertexBoneData(Vertex& vertex)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
    {
        vertex.BoneID[i] = -1;
        vertex.BoneWeight[i] = 0.0f;
    }
}



void SkinnedMeshRenderer::DrawProperties()
{
    Model::DrawProperties();
}

void SkinnedMeshRenderer::SceneDraw()
{
	Model::SceneDraw();
}

void SkinnedMeshRenderer::Start()
{
}

void SkinnedMeshRenderer::Update(float deltaTime)
{
}

void SkinnedMeshRenderer::Render()
{
}

void SkinnedMeshRenderer::OnDestroy()
{
}

void SkinnedMeshRenderer::Draw(Shader* shader)
{

    UpdateMeshRendererBones();


    if (!isVisible)
    {
        return;
    }
    shader->Bind();
    if (shader->modelUniform)
    {
        shader->setMat4("model", transform.GetModelMatrix());
        shader->Bind();

        shader->setBool("isBones", true);

        std::string boneMatrixUniform;

        for (int i = 0; i < listOfBoneInfo.size(); i++)
        {
            boneMatrixUniform = "BoneMatrices[" + std::to_string(i) + "]";
            shader->setMat4(boneMatrixUniform, listOfBoneInfo[i].finalTransformation);
        }

    }



    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i]->Draw(shader);
    }
}


void SkinnedMeshRenderer::LoadAnimation(const std::string& animationPath, const std::string& animationName)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (scene->HasAnimations())
    {
        int animationCount = scene->mNumAnimations;
        aiAnimation* animation = scene->mAnimations[0];

        SkeletonAnim* skeletalanimation = new SkeletonAnim();
        skeletalanimation->Name = animation->mName.C_Str();
        skeletalanimation->Duration = animation->mDuration;

        for (int i = 0; i < animation->mNumChannels; i++)
        {
            aiNodeAnim* animNode = animation->mChannels[i];

            NodeAnim* anim = new NodeAnim(animation->mChannels[i]->mNodeName.C_Str(), animNode);

            skeletalanimation->Channels.push_back(anim);

        }

        listOfAnimation[animationName] = skeletalanimation;

        currentAnimation = skeletalanimation;
    }

}

void SkinnedMeshRenderer::UpdateSkeletonAnimation(float deltaTime)
{

    std::string name = currentAnimation->Name;
    for (NodeAnim* nodeAnimation : currentAnimation->Channels)
    {
        std::string nodeName = nodeAnimation->Name;

        std::map<std::string, BoneNode*> ::iterator boneNode = boneNodeMap.find(nodeName);
        std::map<std::string, BoneInfo> ::iterator boneInfoNode = boneInfoMap.find(nodeName);

        if (boneInfoNode == boneInfoMap.end()) continue;

        if (boneNode == boneNodeMap.end()) continue;


        if (boneNode != boneNodeMap.end())
        {
            glm::mat4& transformedMatrix = boneNode->second->transformation;

            UpdateAnimationFrame(nodeAnimation, transformedMatrix, timeStep);
        }
    }
  
    
}

void SkinnedMeshRenderer::UpdateAnimationFrame(NodeAnim* anim, glm::mat4& nodeTransform, double time)
{
    glm::vec3 translation = UpdateTranslation(anim->listOfPositionKeyFrames, time);
    glm::quat rotation = UpdateRotation(anim->listOfRotationKeyframes, time);
        glm::vec3 scale = UpdateScale(anim->listOfScaleKeyFrames, time);

        nodeTransform = glm::translate(glm::mat4(1),translation)
            * glm::toMat4(rotation)
            * glm::scale(glm::mat4(1.0f), scale);

}

glm::vec3 SkinnedMeshRenderer::UpdateTranslation(std::vector<PositionKeyFrame>& listOfKeyFrames, float time)
{
    //glm
    if (listOfKeyFrames.size() == 1)
    {
        /// returns firstFrame;

        return listOfKeyFrames[0].position;

      //  nodeTransform = nodeTransform * translation;
    }
    else if (listOfKeyFrames.size() > 1)
    {
        int keyFrameEndIndex = 0;

        for (; keyFrameEndIndex < listOfKeyFrames.size(); keyFrameEndIndex++)
        {
            if (listOfKeyFrames[keyFrameEndIndex].time > time)
            {
                break;

            }
        }


        if (keyFrameEndIndex >= listOfKeyFrames.size())
        {

            // entity->transform.position = anim->listOfPositionKeyFrames[keyFrameEndIndex - 1].position;
            return listOfKeyFrames[keyFrameEndIndex - 1].position;

        }


        int keyFrameStartIndex = keyFrameEndIndex - 1;

        PositionKeyFrame startKeyFrame = listOfKeyFrames[keyFrameStartIndex];
        PositionKeyFrame endKeyFrame = listOfKeyFrames[keyFrameEndIndex];

        float percent = (time - startKeyFrame.time) / (endKeyFrame.time - startKeyFrame.time);
        float result = 0.0f;
        switch (endKeyFrame.easeType)
        {
        case EasingType::Linear:
            result = percent;
            break;

        case EasingType::sineEaseIn:
            result = glm::sineEaseIn(percent);
            break;

        case EasingType::sineEaseOut:
            result = glm::sineEaseOut(percent);
            break;

        case EasingType::sineEaseInOut:
            result = glm::sineEaseInOut(percent);
            break;
        }

        glm::vec3 delta = (endKeyFrame.position - startKeyFrame.position);

        //  entity->transform.SetPosition(startKeyFrame.position + delta * result);

        glm::vec3 endValue = startKeyFrame.position + delta * result;

       return endValue;

    }

}

glm::quat SkinnedMeshRenderer::UpdateRotation(std::vector<RotationKeyFrame>& listOfKeyFrames, float time)
{
    if (listOfKeyFrames.size() == 1)
    {
        /// returns firstFrame;

        glm::quat quaternionRotation = glm::quat(glm::radians(listOfKeyFrames[0].rotation_vec3));

        return  quaternionRotation;

     

    }
    else if (listOfKeyFrames.size() > 1)
    {
        int keyFrameEndIndex = 0;

        for (; keyFrameEndIndex < listOfKeyFrames.size(); keyFrameEndIndex++)
        {
            if (listOfKeyFrames[keyFrameEndIndex].time > time)
            {
                break;

            }
        }


        if (keyFrameEndIndex >= listOfKeyFrames.size())
        {

            glm::quat quaternionRotation = glm::quat(glm::radians(listOfKeyFrames[keyFrameEndIndex - 1].rotation_vec3));

            return  quaternionRotation;


        }


        int keyFrameStartIndex = keyFrameEndIndex - 1;

        RotationKeyFrame startKeyFrame = listOfKeyFrames[keyFrameStartIndex];
        RotationKeyFrame endKeyFrame = listOfKeyFrames[keyFrameEndIndex];

        float percent = (time - startKeyFrame.time) / (endKeyFrame.time - startKeyFrame.time);
        float result = 0.0f;

        switch (endKeyFrame.easeType)
        {
        case EasingType::Linear:
            result = percent;
            break;

        case EasingType::sineEaseIn:
            result = glm::sineEaseIn(percent);
            break;

        case EasingType::sineEaseOut:
            result = glm::sineEaseOut(percent);
            break;

        case EasingType::sineEaseInOut:
            result = glm::sineEaseInOut(percent);
            break;
        }

        glm::quat startRotation = glm::quat(glm::radians(startKeyFrame.rotation_vec3));
        glm::quat endRotation = glm::quat(glm::radians(endKeyFrame.rotation_vec3));

        glm::quat quaternionRotation = glm::slerp(startRotation, endRotation, result);


        return  quaternionRotation;



    }
}

glm::vec3 SkinnedMeshRenderer::UpdateScale(std::vector<ScaleKeyFrame>& listOfKeyFrames, float time)
{

    if (listOfKeyFrames.size() == 1)
    {

        // entity->transform.SetScale(animation->scaleKeyFrameList[0].scale);

        return listOfKeyFrames[0].scale;
      

    }
    else if (listOfKeyFrames.size() > 1)
    {
        int keyFrameEndIndex = 0;

        for (; keyFrameEndIndex < listOfKeyFrames.size(); keyFrameEndIndex++)
        {
            if (listOfKeyFrames[keyFrameEndIndex].time > time)
            {
                break;

            }
        }

        if (keyFrameEndIndex >= listOfKeyFrames.size())
        {
            return  listOfKeyFrames[keyFrameEndIndex - 1].scale;
        }
        int keyFrameStartIndex = keyFrameEndIndex - 1;

        ScaleKeyFrame startKeyFrame = listOfKeyFrames[keyFrameStartIndex];
        ScaleKeyFrame endKeyFrame = listOfKeyFrames[keyFrameEndIndex];

        float percent = (time - startKeyFrame.time) / (endKeyFrame.time - startKeyFrame.time);
        float result = 0.0f;


        switch (endKeyFrame.easeType)
        {
        case EasingType::Linear:
            result = percent;
            break;

        case EasingType::sineEaseIn:
            result = glm::sineEaseIn(percent);
            break;

        case EasingType::sineEaseOut:
            result = glm::sineEaseOut(percent);
            break;

        case EasingType::sineEaseInOut:
            result = glm::sineEaseInOut(percent);
            break;
        }

        glm::vec3 delta = (endKeyFrame.scale - startKeyFrame.scale);

        glm::vec3  endValue = startKeyFrame.scale + delta * result;

        return endValue;

    }

}

const SkeletonAnim* SkinnedMeshRenderer::GetCurrentAnimation()
{
    return currentAnimation;
}

const SkeletonAnim* SkinnedMeshRenderer::GetAnimation(const std::string& AnimationName)
{
    return listOfAnimation[AnimationName];
}

void SkinnedMeshRenderer::PlayAnimation(const std::string& animationName)
{
    timeStep = 0;

    currentAnimation = listOfAnimation[animationName];
}
