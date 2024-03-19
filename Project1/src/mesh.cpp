#include "mesh.h"
#include <string>
#include "Renderer.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<BaseTexture*>& textures)
{
    
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    SetupMesh();
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, BaseMaterial* meshMaterial)
{
    this->vertices = vertices;
    this->indices = indices;
    this->meshMaterial = meshMaterial;

    SetupMesh();
}

Mesh::~Mesh()
{
    delete VBO;
    delete IBO;
    delete VAO;
    delete layout;
    delete meshMaterial;

    vertices.clear();
    indices.clear();

    for (BaseTexture*  texture : textures)
    {
        delete texture;
    }

    textures.clear();

    triangle.clear();


}



void Mesh::DrawShadedMesh(Shader* shader)
{
    shader->Bind();  
    meshMaterial->UpdateMaterial(shader);
    
    VAO->Bind();
    IBO->Bind();

    if (isWireFrame)
    {
        GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    }
    else
    {
        GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
    }


    GLCALL(glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0));

   // ((Texture*)meshMaterial->material()->diffuseTexture)->Unbind();
   // ((Texture*)meshMaterial->material()->specularTexture)->Unbind();
  //  ((Texture*)meshMaterial->material()->alphaTexture)->Unbind();
    VAO->Unbind();


}

void Mesh::Draw(Shader* shader)
{
    if (shader->blendMode == SOLID)
    {
        DrawSolidColorMesh(shader , glm::vec4(1));
    }
    else /*if (shader->blendMode == OPAQUE || shader->blendMode == ALPHA_BLEND || shader->blendMode == ALPHA_CUTOUT)*/
    {
        DrawShadedMesh(shader);
    }
}

void Mesh::DrawSolidColorMesh(Shader* shader, glm::vec3 color)
{
   

    if (shader->blendMode == BlendMode::SOLID)
    {
        shader->Bind();
        shader->setVec3("objectColor", color.x, color.y, color.z);
    }
  
    VAO->Bind();
    IBO->Bind();

    if (isWireFrame)
    {
        GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    }
    else
    {
        GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
    }


    GLCALL(glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0));
    VAO->Unbind();
}



void Mesh::TextureScrolling(const bool& isScroll)
{

    this->isTextureScrolling = isScroll;

}

void Mesh::UpdateVertices()
{
    VAO->Bind();
    VBO->UpdateVertexData(vertices.size() * sizeof(Vertex), &vertices[0]);
    VAO->AddBuffer(*VBO, *layout);
    VAO->Unbind();
}

void Mesh::SetupMesh()
{
    CalculateTriangles();
    VAO = new VertexArray();
    void* pVertices = static_cast<void*>(&vertices[0]);
    unsigned int size = vertices.size() * sizeof(Vertex);
    VBO = new VertexBuffer(pVertices, size);
    layout = new VertexBufferLayout();

    layout->Push<float>(3);
    layout->Push<float>(3);
    layout->Push<float>(2);
    layout->Push<float>(4);
    layout->Push<float>(4); //bone ID
    layout->Push<float>(4);  // Bone weight

    VAO->AddBuffer(*VBO, *layout);
    IBO = new IndexBufferObject(&indices[0], indices.size());

}

void Mesh::CalculateTriangles()
{
    for (size_t i = 0; i < indices.size(); i += 3)
    {
        Triangles tempTri;

        tempTri.v1 = vertices[indices[i]].Position;
        tempTri.v2 = vertices[indices[i + 1]].Position;
        tempTri.v3 = vertices[indices[i + 2]].Position;

        tempTri.normal = (vertices[indices[i]].Normal +
            vertices[indices[i + 1]].Normal +
            vertices[indices[i + 2]].Normal) / 3.0f;
        triangle.push_back(tempTri);
    }
}

void Mesh::DrawProperties()
{
    ImGui::InputText("##ObjectName", &name[0], 516);
}

void Mesh::SceneDraw()
{
}
