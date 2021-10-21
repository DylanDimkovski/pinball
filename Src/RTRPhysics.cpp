#define GLM_ENABLE_EXPERIMENTAL
#include "RTRPhysics.h"
#include <iostream>
#include <glm/ext.hpp>

bool RTRPhysics::SphereOBB_Detection(RTRSphere* sphere, RTRCube* cube)
{
    // Get Closest Point on Cube
    glm::vec3 closest_point = ClosestPoint(cube, sphere->position);

    // Find Distance Between Sphere and Closest Point
    sphere->distance = glm::length(sphere->position - closest_point);

    // Get Spheres Radius Squared
    float radiusSq = sphere->size.x * sphere->size.x;

    // If Distance is less than sphere size-> Then we have collision
    return sphere->distance < radiusSq * 2.0f;
}

glm::vec3 RTRPhysics::SphereOBB_Resolution(RTRSphere* sphere, RTRCube* cube)
{
    glm::vec3 closest_point = ClosestPoint(cube, sphere->position);

    if (sphere->position.y < closest_point.y)
    {
        sphere->position.y = closest_point.y + (sphere->size.x * sphere->size.x);
    }

    glm::vec3 normal = glm::normalize(sphere->position - closest_point);

    sphere->movement->velocity -= 2 * glm::dot(cube->rotation, normal) * normal;

    return sphere->movement->velocity;
}


glm::vec3 RTRPhysics::ClosestPoint(RTRCube* obb, glm::vec3 point) {
    
    // Initalize return and direction
    glm::vec3 result = obb->position;
    glm::vec3 dir = point - obb->position;

    // Loop over Rotation Matrix and calculate closest point
    for (int i = 0; i < 3; ++i) {
        glm::vec3 axis(obb->orientation_matrix[i][0], obb->orientation_matrix[i][1], obb->orientation_matrix[i][2]);

        float distance = glm::dot(dir, axis);

        if (distance > obb->size[i]) {
            distance = obb->size[i];
        }
        if (distance < -obb->size[i]) {
            distance = -obb->size[i];
        }

        result += axis * distance;
    }
    
    return result;
}