#include "RTRMovement.h"

void RTRMovement::pitch(float angle)
{
    // keep track of how far we've gone around the axis
    pitch_delta += angle;

    // calculate the new forward vector
    forward = glm::normalize((forward * cosf(angle * 3.14159265359 / 180.0)) + (up * sinf(angle * 3.14159265359 / 180.0)));

    // calculate the new up vector
    up = glm::cross(forward, right);

    // invert so that positive goes down
    up *= -1;
}

void RTRMovement::yaw(float angle)
{
    // keep track of how far we've gone around this axis
    yaw_delta += angle;

    //re-calculate the new forward vector
    forward = glm::normalize((forward * cosf(angle * 3.14159265359 / 180.0)) - (right * sinf(angle * 3.14159265359 / 180.0)));

    //re-calculate the new right vector
    right = glm::cross(forward, up);
}

void RTRMovement::roll(float angle)
{
    // keep track of how far we've gone around this axis
    roll_delta += angle;

    // re-calculate the forward vector
    right = glm::normalize((right * cosf(angle * 3.14159265359 / 180.0) + (up * sinf(angle * 3.14159265359 / 180.0))));

    // re-calculate the up vector
    up = glm::cross(forward, right);

    // invert the up vector so positive points down
    up *= -1;
}
