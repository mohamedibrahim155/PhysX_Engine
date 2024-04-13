#pragma once

#include "../Animation/Bone/Bone.h"
#include "PhysXObject.h"
#include <unordered_map>
class PhysicsSkinMeshRenderer : public PhysXObject
{
public:

    PhysicsSkinMeshRenderer() {};

    virtual ~PhysicsSkinMeshRenderer() {}
    void LoadModel(std::string const& path, bool isLoadTexture = true, bool isDebugModel = false) override;
    virtual void DrawProperties() override;
    virtual void SceneDraw() override;

    virtual void Start() override;
    virtual void Update(float deltaTime) override ;
    virtual void Render() override;
    virtual void OnDestroy() override;
    virtual std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene) override;

    virtual void OnTriggerEnter(PhysXObject* otherObject) override;
    virtual void OnTriggerStay(PhysXObject* otherObject) override;
    virtual void OnTriggerExit(PhysXObject* otherObject) override;

    virtual void OnCollisionEnter(PhysXObject* otherObject, CollisionInfo& collisionInfo) override;
    virtual void OnCollisionStay(PhysXObject* otherObject) override;
    virtual void OnCollisionExit(PhysXObject* otherObject) override;

    void Draw(Shader* shader) override;

    void LoadAnimation(const std::string& animationPath, const std::string& animationName, bool isAnimationLoop = true);
    void UpdateSkeletonAnimation(float timeFrame);
    void UpdateAnimationFrame(NodeAnim* anim, glm::mat4& nodeTransform, double time);
    void PlayAnimation(const std::string& animationName);
    void PlayBlendAnimation(const std::string& animationName, float blendTime);
    int& GetBoneCount() { return boneCount; }
    std::map<std::string, BoneInfo>& GetBoneMap() { return boneInfoMap; }

    BoneNode* GenerateBoneHierarchy(aiNode* ainode, const int depth = 0);
    BoneNode* CreateNode(aiNode* node);

    glm::vec3 UpdateTranslation(std::vector<PositionKeyFrame>& listOfKeyFrames, float time);
    glm::quat UpdateRotation(std::vector<RotationKeyFrame>& listOfKeyFrames, float time);
    glm::vec3 UpdateScale(std::vector<ScaleKeyFrame>& listOfKeyFrames, float time);

    const SkeletonAnim* GetCurrentAnimation();
    const SkeletonAnim* GetAnimation(const std::string& AnimationName);



    float currentTimeStep;
    float previousTimeStep;
    float currentBlendTime;
    float blendDuration;
    float frameSpeed = 40.0f;
   

    bool isPlayAnimation = true;
    bool isBlending = false;

private:

    void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);
    void SetVertexBoneData(Vertex& vertex, int boneID, float weight);
    void UpdateMeshRendererBones();
    void CalculateMatrices(BoneNode* boneNode, const glm::mat4& parentTransformationMatrix);
    void SetDefaultVertexBoneData(Vertex& vertex);

    int boneCount = 0;
    int currentAnimationIndex = 0;
    
    float controlTime;
    float columnWidth = 200;

    bool enableAnimationControl = false;

    std::map<std::string, BoneInfo> boneInfoMap;
    std::map<std::string, BoneNode*> boneNodeMap;
    std::vector<BoneInfo> listOfBoneInfo;
    std::map<std::string, int> boneIDMap;
    std::unordered_map<std::string, SkeletonAnim*> listOfAnimation;

    glm::mat4 GlobalInverseTransformation;
    glm::mat4 globalInverseTransformedMatrix;
    BoneNode* rootBoneNode;
    SkeletonAnim* currentAnimation;
    SkeletonAnim* previousAnimation;
};

