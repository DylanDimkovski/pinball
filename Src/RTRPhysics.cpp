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

bool RTRPhysics::check_collisionww(RTRSphere* sphere)
{
    if ((sphere->position.z - sphere->radius) < 5.0 || (sphere->position.z + sphere->radius) > 5.0) 
    {
        return true;
    }
    return false;
}

glm::vec3 RTRPhysics::ClosestPoint(const RTRCube* obb, glm::vec3 point) {
    
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