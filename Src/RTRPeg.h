#pragma once
#include "RTRObject.h"

class RTRPeg : public RTRObject
{
public:
    RTRPeg(glm::vec3 object_position, glm::vec3 object_size, float object_angle) : RTRObject()
    {
        position = object_position;
        size = object_size;
        rotation = { object_angle, object_angle, object_angle };
    }
    ~RTRPeg() {}
    virtual void Init();
    virtual void End();
    virtual const char* GetName() { return "RTRPeg"; }
};