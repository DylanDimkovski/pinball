#include "RTRPeg.h"

void RTRPeg::Init()
{
    glm::vec3 v[8] = {
        glm::vec3(1, 1, 1),
        glm::vec3(-1, 1,  1),
        glm::vec3(-1, -1,  1),
        glm::vec3(1,  -1,  1),
        glm::vec3(0, 1, -2),
        glm::vec3(-0, 1, -2),
        glm::vec3(-0,  -1.0, -2),
        glm::vec3(0, -1, -2)
    };

    // Add Vertices For Drawing
    vertices.insert(vertices.begin(), {
        v[1], v[2], v[3], v[3], v[0], v[1], // Front
        v[1], v[5], v[6], v[6], v[2], v[1], // Left
        v[0], v[3], v[7], v[7], v[4], v[0], // Right
        v[1], v[0], v[4], v[4], v[5], v[1], // Top
        v[3], v[2], v[6], v[6], v[7], v[3] // Bottom
        });

    // Add TexCoords For Drawing
    texCoords.insert(texCoords.begin(), {
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),

        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),

        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),

        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),

        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, 0.0f)
        });
	// Set Material
	m_Material = { {0.329412f, 0.223529f, 0.027451f}, {0.780392f, 0.568627f, 0.113725f}, {0.992157f, 0.941176f, 0.807843f}, 40.8974f };
	RTRObject::Init();
}

void RTRPeg::End() 
{
	RTRObject::End();
}