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

    // If Distance is less than sphere size Then we have collision
    return sphere->distance < sphere->size.x;
}

bool RTRPhysics::SphereOBB_Detection(RTRSphere* sphere, RTRObject* parent, RTRCube* cube)
{
    // Get Closest Point on Cube
    glm::vec3 closest_point = ClosestPoint(cube, parent, sphere->position);

    // Find Distance Between Sphere and Closest Point
    sphere->distance = glm::length(sphere->position - closest_point);

    // If Distance is less than sphere size Then we have collision
    return sphere->distance < sphere->size.x;
}

void RTRPhysics::SphereOBB_Resolution(RTRSphere* sphere, RTRCube* cube)
{
    // Calculate Normal
    glm::vec3 closest_point = ClosestPoint(cube, sphere->position);
    glm::vec3 normal = glm::normalize(sphere->position - closest_point);

    glm::vec3 posRel = sphere->position - cube->position;
    glm::vec3 closeRel = closest_point - cube->position;
    glm::vec3 distance = closeRel - posRel;
    glm::vec3 direction = glm::normalize(distance);

    glm::vec3 mag = direction * sphere->size.x;
    float diff = glm::length(mag - distance);

    sphere->position -= diff * direction;

    // Calculate Reflection
    sphere->movement->velocity = glm::reflect(sphere->movement->velocity, normal) * 0.999f;
}

void RTRPhysics::SphereOBB_Resolution(RTRSphere* sphere, RTRObject* parent, RTRCube* cube)
{
    // Calculate Normal
    glm::vec3 cubePos = cube->model_matrix[3];
    glm::vec3 closest_point = ClosestPoint(cube, parent, sphere->position);
    glm::vec3 normal = glm::normalize(sphere->position - closest_point);

    glm::vec3 posRel = sphere->position - cubePos;
    glm::vec3 closeRel = closest_point - cubePos;
    glm::vec3 distance = closeRel - posRel;
    glm::vec3 direction = glm::normalize(distance);

    glm::vec3 mag = direction * sphere->size.x;
    float diff = glm::length(mag - distance);

    sphere->position -= diff * direction;

    // Calculate Reflection
    sphere->movement->velocity = glm::reflect(sphere->movement->velocity, normal) * 0.999f;
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

glm::vec3 RTRPhysics::ClosestPoint(RTRCube* obb, RTRObject* parent, glm::vec3 point) {

    // Initalize return and direction
    glm::vec3 result = obb->model_matrix[3];
    glm::vec3 dir = point - glm::vec3(obb->model_matrix[3]);

    glm::mat4 orientation = Rotate_Child(obb, parent);

    // Loop over Rotation Matrix and calculate closest point
    for (int i = 0; i < 3; ++i) {
        glm::vec3 axis(orientation[i][0], orientation[i][1], orientation[i][2]);

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
