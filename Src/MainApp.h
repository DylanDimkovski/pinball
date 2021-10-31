//-----------------------------------------------------------------------------
// MainApp.h
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------
#pragma once
#include <unordered_set>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RTRTexture.h"
#include "RTRApp.h"
#include "RTRShader.h"
#include "RTRCamera.h"
#include "RTRLighting.h"
#include "RTRObject.h"
#include "RTRCube.h"
#include "RTRSphere.h"
#include "RTRSkybox.h"
#include "RTRPhysics.h"
#include "RTRPeg.h"
#include "RTRGrid.h"
#include "RTRCyclinder.h"
#include "Console.h"

class MainApp : public RTRApp
{
public:
    MainApp(const char* title, bool fullscreen = false, int width = 1024, int height = 768)
        : RTRApp(title, fullscreen, width, height) 
    { }
    int Init();
    void Done();
    bool Tick();

private:
    bool m_QuitApp{ false };
    bool m_Paused{ false };
    RTRShader* m_DefaultShader{ nullptr };
    RTRShader* m_SkyboxShader{ nullptr };
    RTRCamera* m_Camera{ nullptr };
    RTRLightingModel* m_LightingModel{ nullptr };
    RTRObject* m_Cube{ nullptr };
    RTRSkybox* m_SkyBox{ nullptr };
    RTRPhysics physics;
    RTRTexture* texture;
    RTRGrid* grid;
    RTRGrid* grid_ball;
    Console* m_Console{ nullptr };

    std::vector<RTRCollision*> collisions;

    float delta = 0.0f;

    float m_LeftFlipper = 0.0f;
    float m_RightFlipper = 0.0f;

    float m_FlipperMin = -120.0f;
    float m_FlipperMax = -45.0f;

    float m_FlipperSpeed = 7.0f;

    std::vector<RTRObject*> walls;
    std::vector<RTRObject*> balls;
    std::vector<RTRObject*> flippers;
    std::vector<RTRObject*> pogs;
    std::vector<RTRObject*> bumpers;
    std::vector<unsigned int> textures;

    bool m_LeftFlipperTurning{ false };
    bool m_RightFlipperTurning{ false };
    bool m_MovingForward{ false };
    bool m_MovingBackward{ false };
    bool m_TurningLeft{ false };
    bool m_TurningRight{ false };
    bool m_StrafingLeft{ false };
    bool m_StrafingRight{ false };
    bool m_TiltingUp{ false };
    bool m_TiltingDown{ false };
    bool m_AddBall{ false };
    bool m_SlowMo{ false };
    bool m_VelocityVector{ false };
    bool m_DebugBounding{ false };
    bool m_DebugCollisions{ false };
    bool m_DebugGrid{ false };

    unsigned int ball = 0;

    glm::mat4 m_ModelMatrix{ 1.0 };
    glm::mat4 m_ViewMatrix{ 1.0 };
    glm::mat4 m_ProjectionMatrix{ 1.0 };

    void CheckInput();

    void UpdateState();
    
    void UpdateTimeState();
    void UpdateCameraState();
    void UpdateBallState();
    void UpdateFlipperState(RTRObject* flipper, bool isTurning, float& flipperDelta, float flipperMin, float flipperMax);

    void RenderFrame();
    void add_ball();

    float Lerp(float a, float b, float t);
};
