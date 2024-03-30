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


private:

	PxTriangleMeshGeometry triangleMeshGeomentry;
	PxTriangleMesh* pxTriangleMesh = nullptr;

	void IntializeMeshCollider();

};

