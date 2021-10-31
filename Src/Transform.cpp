#include "Transform.h"

void Transform(RTRObject* object)
{
	object->model_matrix = (object->translate_matrix * object->orientation_matrix * object->scale_matrix);
}

void Transform(RTRObject* object, RTRObject* parent)
{
	object->model_matrix = (parent->translate_matrix * parent->orientation_matrix) * (object->translate_matrix * object->orientation_matrix * object->scale_matrix);
}

glm::mat4 Rotate_Child(RTRObject* child, RTRObject* parent)
{
	return parent->orientation_matrix * child->orientation_matrix;
}

void SetRotation(RTRObject* object, float angle, glm::vec3 direction)
{
	object->orientation_matrix = glm::rotate(glm::identity<glm::mat4>(), angle, direction);
}

void Rotate(RTRObject* object, float angle, glm::vec3 direction)
{
	object->orientation_matrix = glm::rotate(object->orientation_matrix, angle, direction);
}

void Translate(RTRObject* object)
{
	object->translate_matrix = glm::translate(object->translate_matrix, object->position);
};

void Scale(RTRObject* object)
{
	object->scale_matrix = glm::scale(object->scale_matrix, object->size);
};
