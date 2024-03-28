#include "CapsuleCollider.h"
#include "../PhysXEngine.h"
#include"../PhysXUtils.h"
#include "../../GraphicsRender.h"

CapsuleCollider::CapsuleCollider()
{
    physics = PhysXEngine::GetInstance().GetPhysics();

}

void CapsuleCollider::ConstructCollider()
{
    shapeType = ColliderShape::CAPSULE;

    if (physicsMaterial == nullptr)
    {
        physicsMaterial = PhysXEngine::GetInstance().GetPxPhysicsMaterial();
    }

    capsuleShape = physics->createShape(
        createCapsuleGeomentryFromAABB(modelAABB),
        *physicsMaterial);

    capsuleShape->setLocalPose(this->GetLocalShapeTransfom());
}

void CapsuleCollider::Render()
{
    if (physicsObject == nullptr)  return;

    PxBounds3 boxAABB = modelAABB;

    boxAABB.minimum += GLMToPxVec3(GetPosition());
    boxAABB.maximum += GLMToPxVec3(GetPosition());

  

    glm::vec3 upSphere = (modelTransform->position + offsetPosition +localShapePosition) + modelTransform->GetUp() * halfHeight;
    glm::vec3 downSphere = (modelTransform->position + offsetPosition + localShapePosition) - modelTransform->GetUp() * halfHeight;

    //Sphere 1
    GraphicsRender::GetInstance().DrawSphere(
        upSphere,
        radius,
        glm::vec4(0, 0.5f, 0, 1),
        true);

    //Sphere 2
    GraphicsRender::GetInstance().DrawSphere(
       downSphere,
        radius,
        glm::vec4(0, 0.5f, 0, 1),
        true);

}

void CapsuleCollider::InitializeCollider(PhysXObject* object)
{
    BaseCollider::InitializeCollider(object);

    ConstructCollider();
}

void CapsuleCollider::SetPhysicsMaterial(PhysicsMaterial& material)
{
    physicsMaterial = physics->createMaterial(material.staticFriction,
        material.dynamicFriction, material.bounciness);

    physicsMaterial->setFrictionCombineMode(PxCombineToLocal(material.frictionCombine));
    physicsMaterial->setRestitutionCombineMode(PxCombineToLocal(material.bounceCombine));

    PxMaterial* materials[] = { physicsMaterial };

    capsuleShape->setMaterials(materials, 1);
}

void CapsuleCollider::SetRadius(float radius)
{
    this->radius = radius;

    SetCapsuleShape(radius, halfHeight);
}

void CapsuleCollider::SetHalfLength(float halfLength)
{
    this->halfHeight = halfLength;

    SetCapsuleShape(radius, halfHeight);
}



PxShape* CapsuleCollider::GetShape()
{
    return capsuleShape;
}

PxTransform CapsuleCollider::GetLocalShapeTransfom()
{
    return PxTransform(GLMToPxVec3(localShapePosition), PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
}

PxCapsuleGeometry CapsuleCollider::createCapsuleGeomentryFromAABB(const PxBounds3& aabb)
{

    PxVec3 dimensions = aabb.getDimensions();

    // Calculate the height of the capsule
    float height = dimensions.y;

    // Calculate the radius of the capsule
    //radius = 0.5f * PxMax(dimensions.x, PxMax(dimensions.y, dimensions.z));
     radius = 0.5f * PxMax(dimensions.x, dimensions.z);

    halfHeight = height * 0.5f;
    // Create the capsule geometry
    capsule.radius = radius;
    capsule.halfHeight = halfHeight;


    return capsule;
}

void CapsuleCollider::SetCapsuleShape(float radius, float halfHeight)
{
    if (capsuleShape)
    {
        capsule.radius = radius;
        capsule.halfHeight = halfHeight;
        capsuleShape->setGeometry(capsule);
    }
}
