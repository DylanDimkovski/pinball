#pragma once
#include "RTRObject.h"

class RTRCube : public RTRObject
{
public:
    RTRCube(glm::vec3 object_position, glm::vec3 object_size, float object_angle) : RTRObject() 
    {
        position = object_position;
        size = object_size;
        rotation = { object_angle, object_angle, object_angle };
    }
    ~RTRCube() {}
    virtual void Init();
    virtual const char* GetName() { return "RTRCube"; }

    void set_texture();

    float tex_scale = 10.0f;
};