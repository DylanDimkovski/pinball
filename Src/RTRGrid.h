#pragma once
#include <glm/ext.hpp>

#include <vector>
#include <unordered_set>

#include "RTRObject.h"
#include "RTRPhysics.h"
#include "RTRPeg.h"

struct node 
{
    std::vector<RTRObject*> objects;
    glm::vec3 pos;
    float size;
    int count;
    node(glm::vec3 pos, float size) : pos(pos), size(size) {};
};

class RTRGrid
{
public:

    ~RTRGrid();

    void init(float size, float divisions);
    void insert(RTRObject* object);
    
    void check_collision(RTRObject* object);
    void check_sphere_collision(RTRObject* object, std::vector<RTRCollision*>& collisions);
    void check_collision(RTRObject* object, RTRObject* parent);

    void debug(glm::mat4 projection, glm::mat4 view, std::vector<glm::vec3> &vertices);

    virtual const char* GetName() { return "RTRCube"; }

    std::vector<node*> grid;

    RTRPhysics physics;
};