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

	glm::vec3 boxCentre;
	glm::vec3 sizeExtents = glm::vec3(2);

	// Inherited via BaseCollider
    void ConstructCollider() override;
    void InitializeCollider(PhysXObject* object) override;
	PxShape* GetShape() override;


private:


	PxMaterial* physicsMaterial;
	PxPhysics* physics;
	PxShape* boxshape = nullptr;

	PxBoxGeometry CreateBoxGeometryFromAABB(const PxBounds3& aabb);

	


	// Inherited via BaseCollider
	void Render() override;

};

