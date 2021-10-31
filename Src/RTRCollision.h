#pragma once
#include <glm/ext.hpp>
#include <glad/glad.h>

#include "glm/gtx/string_cast.hpp"
#define GLM_ENABLE_EXPERIMENTAL
class RTRCollision 
{
public:
	RTRCollision(glm::vec3 position, glm::vec3 normal, glm::vec3 tangent, glm::vec3 reflection) 
	{
		this->position = position;
		this->normal = normal;
		this->tangent = tangent;
		this->reflection = reflection;
	};
	void tick(float delta) 
	{
		lifetime -= delta;
	};
	bool isDone()
	{
		return lifetime <= 0;
	};

	void debug(glm::mat4 projection, glm::mat4 view) 
	{
		glDisable(GL_CULL_FACE);
		glDisable(GL_TEXTURE);
		glUseProgram(0);
		glBindVertexArray(0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(projection));

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glm::value_ptr(view));

		glPushMatrix();

		glTranslatef(position.x, position.y, position.z);

		glBegin(GL_LINES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0, 0, 0);
		glVertex3fv(glm::value_ptr(normal* 1.5f));

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0, 0, 0);
		glVertex3fv(glm::value_ptr(tangent * 1.5f));

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0, 0, 0);
		glVertex3fv(glm::value_ptr(reflection * 1.5f));
		
		glEnd();
		glPopMatrix();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	float lifetime = 2.0f;
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 reflection;
};