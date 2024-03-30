#pragma once
#include "BaseCollider.h"
class MeshCollider : public BaseCollider
{
public:
	MeshCollider();
	~MeshCollider();
	// Inherited via BaseCollider
	void ConstructCollider() override;
   void InitializeCollider(PhysXObject* object) override;


	void Render() override;

	void SetPhysicsMaterial(PhysicsMaterial& material) override;

	PxShape* GetShape() override;

private:

	PxMaterial* physicsMaterial = nullptr;
	PxPhysics* physics = nullptr;
	PxShape* meshShape = nullptr;

	PxTriangleMeshGeometry triangleMeshGeomentry;
	PxTriangleMesh* pxTriangleMesh = nullptr;

	void IntializeMeshCollider();

};

