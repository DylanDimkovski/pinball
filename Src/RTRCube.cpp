#include "RTRCube.h"

void RTRCube::Init()
{
    // Set Rotation Angle and Size
    float angle = 25.0f * 3.14159265359 / 180;
    rotation = { angle, angle, angle };
    movement->pitch_delta, movement->yaw_delta, movement->roll_delta = angle;
    size = { 5.0f, 2.0f, 10.0f };

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

    // Apply any Transformations
    model_matrix = glm::rotate(model_matrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    orientation_matrix = glm::rotate(orientation_matrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model_matrix = glm::scale(model_matrix, size);

    // Set New Material
    m_Material = {{0.329412f, 0.223529f, 0.027451f}, {0.780392f, 0.568627f, 0.113725f}, {0.992157f, 0.941176f, 0.807843f}, 40.8974f};
    RTRObject::Init();
    textureID = texture->load_texture("D:/Uni Work/RealTimeGraphics/A2_SURNAME_FIRSTNAME/Src/textures/Wood066_4K_Color.png");
}

