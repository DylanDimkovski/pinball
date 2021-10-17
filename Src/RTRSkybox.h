#pragma once
#pragma once
#include "RTRShader.h"
#include "RTRCamera.h"
#include "RTRObject.h"
#include <glad/glad.h>
#include <glm/ext.hpp>
#include <vector>
#include <string>
class RTRSkybox : public RTRObject
{
public:
    RTRSkybox() : RTRObject() {}
    ~RTRSkybox() {}
    virtual void Init();
    virtual void Render(RTRCamera* camera, glm::mat4 projection, RTRShader* shader);
    virtual void End();

    float skyboxVertices[108] = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    std::vector<std::string> faces
    {
        "D:/Uni Work/RealTimeGraphics/A2_SURNAME_FIRSTNAME/Src/skyboxs/skybox7/right.png",
        "D:/Uni Work/RealTimeGraphics/A2_SURNAME_FIRSTNAME/Src/skyboxs/skybox7/left.png",
        "D:/Uni Work/RealTimeGraphics/A2_SURNAME_FIRSTNAME/Src/skyboxs/skybox7/top.png",
        "D:/Uni Work/RealTimeGraphics/A2_SURNAME_FIRSTNAME/Src/skyboxs/skybox7/bottom.png",
        "D:/Uni Work/RealTimeGraphics/A2_SURNAME_FIRSTNAME/Src/skyboxs/skybox7/front.png",
        "D:/Uni Work/RealTimeGraphics/A2_SURNAME_FIRSTNAME/Src/skyboxs/skybox7/back.png"
    };
};