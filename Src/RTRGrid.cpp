#include "RTRGrid.h";

RTRGrid::~RTRGrid()
{
	for (auto i : grid)
		delete i;

	grid.clear();
}

void RTRGrid::init(float size, float divisions)
{
	float inner = size / (divisions * 2.0f);

	for (int x = -divisions; x <= divisions; x++)
	{
		for (int y = -divisions; y <= divisions; y++)
		{
			for (int z = -divisions; z <= divisions; z++)
			{
				grid.push_back(new node(glm::vec3(x * inner, y * inner, z * inner), inner));
			}
		}
	}
}

void RTRGrid::insert(RTRObject* object)
{
	float size = fmaxf(fmaxf(object->size.x, object->size.y), object->size.z);

	for (auto node : grid)
	{
		if (physics.BoxBox_Detection(node->pos, node->size / 2.0f, object->model_matrix[3], size / 2.0f))
		{
			node->objects.push_back(object);
			node->count = node->objects.size();
		}
	}                  
}

void RTRGrid::check_collision(RTRObject* object)
{
	std::unordered_set<RTRObject*> seen;
	float size = fmaxf(fmaxf(object->size.x, object->size.y), object->size.z);

	for (auto node : grid)
	{
		bool collides = false;

		if (node->count)
			collides = physics.BoxBox_Detection(node->pos, node->size / 2.0f, object->position, size);

		if (collides)
		{
			for (auto obj : node->objects)
			{
				if (obj != object && !seen.count(obj))
				{ 
					if (physics.SphereOBB_Detection((RTRSphere*)object, (RTRCube*)obj))
					{
						physics.SphereOBB_Resolution((RTRSphere*)object, (RTRCube*)obj);
						seen.insert(obj);
					}
				}
			}
		}
	}
}

void RTRGrid::check_collision(RTRObject* object, RTRObject* parent)
{
	std::unordered_set<RTRObject*> seen;
	float size = fmaxf(fmaxf(object->size.x, object->size.y), object->size.z);

	for (auto node : grid)
	{
		bool collides = false;

		if (node->count)
			collides = physics.BoxBox_Detection(node->pos, node->size / 2.0f, object->position, size);

		if (collides)
		{
			for (auto obj : node->objects)
			{
				if (obj != object && !seen.count(obj))
				{
					if (physics.SphereOBB_Detection((RTRSphere*)object, parent, (RTRCube*)obj))
					{
						physics.SphereOBB_Resolution((RTRSphere*)object, parent, obj);
						seen.insert(obj);
					}
				}
			}
		}
	}
}

void RTRGrid::check_sphere_collision(RTRObject* object, std::vector<RTRCollision*> &collisions)
{
	std::unordered_set<RTRObject*> seen;

	for (auto node : grid)
	{
		for (auto obj : node->objects)
		{
			if (obj != object && !seen.count(obj))
			{
				if (physics.SphereSphere_Detection(object, obj))
				{
					physics.SphereSphere_Resolution(object, obj, collisions);
					seen.insert(obj);
				}
			}
		}
	}
}

void RTRGrid::debug(glm::mat4 projection, glm::mat4 view, std::vector<glm::vec3> &vertices)
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

	for (auto node : grid)
	{
		if (node->objects.size() || true)
		{
			glPushMatrix();

			glColor3f(1.0f, 0.0f, 0.0f);

			glTranslatef(node->pos.x, node->pos.y, node->pos.z);
			glScalef(node->size, node->size, node->size);

			glBegin(GL_TRIANGLES);
			for (auto i : vertices)
			{
				glVertex3fv(glm::value_ptr(i));
			}
			glEnd();
			glPopMatrix();
		}
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
