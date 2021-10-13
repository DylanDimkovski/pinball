#include "RTRSkybox.h"

void RTRSkybox::init()
{
    setup_buffer();
    textureID = texture->load_skybox(faces);
}

void RTRSkybox::setup_buffer()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void RTRSkybox::draw(RTRCamera* camera, glm::mat4 projection, RTRShader* shader)
{
    // draw skybox as last
    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    glm::mat4 view = glm::mat4(glm::mat3(camera->GetViewMatrix()));
    shader->SetMat4("view", view);
    shader->SetMat4("projection", projection);
    // skybox cube
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default
}

void RTRSkybox::done()
{
    delete texture;
    faces.clear();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VAO);
}
