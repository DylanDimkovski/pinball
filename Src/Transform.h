#pragma once
#include <glm/ext.hpp>

void Transform(RTRObject* object)
{
	object->model_matrix = object->orientation_matrix * object->translate_matrix * object->scale_matrix;
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
