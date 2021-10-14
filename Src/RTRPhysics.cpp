#define GLM_ENABLE_EXPERIMENTAL
#include "RTRPhysics.h"
#include <iostream>
#include <glm/ext.hpp>

bool RTRPhysics::check_collisionf(RTRCube* cube, RTRSphere* sphere)
{
    // Get Center of Sphere 
    glm::vec3 center(abs(sphere->position) + sphere->radius);
    glm::mat4 inverse_point = glm::inverse(cube->model_matrix);

    center = glm::vec4(center, 1.0f) * inverse_point;

    glm::vec3 closest
    {
        glm::max(cube->min.x, glm::min(center.x, cube->max.x)),
        glm::max(cube->min.x, glm::min(center.x, cube->max.x)),
        glm::max(cube->min.x, glm::min(center.x, cube->max.x))
    };

    /*
    // Get Offset position to account for rotated AABB
    glm::vec3 pos
    {
        cube->position.x,
        (cube->position.y * cosf(cube->rotation_angle.x)) - (sphere->position.z * sinf(cube->rotation_angle.x)),
        (cube->position.y * sinf(cube->rotation_angle.x)) + (sphere->position.z * cosf(cube->rotation_angle.x))
    };

    // Calculate AABB info (center, half-extents)
    glm::vec3 aabb_half_extents(cube->size / 2.0f);
    glm::vec3 aabb_center(cube->position + aabb_half_extents);

    // Calculate Difference vector between both centers
    glm::vec3 difference = center - aabb_center;
    glm::vec3 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

    // Attach Clamped Value to AABB to get the point closest to circle
    glm::vec3 closest = clamped + aabb_center;

    // Calculate difference between Sphere Center and Closest point on AABB
    difference = closest - center;

    // Comparison Value
    float comparison = sphere->radius*2.0f;
    std::cout << glm::length(abs(difference)) << ", " << comparison << std::endl;
    */

    // Return If overlapping
    return glm::length(closest) > sphere->radius;
}