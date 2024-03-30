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

	float radius = 1;

private:

	PxSphereGeometry CreateSphereGeomentryFromAABB(const PxBounds3& aabb);

	float columnWidth = 150.0f;
};

