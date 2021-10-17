#include "RTRSkybox.h"

void RTRSkybox::Init()
{
    glGenVertexArrays(1, &m_VertexArray);
    glGenBuffers(1, &m_VertexBuffer);
    glBindVertexArray(m_VertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    textureID = texture->load_skybox(faces);
}

void RTRSkybox::Render(RTRCamera* camera, glm::mat4 projection, RTRShader* shader)
{
    // draw skybox as last
    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    glm::mat4 view = glm::mat4(glm::mat3(camera->GetViewMatrix()));
    shader->SetMat4("view", view);
    shader->SetMat4("projection", projection);
    // skybox cube
    glBindVertexArray(m_VertexArray);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default
}

void RTRSkybox::End()
{
    std::vector<std::string>().swap(faces);
    RTRObject::End();
}
