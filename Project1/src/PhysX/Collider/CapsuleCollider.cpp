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

  
    glm::vec3 getDirection = GetModelDirection();
   
    glm::vec3 upSphere = (modelTransform->position + offsetPosition +localShapePosition) + getDirection * halfHeight;
    glm::vec3 downSphere = (modelTransform->position + offsetPosition + localShapePosition) - getDirection * halfHeight;

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

void CapsuleCollider::SetAxis(const Direction& direction)
{
    this->direction = direction;
    capsuleShape->setLocalPose(GetLocalShapeTransfom());
}



PxShape* CapsuleCollider::GetShape()
{
    return capsuleShape;
}

PxTransform CapsuleCollider::GetLocalShapeTransfom()
{
    switch (direction)
    {
    case Direction::X_axis:
        return PxTransform(GLMToPxVec3(localShapePosition), PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f)));

        break;
    case Direction::Y_axis:
        return PxTransform(GLMToPxVec3(localShapePosition), PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
        break;
    case Direction::Z_axis:
        return PxTransform(GLMToPxVec3(localShapePosition), PxQuat(PxHalfPi, PxVec3(0.0f, 1.0f, 0.0f)));
        break;
    default:
        break;
    }
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

glm::vec3 CapsuleCollider::GetModelDirection()
{
    switch (direction)
    {
    case Direction::X_axis:
        return modelTransform->GetRight();

        break;
    case Direction::Y_axis:
        return modelTransform->GetUp();
        break;
    case Direction::Z_axis:
        return modelTransform->GetForward();
        break;
    }
    return glm::vec3(0);
}
