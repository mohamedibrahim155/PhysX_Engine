#pragma once
#ifndef MESH_H
#define MESH_H


#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"



#include <string>
#include <vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Textures.h"
#include "Vertex.h"
#include "Triangle.h"
#include "material.h"
#include "Object.h"
#define MAX_BONE_INFLUENCE 4




class Mesh : public Object
{
public:

   

    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<BaseTexture*>      textures;
    BaseMaterial* meshMaterial;
    //unsigned int VAO;
    std::vector<Triangles> triangle;

    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<BaseTexture*>& textures);
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, BaseMaterial* meshMaterial);
    ~Mesh();

    void DrawShadedMesh(Shader* shader);
    void Draw(Shader* shader);
    void DrawSolidColorMesh(Shader* shader , glm::vec3 color);



    void TextureScrolling(const bool& isScroll);

    VertexBuffer* VBO;
    IndexBufferObject* IBO;
    VertexArray* VAO;
    VertexBufferLayout* layout;
    bool isWireFrame = false;
    std::string name;

    void UpdateVertices();
private:
    
    //unsigned int VBO, EBO;

    void SetupMesh();
    void CalculateTriangles();
    bool isTextureScrolling = false;

    // Inherited via Object
    void DrawProperties() override;
    void SceneDraw() override;
};
#endif
