#include "SphereCollider.h"
#include "../PhysXEngine.h"
#include "../PhysXUtils.h"
#include "../../GraphicsRender.h"

SphereCollider::SphereCollider()
{
}

void SphereCollider::ConstructCollider()
{

	shapeType = ColliderShape::SPHERE;

	shape = physics->createShape(
		CreateSphereGeomentryFromAABB(modelAABB),
		*physicsMaterial);

	shape->setLocalPose(GetLocalShapeTransfom());
}

void SphereCollider::DrawShape()
{
	if (physicsObject ==  nullptr)  return;

	PxBounds3 boxAABB = modelAABB;

	boxAABB.minimum += GLMToPxVec3(GetPosition());
	boxAABB.maximum += GLMToPxVec3(GetPosition());

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

void SphereCollider::SetRadius(float radius)
{
	this->radius = radius;

	PxSphereGeometry sphere(radius);

	if (shape)
	{
		shape->setGeometry(sphere);
	}
}



PxSphereGeometry SphereCollider::CreateSphereGeomentryFromAABB(const PxBounds3& aabb)
{

	PxVec3 sideLengths = aabb.getDimensions();

    radius = 0.5f * glm::max(sideLengths.x, glm::max(sideLengths.y, sideLengths.z));

	PxSphereGeometry sphere(radius);

	return sphere;
}

void SphereCollider::DrawColliderProperties()
{
	ImGui::NewLine();

	if (!ImGui::TreeNodeEx("Sphere Collider", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	if (DrawBoolImGui("is Trigger", isTrigger))
	{
		SetTriggerState(isTrigger);
	}

	DrawTransformVector3ImGui("Offset Position", offsetPosition, 0, columnWidth);

	if (DrawDragFloatImGui("Radius", radius, 0.1f, 0.01f))
	{
		SetRadius(radius);
	}

	ImGui::TreePop();
}
