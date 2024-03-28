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

	boxshape->setLocalPose(GetLocalShapeTransfom());

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

void BoxCollider::SetSize(glm::vec3 size)
{
	sizeExtents = size;

	 PxBoxGeometry shapeGeomentry = CreateBoxGeometryFromAABB(modelAABB);

	if (boxshape)
	{
		boxshape->setGeometry(shapeGeomentry);
	}
}

PxBoxGeometry BoxCollider::CreateBoxGeometryFromAABB(const PxBounds3& aabb)
{
	PxVec3 dimensions = aabb.getDimensions();

	PxVec3 extends = GLMToPxVec3(sizeExtents);

	PxVec3 tempExtends;

	tempExtends.x = aabb.getExtents(0) * extends.x;
	tempExtends.y = aabb.getExtents(1) * extends.y;
	tempExtends.z = aabb.getExtents(2) * extends.z;

	PxBoxGeometry boxGeometry(tempExtends); // Half extents are used for PxBoxGeometry

	return boxGeometry;
}

void BoxCollider::Render()
{
	if (physicsObject)
	{
		PxBounds3 boxAABB = modelAABB;

		boxAABB.minimum += GLMToPxVec3(GetPosition());
		boxAABB.maximum += GLMToPxVec3(GetPosition());

		PxVec3 extends = GLMToPxVec3(sizeExtents);

		PxVec3 tempExtends;

		tempExtends.x = boxAABB.getExtents(0) * extends.x;
		tempExtends.y = boxAABB.getExtents(1) * extends.y;
		tempExtends.z = boxAABB.getExtents(2) * extends.z;


		GraphicsRender::GetInstance().DrawBox(
			PxVec3ToGLM(boxAABB.getCenter()),
			PxVec3ToGLM(tempExtends),
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


