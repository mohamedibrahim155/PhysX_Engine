#include "SphereCollider.h"
#include "../PhysXEngine.h"
#include "../PhysXUtils.h"
#include "../../GraphicsRender.h"

SphereCollider::SphereCollider()
{
	physics = PhysXEngine::GetInstance().GetPhysics();
}

void SphereCollider::ConstructCollider()
{

	shapeType = ColliderShape::SPHERE;

	if (physicsMaterial == nullptr)
	{
		physicsMaterial = PhysXEngine::GetInstance().GetPxPhysicsMaterial();
	}

	sphereShape = physics->createShape(
		CreateSphereGeomentryFromAABB(modelAABB),
		*physicsMaterial);
}

void SphereCollider::Render()
{
	if (physicsObject ==  nullptr)  return;

	PxBounds3 boxAABB = modelAABB;

	boxAABB.minimum += GLMToPxVec3(GetPosition());
	boxAABB.maximum += GLMToPxVec3(GetPosition());

	/*PxVec3 extends = GLMToPxVec3(sizeExtents);

	PxVec3 tempExtends;

	tempExtends.x = boxAABB.getExtents(0) * extends.x;
	tempExtends.y = boxAABB.getExtents(1) * extends.y;
	tempExtends.z = boxAABB.getExtents(2) * extends.z;*/


	GraphicsRender::GetInstance().DrawSphere(
		PxVec3ToGLM(boxAABB.getCenter()), 
		radius, 
		glm::vec4(0, 1, 0, 1),
		true);



}

void SphereCollider::InitializeCollider(PhysXObject* object)
{
	BaseCollider::InitializeCollider(object);

	this->ConstructCollider();
}

void SphereCollider::SetPhysicsMaterial(PhysicsMaterial& material)
{
	physicsMaterial = physics->createMaterial(material.staticFriction,
		material.dynamicFriction, material.bounciness);

	physicsMaterial->setFrictionCombineMode(PxCombineToLocal(material.frictionCombine));
	physicsMaterial->setRestitutionCombineMode(PxCombineToLocal(material.bounceCombine));

	PxMaterial* materials[] = { physicsMaterial };

	sphereShape->setMaterials(materials, 1);
}

void SphereCollider::SetRadius(float radius)
{
	this->radius = radius;

	PxSphereGeometry sphere(radius);

	if (sphereShape)
	{
		sphereShape->setGeometry(sphere);
	}
}

PxShape* SphereCollider::GetShape()
{
	return sphereShape;
}

PxSphereGeometry SphereCollider::CreateSphereGeomentryFromAABB(const PxBounds3& aabb)
{

	PxVec3 sideLengths = aabb.getDimensions();

    radius = 0.5f * glm::max(sideLengths.x, glm::max(sideLengths.y, sideLengths.z));

	PxSphereGeometry sphere(radius);

	return sphere;
}