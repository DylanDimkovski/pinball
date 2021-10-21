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
    float sectorCount = 64.0f;
    float stackCount = 128.0f;
};