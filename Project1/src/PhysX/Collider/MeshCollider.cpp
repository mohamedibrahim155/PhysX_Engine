#include "MeshCollider.h"
#include "../PhysXEngine.h"
#include "../PhysXUtils.h"
#include "../../GraphicsRender.h"
//#include <foundation/PxIO.h>
//#include <cooking/PxCooking.h>
using namespace physx;
MeshCollider::MeshCollider()
{
	physics = PhysXEngine::GetInstance().GetPhysics();
}

MeshCollider::~MeshCollider()
{
	if (pxTriangleMesh)
	{
		meshShape->release();
		pxTriangleMesh->release();

	}
}

void MeshCollider::ConstructCollider()
{
	shapeType = ColliderShape::MESH;


	IntializeMeshCollider();

	if (physicsMaterial == nullptr)
	{
		physicsMaterial = PhysXEngine::GetInstance().GetPxPhysicsMaterial();
	}

	meshShape = physics->createShape(triangleMeshGeomentry,*physicsMaterial);

	meshShape->setLocalPose(GetLocalShapeTransfom());

}

void MeshCollider::InitializeCollider(PhysXObject* object)
{
	BaseCollider::InitializeCollider(object);

	ConstructCollider();
}

void MeshCollider::Render()
{
}

void MeshCollider::SetPhysicsMaterial(PhysicsMaterial& material)
{
	physicsMaterial = physics->createMaterial(material.staticFriction,
		material.dynamicFriction, material.bounciness);

	physicsMaterial->setFrictionCombineMode(PxCombineToLocal(material.frictionCombine));
	physicsMaterial->setRestitutionCombineMode(PxCombineToLocal(material.bounceCombine));

	PxMaterial* materials[] = { physicsMaterial };

	meshShape->setMaterials(materials, 1);
}

PxShape* MeshCollider::GetShape()
{
	return meshShape;
}

void MeshCollider::IntializeMeshCollider()
{
	PxU32 gVertexCount;
    PxArray<PxVec3> vertices;
    PxArray<PxU32> indices;

	int totalMeshVerticesCount = 0;
	int totalMeshIndicesCount = 0;
	int vertexCount = 0;
	int lastMeshVertexCount = 0;


	

	for (std::shared_ptr<Mesh> mesh : physicsObject->meshes)
	{

		totalMeshVerticesCount += mesh->vertices.size();
		totalMeshIndicesCount += mesh->indices.size();

		lastMeshVertexCount = vertexCount;
		for (Vertex& vertex : mesh->vertices)
		{
			vertices.pushBack(GLMToPxVec3(vertex.Position));
			vertexCount++;
		}

		for (unsigned int index : mesh->indices)
		{
			indices.pushBack(index + lastMeshVertexCount);
		}

	}

	const PxTolerancesScale scale;
	PxCookingParams params(scale);
	params.midphaseDesc.setToDefault(PxMeshMidPhase::eBVH34);
	params.meshPreprocessParams |= PxMeshPreprocessingFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE;
	params.meshPreprocessParams |= PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH;
	PxTriangleMeshDesc triangleMeshDesc;
	triangleMeshDesc.points.count = totalMeshVerticesCount;
	triangleMeshDesc.points.data = vertices.begin();
	triangleMeshDesc.points.stride = sizeof(PxVec3);
	triangleMeshDesc.triangles.count = totalMeshIndicesCount / 3;
	triangleMeshDesc.triangles.data = indices.begin();
	triangleMeshDesc.triangles.stride = 3 * sizeof(PxU32);

	PxDefaultMemoryOutputStream writeBuffer;
	
	if (!PxCookTriangleMesh(params, triangleMeshDesc, writeBuffer))
	{
		// Handle cooking failure

		return;
	}
	PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
	 pxTriangleMesh = physics->createTriangleMesh(readBuffer);


	triangleMeshGeomentry.scale = GLMToPxVec3(modelTransform->scale);
	triangleMeshGeomentry.triangleMesh = pxTriangleMesh;

	vertices.clear();
	indices.clear();
}
