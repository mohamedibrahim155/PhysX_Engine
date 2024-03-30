#include "BoxCollider.h"
#include "../PhysXEngine.h"
#include "../PhysXUtils.h"
#include "../../GraphicsRender.h"
BoxCollider::BoxCollider()
{
}

BoxCollider::~BoxCollider()
{
	if (shape)
	{
		shape->release();
	}
}

void BoxCollider::ConstructCollider()
{
	shapeType = ColliderShape::BOX;

	shape = physics->createShape(
		CreateBoxGeometryFromAABB(modelAABB), 
		*physicsMaterial);

	shape->setLocalPose(GetLocalShapeTransfom());

}

void BoxCollider::InitializeCollider(PhysXObject* object)
{
	BaseCollider::InitializeCollider(object);

	ConstructCollider();

}


void BoxCollider::SetSize(glm::vec3 size)
{
	sizeExtents = size;

	 PxBoxGeometry shapeGeomentry = CreateBoxGeometryFromAABB(modelAABB);

	if (shape)
	{
		shape->setGeometry(shapeGeomentry);
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



