//-----------------------------------------------------------------------------
// RTRObject.h
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------
#pragma once
#include "RTRLighting.h"
#include "RTRTexture.h"
#include "RTRShader.h"
#include "RTRMovement.h"
#include <vector>

struct RTRPoint_t {
    float x, y, z;
};

struct RTRFace_t {
    unsigned int v0, v1, v2;
};

class RTRObject
{
public:
    RTRObject() {}
    ~RTRObject() {}
    virtual void Init();
    virtual void Render(RTRShader* shader);
    virtual void End();
    void SetMaterial(RTRMaterial_t mat) { m_Material = mat; }
    void SetTexture(char const* filename) { textureID = texture->load_texture(filename); }
    virtual const char* GetName() { return "RTRObject"; }

    RTRTexture* texture = new RTRTexture();
    RTRMovement* movement = new RTRMovement();
    RTRMaterial_t m_Material{ {0.19225, 0.19225, 0.19225 }, { 0.50754, 0.50754, 0.50754 }, { 0.508273, 0.508273, 0.508273 }, 128.0 };

    unsigned int m_VertexBuffer{ 0 };
    unsigned int m_TexBuffer{ 0 };
    unsigned int m_VertexArray{ 0 };
    unsigned int m_FaceElementBuffer{ 0 };
    unsigned int textureID = 0;

    bool is_created = false;

    float distance = 0;

    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    glm::vec3 size{ 0.0f };
    glm::vec3 rotation{ 0.0f };
    glm::vec3 position{ 0.0f };

    glm::mat4 model_matrix = glm::identity<glm::mat4>();

    glm::mat4 orientation_matrix = glm::identity<glm::mat4>();
    glm::mat4 translate_matrix = glm::identity<glm::mat4>();;
    glm::mat4 scale_matrix = glm::identity<glm::mat4>();;
};
