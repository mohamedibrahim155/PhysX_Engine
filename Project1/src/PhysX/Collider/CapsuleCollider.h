#pragma once
#include "BaseCollider.h"

enum class Direction
{
	X_axis =0,
	Y_axis=1,
	Z_axis=2
};
class CapsuleCollider : public BaseCollider
{
public:

	CapsuleCollider();

	// Inherited via BaseCollider
	void ConstructCollider() override;

	void DrawShape() override;
	void DrawColliderProperties() override;
    void InitializeCollider(PhysXObject* object) override;
	void SetRadius(float radius);
	void SetHalfLength(float halfLength);
	void SetAxis(const Direction& direction);

    PxTransform GetLocalShapeTransfom() override;

	Direction direction = Direction::Y_axis;
	float radius = 0.5f;
	float halfHeight = 1;
private:

	void SetCapsuleShape(float radius, float halfHeight);
	PxCapsuleGeometry createCapsuleGeomentryFromAABB(const PxBounds3& aabb);
	glm::vec3 GetModelDirection();

	PxCapsuleGeometry capsule;
	float columnWidth = 150.0f;
	static const char* directionOptions[];

};

