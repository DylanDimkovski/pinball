#pragma once
#include <glm/ext.hpp>
#include <vector>

struct bounds 
{
    glm::vec3 start;
    glm::vec3 end;
};

class RTRGrid
{
public:
    RTRGrid() {}
    ~RTRGrid() {}
    void init();
    void insert();
    void remove();
    virtual const char* GetName() { return "RTRCube"; }

    std::vector<bounds> grid;
    float rows;
    float cols;
    float cell_size = 4.0f;
};