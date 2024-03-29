#pragma once
#include "BaseCollider.h"

enum class Direction
{
	X_axis,
	Y_axis,
	Z_axis
};
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
	void SetAxis(const Direction& direction);
	PxShape* GetShape() override;
    PxTransform GetLocalShapeTransfom() override;

	Direction direction = Direction::Y_axis;
	float radius = 0.5f;
	float halfHeight = 1;
private:

	PxMaterial* physicsMaterial = nullptr;
	PxPhysics* physics = nullptr;
	PxShape* capsuleShape = nullptr;

	PxCapsuleGeometry createCapsuleGeomentryFromAABB(const PxBounds3& aabb);
	void SetCapsuleShape(float radius, float halfHeight);

	PxCapsuleGeometry capsule;

	glm::vec3 GetModelDirection();

};

