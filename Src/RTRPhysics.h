#pragma once
#include "RTRCube.h"
#include "RTRSphere.h"
class RTRPhysics
{
public:
	bool check_collisionf(RTRCube* cube, RTRSphere* sphere);
private:
	glm::vec3 ClosestPoint(const RTRCube* obb, glm::vec3 point);
};