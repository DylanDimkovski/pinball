#define GLM_ENABLE_EXPERIMENTAL
#include "RTRPhysics.h"
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
    sphere->movement->velocity = glm::reflect(sphere->movement->velocity, normal) * 0.99999f;
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
    sphere->movement->velocity = glm::reflect(sphere->movement->velocity, normal) * 0.99999f;
}

void RTRPhysics::SphereOBB_Resolution(RTRSphere* sphere, RTRObject* parent, RTRObject* cube)
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
    if (cube->GetName() == "RTRCylinder" && cube->reflect == 0.6) 
    {
        sphere->movement->velocity = glm::reflect(sphere->movement->velocity, normal) * 1.11111;
    }
    else sphere->movement->velocity = glm::reflect(sphere->movement->velocity, normal) * 0.99999f;
}

bool RTRPhysics::SphereSphere_Detection(RTRObject* sphere1, RTRObject* sphere2)
{
    float radii_sum = sphere1->size.x + sphere2->size.x;
    float sq_distance = glm::length(sphere1->position - sphere2->position);
    return sq_distance < radii_sum * radii_sum;
}

void RTRPhysics::SphereSphere_Resolution(RTRObject* sphere1, RTRObject* sphere2, std::vector<RTRCollision*> &collisions)
{
    glm::vec3 nV = glm::normalize(sphere1->position - sphere2->position);
    glm::vec3 tV = glm::cross(nV, glm::vec3(-nV.y, nV.x, 0));
    glm::vec3 v1 = sphere1->movement->velocity;
    glm::vec3 v2 = sphere2->movement->velocity;

    glm::vec3 radii_sum = sphere1->size + sphere2->size;
    glm::vec3 distance = radii_sum - glm::length(sphere1->position - sphere2->position);
    
    sphere1->position -= glm::normalize(sphere1->position - sphere2->position) * distance;

    float n1 = glm::dot(v1, nV);
    float n2 = glm::dot(v2, nV);

    float t1 = glm::dot(v1, tV);
    float t2 = glm::dot(v2, tV);

    float m1 = 10;
    float m2 = 10;

    float M = m1 + m2;
    
    float N1 = (n1 * (m1 - m2) + 2.0f * m2 * n2) / M;
    float N2 = (n2 * (m2 - m1) + 2.0f * m1 * n1) / M;

    sphere1->movement->velocity = N1 * nV + t1 * tV;
    sphere2->movement->velocity = N2 * nV + t2 * tV;

    glm::vec3 pos = glm::normalize(sphere1->position - sphere2->position) * sphere1->size + sphere1->position;

    collisions.push_back(new RTRCollision(pos, nV, tV, glm::normalize(sphere1->movement->velocity)));
}

bool RTRPhysics::BoxBox_Detection(glm::vec3 p1, float s1, glm::vec3 p2, float s2)
{
    glm::vec3 p1Max = { p1.x + s1, p1.y + s1, p1.z + s1, };
    glm::vec3 p2Max = { p2.x + s2, p2.y + s2, p2.z + s2, };

    glm::vec3 p1Min = { p1.x - s1, p1.y - s1, p1.z - s1, };
    glm::vec3 p2Min = { p2.x - s2, p2.y - s2, p2.z - s2, };

    return (
        (p1Min.x <= p2Max.x && p1Max.x >= p2Min.x) &&
        (p1Min.y <= p2Max.y && p1Max.y >= p2Min.y) &&
        (p1Min.z <= p2Max.z && p1Max.z >= p2Min.z)
    );
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

glm::vec3 RTRPhysics::ClosestPoint(RTRObject* obb, RTRObject* parent, glm::vec3 point)
{
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
