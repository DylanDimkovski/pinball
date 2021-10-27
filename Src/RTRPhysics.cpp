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

    sphere->movement->initial_velocity = sphere->movement->velocity;

    // If Distance is less than sphere size Then we have collision
    return sphere->distance < sphere->size.x;
}

glm::vec3 RTRPhysics::SphereOBB_Resolution(RTRSphere* sphere, RTRCube* cube)
{
    // Calculate Normal
    glm::vec3 closest_point = ClosestPoint(cube, sphere->position);
    glm::vec3 normal = glm::normalize(sphere->position - closest_point);

    if (glm::length(sphere->position) < glm::length(closest_point))
    {
        sphere->position.y = closest_point.y + sphere->size.x;
    }

    // Calculate Reflection
    sphere->movement->velocity = glm::reflect(sphere->movement->velocity, normal);

    sphere->movement->velocity *= 0.9999f;

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