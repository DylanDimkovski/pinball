#pragma once
#include "RTRObject.h"

class RTRCyclinder : public RTRObject
{
public:
    RTRCyclinder(float sector, float stack, float height, glm::vec3 position, glm::vec3 size) : RTRObject()
    {
        this->sectorCount = sector;
        this->stackCount = stack;
        this->height = height;
        this->position = position;
        this->size = size;
    }
    ~RTRCyclinder() {}
    virtual void Init();
    virtual void End();
    virtual const char* GetName() { return "RTRCylinder"; }
    std::vector<float> getUnitCircleVerticies();
    std::vector<float> getSideNormals();
    void buildVerticiesSmooth();
    void debug(glm::mat4 projection, glm::mat4 view);


    float sectorCount;
    float stackCount;
    float height;
    float base_radius = 1.0f;
    float top_radius = 1.0f;
};