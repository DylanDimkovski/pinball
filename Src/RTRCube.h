#pragma once
#include "RTRObject.h"

class RTRCube : public RTRObject
{
public:
    RTRCube() : RTRObject() {}
    ~RTRCube() {}
    virtual void Init();
    virtual const char* GetName() { return "RTRCube"; }
};