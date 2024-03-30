#include "BaseCollider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "CapsuleCollider.h"
#include "../PhysXObject.h"
#include "../PhysXUtils.h"
#include "../PhysXEngine.h"

BaseCollider::BaseCollider()
{
	physics = PhysXEngine::GetInstance().GetPhysics();
	physicsMaterial = PhysXEngine::GetInstance().GetPxPhysicsMaterial();
}

void BaseCollider::InitializeCollider(PhysXObject* object)
{
	physicsObject = object;

	modelTransform = &object->transform;

	modelAABB = CalculatePxModelAABB();

	modelAABB.minimum.x *= modelTransform->scale.x;
	modelAABB.minimum.y *= modelTransform->scale.y;
	modelAABB.minimum.z *= modelTransform->scale.z;

	modelAABB.maximum.x *= modelTransform->scale.x;
	modelAABB.maximum.y *= modelTransform->scale.y;
	modelAABB.maximum.z *= modelTransform->scale.z;

	
}

void BaseCollider::SetPhysicsMaterial(PhysicsMaterial& material)
{
	physicsMaterial = physics->createMaterial(material.staticFriction,
		material.dynamicFriction, material.bounciness);

	physicsMaterial->setFrictionCombineMode(PxCombineToLocal(material.frictionCombine));
	physicsMaterial->setRestitutionCombineMode(PxCombineToLocal(material.bounceCombine));

	PxMaterial* materials[] = { physicsMaterial };

	shape->setMaterials(materials, 1);
}

PxShape* BaseCollider::GetShape()
{
	return shape;
}

glm::vec3 BaseCollider::GetPosition()
{
	return modelTransform->position + offsetPosition;
}

glm::vec3 BaseCollider::GetOffsetPosition()
{
	return offsetPosition;
}

glm::quat BaseCollider::GetRotation()
{
	return modelTransform->quaternionRotation;
}

PxTransform BaseCollider::GetLocalShapeTransfom()
{
	return PxTransform(GLMToPxVec3(localShapePosition),PxQuat(0,0,0,1));
}

void BaseCollider::SetCentreOffset(const glm::vec3& offsetValue)
{
	offsetPosition = offsetValue;
}

BoxCollider* BaseCollider::AsBoxCollider()
{
	return (BoxCollider*)this;
}

SphereCollider* BaseCollider::AsSphereCollider()
{
	return (SphereCollider*)this;
}

CapsuleCollider* BaseCollider::AsCapsuleCollider()
{
	return (CapsuleCollider*)this;
}

PxBounds3 BaseCollider::CalculatePxModelAABB()
{
	if (physicsObject->meshes.empty())
	{
		return PxBounds3{ PxVec3(0.0f), PxVec3(0.0f) };
	}

	PxBounds3 minMax;

	minMax.minimum = GLMToPxVec3(physicsObject->meshes[0]->vertices[0].Position);
	minMax.maximum = GLMToPxVec3(physicsObject->meshes[0]->vertices[0].Position);

	for (std::shared_ptr<Mesh> mesh : physicsObject->meshes)
	{
		PxBounds3 temp = CalculateAABB(mesh->vertices);

		minMax.minimum.x = PxMin(temp.minimum.x, minMax.minimum.x);
		minMax.minimum.y = PxMin(temp.minimum.y, minMax.minimum.y);
		minMax.minimum.z = PxMin(temp.minimum.z, minMax.minimum.z);

		minMax.maximum.x = PxMax(temp.maximum.x, minMax.maximum.x);
		minMax.maximum.y = PxMax(temp.maximum.y, minMax.maximum.y);
		minMax.maximum.z = PxMax(temp.maximum.z, minMax.maximum.z);
	}

	return PxBounds3(minMax.minimum, minMax.maximum);
}
