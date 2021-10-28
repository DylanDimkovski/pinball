#pragma once
#include "RTRCube.h"
#include "RTRSphere.h"
#include "Transform.h"
class RTRPhysics
{
public:
	
	// Sphere OBB
	bool SphereOBB_Detection(RTRSphere* sphere, RTRCube* cube);
	bool SphereOBB_Detection(RTRSphere* sphere, RTRObject* parent, RTRCube* cubee);
	void SphereOBB_Resolution(RTRSphere* sphere, RTRCube* cube);
	void SphereOBB_Resolution(RTRSphere* sphere, RTRObject* parent, RTRCube* cube);

	bool SphereSphere_Detection(RTRObject* sphere1, RTRObject* sphere2);
	void SphereSphere_Resolution(RTRObject* sphere1, RTRObject* sphere2);


	glm::vec3 ClosestPoint(RTRCube* obb, glm::vec3 point);
	glm::vec3 ClosestPoint(RTRCube* obb, RTRObject* parent, glm::vec3 point);
	
};