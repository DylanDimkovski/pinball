#pragma once
#include "RTRCube.h"
#include "RTRSphere.h"
#include "Transform.h"
class RTRPhysics
{
public:
	
	bool SphereOBB_Detection(RTRSphere* sphere, RTRCube* cubee);
	bool SphereOBB_Detection(RTRSphere* sphere, RTRObject* parent, RTRCube* cubee);

	void SphereOBB_Resolution(RTRSphere* sphere, RTRCube* cube);
	void SphereOBB_Resolution(RTRSphere* sphere, RTRObject* parent, RTRCube* cube);

	glm::vec3 ClosestPoint(RTRCube* obb, glm::vec3 point);
	glm::vec3 ClosestPoint(RTRCube* obb, RTRObject* parent, glm::vec3 point);
	
};