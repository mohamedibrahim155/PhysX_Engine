#pragma once
#include "glm/glm.hpp"
#include <PxMaterial.h>
#include<PxPhysics.h>
#include "BaseCollider.h"
using namespace physx;


class BoxCollider : public BaseCollider
{
public :

	BoxCollider();
	~BoxCollider();

	// Inherited via BaseCollider
    void ConstructCollider() override;
    void InitializeCollider(PhysXObject* object) override;
	void DrawShape() override;
	void DrawColliderProperties() override;
	void SetSize(glm::vec3 size);

	glm::vec3 boxCentre;
	glm::vec3 sizeExtents = glm::vec3(1);

private:

	PxBoxGeometry CreateBoxGeometryFromAABB(const PxBounds3& aabb);
};

