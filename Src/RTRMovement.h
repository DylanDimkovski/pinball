#pragma once
#include <glm/ext.hpp>
class RTRMovement
{
public:
    RTRMovement() {}
    ~RTRMovement() {}

    void pitch(float angle);
    void roll(float angle);
    void yaw(float angle);

    glm::vec3 velocity = {0.0f, 0.0f, 0.0f};
    glm::vec3 initial_velocity{ 0.0f };
    glm::vec3 force = { 0.0f, 0.0f, 0.0f };
    glm::vec3 forward = { 0.0f, 0.0f, 0.0f };
    glm::vec3 front = { 0.0f, 0.0f, 0.0f };
    glm::vec3 right = { 0.0f, 0.0f, 0.0f };
    glm::vec3 up = { 0.0f, 0.0f, 0.0f };

    float pitch_delta = 0;
    float roll_delta = 0;
    float yaw_delta = 0;

    float gravity = 0;
    float friction = 0;
};
