//-----------------------------------------------------------------------------
// RTRObject.cpp
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------
#include <iostream>
#include "RTRObject.h"

// README / TODO - This is just a simple start.
// * For your assignment, think carefully about how Shaders, Materials and Objects will hang together.
// * Have a hierarchy of differnet object types (static object, moving object, hierarchical object, object with force, etc...
// * Don't worry too much about optimising the buffer handling by, for example, merging all objects into a single 
// vertex buffer. Or sorting object based on shader or material to minimize switches. Spend your time on more imprtant 
// optimisation techniques that will add marks - for example your uniform grid implementation. 
// * For this assignment you can hardcode the vertex buffers for the differnet shapes (see cube) and then 
// scale, place and animate them with transformation matrices.

//-----------------------------------------------------------------------------
void RTRObject::Init()
{
    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &m_FaceElementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_FaceElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void RTRObject::Render(RTRShader *shader)
{
    shader->SetMaterial("u_ObjectMaterial", m_Material);
    glBindVertexArray(m_VertexArray);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void RTRObject::End()
{
    glDeleteVertexArrays(1, &m_VertexArray); m_VertexArray = 0;
    glDeleteBuffers(1, &m_VertexBuffer); m_VertexBuffer = 0;
    glDeleteBuffers(1, &m_FaceElementBuffer); m_FaceElementBuffer = 0;
    std::vector<glm::vec3>().swap(vertices);
    std::vector<glm::vec3>().swap(normals);
    std::vector<unsigned int>().swap(indices);
    std::vector <float> ().swap(texCoords);
}