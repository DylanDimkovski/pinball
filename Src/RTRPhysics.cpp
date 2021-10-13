#include "RTRPhysics.h"
#include <iostream>
#include <cmath>

bool RTRPhysics::check_collisionf(RTRCube* cube, RTRSphere* sphere)
{
    glm::vec3 point
    {
        cube->position.x,
        cube->position.y*0.5f*(((cube->position.y) * cos(cube->rotation_angle.x)) - ((cube->position.z) * sin(cube->rotation_angle.x))),
        cube->position.z
    };
    
    return point.y > (sphere->position.y + sphere->radius);
}


//cube->position.x + aabb_half_extents.x,
//((cube->position.y / 2.0f) * cos(cube->rotation_angle.x)) - ((cube->position.z / 2.0f) * sin(cube->rotation_angle.x)) + aabb_half_extents.y,
//((cube->position.y / 2.0f) * sin(cube->rotation_angle.x)) + ((cube->position.z / 2.0f) * cos(cube->rotation_angle.x)) + aabb_half_extents.z