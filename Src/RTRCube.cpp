#include "RTRCube.h"

void RTRCube::Init()
{
    float angle = 25.0f * glm::pi<float>() / 180;
    rotation_angle = { angle, angle, angle };
    position = { 0.0f, 0.0f, 0.0f };
    size = { 5.0f, 0.5f, 10.0f };
    vertices.insert(vertices.end(), {
        glm::vec3(-1, -1, 1),
        glm::vec3(1, -1,  1),
        glm::vec3(1,  1,  1),
        glm::vec3(-1,  1,  1),
        glm::vec3(1, -1, -1),
        glm::vec3(-1, -1, -1),
        glm::vec3(-1,  1, -1),
        glm::vec3(1,  1, -1)
    });
    bounding_box.insert(bounding_box.end(), {
        glm::vec3(-1, -1, 1),
        glm::vec3(1, -1,  1),
        glm::vec3(1,  1,  1),
        glm::vec3(-1,  1,  1),
        glm::vec3(1, -1, -1),
        glm::vec3(-1, -1, -1),
        glm::vec3(-1,  1, -1),
        glm::vec3(1,  1, -1)
        });
    indices.insert(indices.end(), {
        1, 4, 7, 1, 7, 2,
        5, 0, 3, 5, 3, 6,
        3, 2, 7, 3, 7, 6,
        5, 4, 1, 5, 1, 0,
        0, 1, 2, 0, 2, 3,
        4, 5, 6, 4, 6, 7
    });
    RTRObject::Init();
}
