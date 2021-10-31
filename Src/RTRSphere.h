#pragma once
#include "RTRObject.h"

class RTRSphere : public RTRObject
{
public:
    RTRSphere() : RTRObject() {}
    ~RTRSphere() {}
    virtual void Init();
    virtual void End();
    virtual const char* GetName() { return "RTRSphere"; }
    void debug(glm::mat4 projection, glm::mat4 view);
    float sectorCount = 64.0f;
    float stackCount = 128.0f;
};