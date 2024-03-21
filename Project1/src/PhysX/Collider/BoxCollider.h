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

	// Inherited via Object
	void DrawProperties() override;
	void SceneDraw() override;

	PxShape* GetShape();

private:


	PxMaterial* physicsMaterial;
	PxPhysics* physics;

};

