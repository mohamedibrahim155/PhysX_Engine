#pragma once

#include<PxPhysics.h>
#include "BaseCollider.h"

using namespace physx;

class SphereCollider : public BaseCollider
{
public:

	SphereCollider();

	// Inherited via BaseCollider
	void ConstructCollider() override;

	void DrawShape() override;
	void DrawColliderProperties() override;
	void InitializeCollider(PhysXObject* object) override;
	void SetRadius(float radius);

	glm::vec3 Centre;
	float radius = 1;

private:

	PxSphereGeometry CreateSphereGeomentryFromAABB(const PxBounds3& aabb);
};

