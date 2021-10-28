#pragma once
#include <glm/ext.hpp>
#include "RTRObject.h"

void Transform(RTRObject* object);

void Transform(RTRObject* object, RTRObject* parent);

glm::mat4 Rotate_Child(RTRObject* child, RTRObject* parent);

void Rotate(RTRObject* object, float angle, glm::vec3 direction);

void Translate(RTRObject* object);

void Scale(RTRObject* object);
