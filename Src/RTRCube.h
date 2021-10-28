#pragma once
#include "RTRObject.h"

class RTRCube : public RTRObject
{
public:
    RTRCube(glm::vec3 object_position, glm::vec3 object_size) : RTRObject() 
    {
        position = object_position;
        size = object_size;
    }
    ~RTRCube() {}
    virtual void Init();
    virtual const char* GetName() { return "RTRCube"; }

    float tex_scale = 10.0f;
};