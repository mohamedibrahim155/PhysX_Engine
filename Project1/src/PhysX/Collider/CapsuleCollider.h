#pragma once
#include "BaseCollider.h"
class CapsuleCollider : public BaseCollider
{
public:

	CapsuleCollider();

	// Inherited via BaseCollider
	void ConstructCollider() override;

	void Render() override;
    void InitializeCollider(PhysXObject* object) override;
	void SetPhysicsMaterial(PhysicsMaterial& material) override;
	void SetRadius(float radius);
	void SetHalfLength(float halfLength);
	PxShape* GetShape() override;
    PxTransform GetLocalShapeTransfom() override;


	float radius = 0.5f;
	float halfHeight = 1;
private:

	PxMaterial* physicsMaterial = nullptr;
	PxPhysics* physics = nullptr;
	PxShape* capsuleShape = nullptr;

	PxCapsuleGeometry createCapsuleGeomentryFromAABB(const PxBounds3& aabb);
	void SetCapsuleShape(float radius, float halfHeight);

	PxCapsuleGeometry capsule;

};

