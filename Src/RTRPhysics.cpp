#define GLM_ENABLE_EXPERIMENTAL
#include "RTRPhysics.h"
#include <iostream>
#include <glm/ext.hpp>

bool RTRPhysics::check_collisionf(RTRCube* cube, RTRSphere* sphere)
{
    // Get Closest Point on Cube
    glm::vec3 closestPoint = ClosestPoint(cube, sphere->position);

    // Find Distance Between Sphere and Closest Point
    float distSq = glm::length(sphere->position - closestPoint);

    // Get Spheres Radius Squared
    float radiusSq = sphere->radius * sphere->radius;

    // If Distance is less than sphere size. Then we have collision
    return distSq < radiusSq * 2.0f;
}

glm::vec3 RTRPhysics::ClosestPoint(const RTRCube* obb, glm::vec3 point) {
    
    // Initalize return and direction
    glm::vec3 result = obb->position;
    glm::vec3 dir = point - obb->position;

    // Orientation Matrix Only Works For Objects Rotated on X-Axis
    glm::mat3 orientation_matrix
    {
        1.0f, 0.0f, 0.0f,
        0.0f, cosf(obb->rotation_angle.x), sinf(obb->rotation_angle.x),
        0.0f, -sinf(obb->rotation_angle.x), cosf(obb->rotation_angle.x)
    };

    // Loop over Rotation Matrix and calculate closest point
    for (int i = 0; i < 3; ++i) {
        glm::vec3 axis(orientation_matrix[i][0], orientation_matrix[i][1], orientation_matrix[i][2]);

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