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

	void Render() override;
	void InitializeCollider(PhysXObject* object) override;
	void SetPhysicsMaterial(PhysicsMaterial& material) override;
	void SetRadius(float radius);

	PxShape* GetShape() override;

	glm::vec3 Centre;
	float radius = 1;

private:

	PxSphereGeometry CreateSphereGeomentryFromAABB(const PxBounds3& aabb);
	PxMaterial* physicsMaterial = nullptr;
	PxPhysics* physics = nullptr;
	PxShape* sphereShape = nullptr;


};

