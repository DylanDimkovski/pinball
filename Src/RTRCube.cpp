#include "RTRCube.h"

void RTRCube::Init()
{
    movement->pitch_delta, movement->yaw_delta, movement->roll_delta = rotation.x;

    glm::vec3 v[8] = {
        glm::vec3(1, 1, 1),
        glm::vec3(-1, 1,  1),
        glm::vec3(-1, -1,  1),
        glm::vec3(1,  -1,  1),
        glm::vec3(1, 1, -1),
        glm::vec3(-1, 1, -1),
        glm::vec3(-1,  -1, -1),
        glm::vec3(1, -1, -1)
    };

    // Add Vertices For Drawing
    vertices.insert(vertices.begin(), {
        v[1], v[2], v[3], v[3], v[0], v[1],
        v[5], v[4], v[7], v[7], v[6], v[5],
        v[1], v[5], v[6], v[6], v[2], v[1],
        v[0], v[3], v[7], v[7], v[4], v[0],
        v[1], v[0], v[4], v[4], v[5], v[1],
        v[3], v[2], v[6], v[6], v[7], v[3]
    });

    // Add TexCoords For Drawing
    texCoords.insert(texCoords.begin(), {
        glm::vec2(0.0f, 0.0f)*tex_scale,
        glm::vec2(1.0f, 0.0f)*tex_scale,
        glm::vec2(1.0f, 1.0f)*tex_scale,
        glm::vec2(1.0f, 1.0f)*tex_scale,
        glm::vec2(0.0f, 1.0f)*tex_scale,
        glm::vec2(0.0f, 0.0f)*tex_scale,
                             
        glm::vec2(0.0f, 0.0f)*tex_scale,
        glm::vec2(1.0f, 0.0f)*tex_scale,
        glm::vec2(1.0f, 1.0f)*tex_scale,
        glm::vec2(1.0f, 1.0f)*tex_scale,
        glm::vec2(0.0f, 1.0f)*tex_scale,
        glm::vec2(0.0f, 0.0f)*tex_scale,
                          
        glm::vec2(0.0f, 0.0f)*tex_scale,
        glm::vec2(1.0f, 0.0f)*tex_scale,
        glm::vec2(1.0f, 1.0f)*tex_scale,
        glm::vec2(1.0f, 1.0f)*tex_scale,
        glm::vec2(0.0f, 1.0f)*tex_scale,
        glm::vec2(0.0f, 0.0f)*tex_scale,
                         
        glm::vec2(0.0f, 0.0f)*tex_scale,
        glm::vec2(1.0f, 0.0f)*tex_scale,
        glm::vec2(1.0f, 1.0f)*tex_scale,
        glm::vec2(1.0f, 1.0f)*tex_scale,
        glm::vec2(0.0f, 1.0f)*tex_scale,
        glm::vec2(0.0f, 0.0f)*tex_scale,
                            
        glm::vec2(0.0f, 0.0f)*tex_scale,
        glm::vec2(1.0f, 0.0f)*tex_scale,
        glm::vec2(1.0f, 1.0f)*tex_scale,
        glm::vec2(1.0f, 1.0f)*tex_scale,
        glm::vec2(0.0f, 1.0f)*tex_scale,
        glm::vec2(0.0f, 0.0f)*tex_scale,
                         
        glm::vec2(0.0f, 0.0f)*tex_scale,
        glm::vec2(1.0f, 0.0f)*tex_scale,
        glm::vec2(1.0f, 1.0f)*tex_scale,
        glm::vec2(1.0f, 1.0f)*tex_scale,
        glm::vec2(0.0f, 1.0f)*tex_scale,
        glm::vec2(0.0f, 0.0f)*tex_scale
    });
    // Set New Material
    m_Material = {{0.329412f, 0.223529f, 0.027451f}, {0.780392f, 0.568627f, 0.113725f}, {0.992157f, 0.941176f, 0.807843f}, 40.8974f};
    RTRObject::Init();
}

