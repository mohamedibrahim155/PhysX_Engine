#pragma once
#include "model.h"
#include "Animation/Bone/Bone.h"
#include <unordered_map>
class SkinnedMeshRenderer : public Model
{
public:

    SkinnedMeshRenderer() {};
    SkinnedMeshRenderer(std::string const& path, bool isLoadTexture = true, bool isDebugModel = false);
    virtual ~SkinnedMeshRenderer() {}
    void LoadModel(std::string const& path, bool isLoadTexture = true, bool isDebugModel = false) override;
    virtual void DrawProperties() override;
    virtual void SceneDraw() override;

    virtual void Start() override;
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void OnDestroy() override;
    virtual std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene) override;

     void Draw(Shader* shader) override;

     void LoadAnimation(const std::string& animationPath, const std::string& animationName);
     void UpdateSkeletonAnimation(float deltaTime);
     void UpdateAnimationFrame(NodeAnim* anim , glm::mat4& nodeTransform, double time);
     void PlayAnimation(const std::string& animationName);

     int& GetBoneCount() { return boneCount; }
     std::map<std::string, BoneInfo>& GetBoneMap() { return boneInfoMap; }

     BoneNode* GenerateBoneHierarchy(aiNode* ainode, const int depth = 0);
     BoneNode* CreateNode(aiNode* node);

     glm::vec3 UpdateTranslation(std::vector<PositionKeyFrame>& listOfKeyFrames, float time);
     glm::quat UpdateRotation(std::vector<RotationKeyFrame>& listOfKeyFrames, float time);
     glm::vec3 UpdateScale(std::vector<ScaleKeyFrame>& listOfKeyFrames, float time);

     const SkeletonAnim* GetCurrentAnimation();
     const SkeletonAnim* GetAnimation(const std::string& AnimationName);

     float timeStep;

   private:

       void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);
       void SetVertexBoneData(Vertex& vertex, int boneID, float weight);
       void UpdateMeshRendererBones();
       void CalculateMatrices(BoneNode* boneNode, const glm::mat4& parentTransformationMatrix);
       void SetDefaultVertexBoneData(Vertex& vertex);

       int boneCount = 0;
       int currentAnimationIndex = 0;

       std::map<std::string, BoneInfo> boneInfoMap;
       std::map<std::string, BoneNode*> boneNodeMap;
       std::vector<BoneInfo> listOfBoneInfo;
       std::map<std::string, int> boneIDMap;
       std::unordered_map<std::string, SkeletonAnim*> listOfAnimation;

       glm::mat4 GlobalInverseTransformation;
       glm::mat4 globalInverseTransformedMatrix;
       BoneNode* rootBoneNode;
       SkeletonAnim* currentAnimation;
};

