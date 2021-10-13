#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#include "RTRPhysics.h"
#include <iostream>

bool RTRPhysics::check_collisionf(RTRCube* cube, RTRSphere* sphere)
{
    // get center point circle first 
    glm::vec3 center(sphere->position + sphere->radius);
    // calculate AABB info (center, half-extents)
    glm::vec3 aabb_half_extents
    (
        5.0f, 
        (0.5f * cosf(glm::radians(8.15f))) - (10.0f * sinf(glm::radians(8.15f))),
        (0.5f * sinf(glm::radians(8.15f))) + (10.0f * cosf(glm::radians(8.15f)))
    );

    glm::vec3 aabb_center(
        aabb_half_extents.x,
        aabb_half_extents.y,
        aabb_half_extents.z
    );
    // get difference vector between both centers
    glm::vec3 difference = center - aabb_center;
    glm::vec3 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // add clamped value to AABB_center and we get the value of box closest to circle
    glm::vec3 closest = aabb_center + clamped;
    // retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - center;
    return glm::length(difference) < sphere->radius;
}