#pragma once
#include "RTRCube.h"
#include "RTRSphere.h"
class RTRPhysics
{
public:
	bool SphereOBB_Detection(RTRSphere* sphere, RTRCube* cubee);
	glm::vec3 SphereOBB_Resolution(RTRSphere* sphere, RTRCube* cube);
private:
	glm::vec3 ClosestPoint(RTRCube* obb, glm::vec3 point);
};