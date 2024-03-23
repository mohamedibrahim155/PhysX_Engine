#include "BoxCollider.h"
#include "../PhysXEngine.h"
#include "../PhysXUtils.h"
#include "../../GraphicsRender.h"
BoxCollider::BoxCollider()
{
	physics = PhysXEngine::GetInstance().GetPhysics();
}

BoxCollider::~BoxCollider()
{
	if (boxshape)
	{
		boxshape->release();
	}
}

void BoxCollider::ConstructCollider()
{
	shapeType = ColliderShape::BOX;

	if (physicsMaterial == nullptr)
	{
		physicsMaterial = PhysXEngine::GetInstance().GetPxPhysicsMaterial();
	}

	boxshape = physics->createShape(
		CreateBoxGeometryFromAABB(modelAABB), 
		*physicsMaterial);

	sizeExtents = PxVec3ToGLM(modelAABB.getDimensions() * 0.5f);
}

void BoxCollider::InitializeCollider(PhysXObject* object)
{
	BaseCollider::InitializeCollider(object);

	ConstructCollider();

}

PxShape* BoxCollider::GetShape()
{
	return boxshape;
}

PxBoxGeometry BoxCollider::CreateBoxGeometryFromAABB(const PxBounds3& aabb)
{
	PxVec3 dimensions = aabb.getDimensions();
	PxBoxGeometry boxGeometry(dimensions * 0.5f); // Half extents are used for PxBoxGeometry
	return boxGeometry;
}

void BoxCollider::Render()
{
	if (physicsObject)
	{
		PxBounds3 boxAABB = modelAABB;

		boxAABB.minimum += GLMToPxVec3( physicsObject->transform.position);
		boxAABB.maximum += GLMToPxVec3(physicsObject->transform.position);



		GraphicsRender::GetInstance().DrawBox(
			PxVec3ToGLM(boxAABB.getCenter()),
			PxVec3ToGLM(boxAABB.getDimensions() * 0.5f),
			physicsObject->transform.rotation,
			glm::vec4(0,1,0,1),true);

	}
}

void BoxCollider::SetPhysicsMaterial(PhysicsMaterial& material)
{
	physicsMaterial = physics->createMaterial(material.staticFriction,
		material.dynamicFriction, material.bounciness);

	physicsMaterial->setFrictionCombineMode(PxCombineToLocal(material.frictionCombine));
	physicsMaterial->setRestitutionCombineMode(PxCombineToLocal(material.bounceCombine));

	PxMaterial* materials[] = { physicsMaterial };

	boxshape->setMaterials(materials, 1);
}


