#include "RTRCube.h"

void RTRCube::Init()
{
    float angle = 25.0f * 3.14159265359 / 180;
    rotation_angle = { angle, angle, angle };
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

    indices.insert(indices.end(), {
        1, 4, 7, 1, 7, 2,
        5, 0, 3, 5, 3, 6,
        3, 2, 7, 3, 7, 6,
        5, 4, 1, 5, 1, 0,
        0, 1, 2, 0, 2, 3,
        4, 5, 6, 4, 6, 7
    });
    model_matrix = glm::rotate(model_matrix, rotation_angle.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model_matrix = glm::scale(model_matrix, size);
        
    min.x = -1;
    min.y = -1;
    min.z = -1;
    max.x = 1;
    max.y = 1;
    max.z = 1;

    RTRObject::Init();
}
