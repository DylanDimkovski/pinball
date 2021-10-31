#pragma once
#include "RTRCube.h"
#include "RTRSphere.h"
#include "Transform.h"
#include "RTRCollision.h"
class RTRPhysics
{
public:
	
	// Sphere OBB
	bool SphereOBB_Detection(RTRSphere* sphere, RTRCube* cube);
	bool SphereOBB_Detection(RTRSphere* sphere, RTRObject* parent, RTRCube* cubee);
	void SphereOBB_Resolution(RTRSphere* sphere, RTRCube* cube);
	void SphereOBB_Resolution(RTRSphere* sphere, RTRObject* parent, RTRCube* cube);
	void SphereOBB_Resolution(RTRSphere* sphere, RTRObject* parent, RTRObject* cube);

	bool SphereSphere_Detection(RTRObject* sphere1, RTRObject* sphere2);
	void SphereSphere_Resolution(RTRObject* sphere1, RTRObject* sphere2, std::vector<RTRCollision*> &collision);

	bool BoxBox_Detection(glm::vec3 p1, float s1, glm::vec3 p2, float s2);

	glm::vec3 ClosestPoint(RTRCube* obb, glm::vec3 point);
	glm::vec3 ClosestPoint(RTRCube* obb, RTRObject* parent, glm::vec3 point);
	glm::vec3 ClosestPoint(RTRObject* obb, RTRObject* parent, glm::vec3 point);
	
};