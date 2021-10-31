//-----------------------------------------------------------------------------
// MainApp.cpp
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------
#include "MainApp.h"

#include "glm/gtx/string_cast.hpp"
#define GLM_ENABLE_EXPERIMENTAL

int MainApp::Init()
{
    if (int err = RTRApp::Init() != 0) {
        return err;
    }

    // Setup projection matrix and viewport transform. 
    // These won't need to change as we're not worrying about screen size changes for this assignment
    m_ProjectionMatrix = glm::perspective(glm::radians(60.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 100.0f);
    glViewport(0, 0, m_WindowWidth, m_WindowHeight);

    // Create two shaders
    // You might want to maintain a vector of all shaders you will use in your assignment
    m_DefaultShader = new RTRShader();
    if (m_DefaultShader->Load("D:/Uni Work/RealTimeGraphics/A2_SURNAME_FIRSTNAME/Src/RTRDefault.vert", "D:/Uni Work/RealTimeGraphics/A2_SURNAME_FIRSTNAME/Src/RTRDefault.frag", "D:/Uni Work/RealTimeGraphics/A2_SURNAME_FIRSTNAME/Src/RTRDefault.geom") != 0) {
        return -1;
    }

    // Create Skybox
    m_SkyboxShader = new RTRShader();
    if (m_SkyboxShader->Load("D:/Uni Work/RealTimeGraphics/A2_SURNAME_FIRSTNAME/Src/RTRSkybox.vert", "D:/Uni Work/RealTimeGraphics/A2_SURNAME_FIRSTNAME/Src/RTRSkybox.frag") != 0) {
        return -1;
    }

    textures.push_back(texture->load_texture("Src/textures/table/Wood066_4K_Color.png")); // Board
    textures.push_back(texture->load_texture("Src/textures/wall/Tiles093_4K_Color.png")); // Wall
    textures.push_back(texture->load_texture("Src/textures/ball/Marble012_4K_Color.png")); // Ball
    textures.push_back(texture->load_texture("Src/textures/peg/Plastic010_4K_Color.png")); // Peg
    textures.push_back(texture->load_texture("Src/textures/pog/Wood048_4K_Color.png")); // Pog
    textures.push_back(texture->load_texture("Src/textures/bump/Fabric051_4K_Color.png")); // Bumper

    // Create and initialise camera
    m_Camera = new RTRCamera(glm::vec3(0.0, 6.5, 23.70), glm::vec3(0.0, 1.0, 0.0));

    // Create and initialise lighting model
    m_LightingModel = new RTRLightingModel();

    // Point Light
    m_LightingModel->AddLight({
        .Type = RTRLightType::PointLight,
        .Ambient = glm::vec3(0.3, 0.3, 0.3),
        .Diffuse = glm::vec3(1.0, 1.0, 1.0),
        .Specular = glm::vec3(1.0, 1.0, 1.0),
        .Position = glm::vec3(3.0, 20.0, -2.0),
        .Constant = 1.0f,
        .Linear = 0.0f,
        .Quadratic = 0.0f
        });

    // Create Table Object
    m_Cube = new RTRCube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 1.0f, 15.0f));
    m_Cube->Init();
    m_Cube->textureID = textures.at(0);
    m_Cube->reflect = 0.2f;
    Scale(m_Cube);
    Rotate(m_Cube, glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Translate(m_Cube);
    Transform(m_Cube);

    // Create Walls
    // Bounds
    walls.push_back(new RTRCube(glm::vec3(0.0f, 2.0f, -14.0f), glm::vec3(8.0f, 1.0f, 1.0f))); // Top Wall 0
    walls.push_back(new RTRCube(glm::vec3(-9.0f, 2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 15.0f))); // Left Wall 1
    walls.push_back(new RTRCube(glm::vec3(9.0f, 2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 15.0f))); // Right Wall 2 
    walls.push_back(new RTRCube(glm::vec3(0.0f, 2.0, 14.0f), glm::vec3(8.0f, 1.0f, 1.0f))); // Bottom Wall 3

    // Launcher Area
    walls.push_back(new RTRCube(glm::vec3(5.0f, 2.0f, 5.0f), glm::vec3(1.0f, 1.0f, 8.0f))); // Divider 4

    // Backboard Area
    walls.push_back(new RTRCube(glm::vec3(-7.0f, 2.0f, -13.0f), glm::vec3(2.0f, 1.0f, 1.0f))); // Left Corner 5
    walls.push_back(new RTRCube(glm::vec3(7.0f, 2.0f, -13.0f), glm::vec3(2.0f, 1.0f, 1.0f))); // Right Corner 6

    // End Area
    walls.push_back(new RTRCube(glm::vec3(-6.0f, 2.0f, 11.5f), glm::vec3(2.0f, 1.0f, 0.5f))); // Left Wall 7
    walls.push_back(new RTRCube(glm::vec3(2.0f, 2.0f, 11.5f), glm::vec3(2.0f, 1.0f, 0.5f))); // Right Wall 8

    // Peg Area
    walls.push_back(new RTRCube(glm::vec3(-6.0f, 2.0f, 9.5f), glm::vec3(1.0f, 1.0f, 0.5f))); // Left Wall 9
    walls.push_back(new RTRCube(glm::vec3(2.0f, 2.0f, 9.5f), glm::vec3(1.0f, 1.0f, 0.5f))); // Right Wall 10


    // Y Axis Rotations
    Rotate(walls.at(5), glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Rotate(walls.at(6), glm::radians(-20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Rotate(walls.at(9), glm::radians(-20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Rotate(walls.at(10), glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    for (int i = 0; i < walls.size(); i++) 
    {
        walls.at(i)->Init();
        walls.at(i)->reflect = 0.3f;
        walls.at(i)->textureID = textures.at(1);
        Scale(walls.at(i));
        Translate(walls.at(i));
        Transform(walls.at(i), m_Cube);
    }

    // Add Flippers
    flippers.push_back(new RTRPeg(glm::vec3(-5.0f, 2.0f, 9.93f), glm::vec3(0.5f, 1.0f, 1.0f), glm::radians(-115.0f))); // Left
    flippers.push_back(new RTRPeg(glm::vec3(1.0f, 2.0f, 9.93f), glm::vec3(0.5f, 1.0f, 1.0f), glm::radians(115.0f))); // Right

    Rotate(flippers.at(0), flippers.at(0)->rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));
    Rotate(flippers.at(1), flippers.at(1)->rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));

    for (int i = 0; i < flippers.size(); i++)
    {
        flippers.at(i)->Init();
        flippers.at(i)->textureID = textures.at(3);
        Translate(flippers.at(i));
        Scale(flippers.at(i));
        Transform(flippers.at(i), m_Cube);
    }

    // Add Pogs
    pogs.push_back(new RTRCyclinder(38.0f, 8.0f, 8.0f, glm::vec3(0.0f, 1.0f, -8.0f), glm::vec3(0.5f, 0.5f, 0.5f)));
    pogs.push_back(new RTRCyclinder(38.0f, 8.0f, 8.0f, glm::vec3(-2.0f, 1.0f, -6.0f), glm::vec3(0.5f, 0.5f, 0.5f)));
    pogs.push_back(new RTRCyclinder(38.0f, 8.0f, 8.0f, glm::vec3(2.0f, 1.0f, -6.0f), glm::vec3(0.5f, 0.5f, 0.5f)));

    for (auto i : pogs) 
    {
        i->Init();
        i->textureID = textures.at(4);
        i->reflect = 0.3f;

        Translate(i);
        Rotate(i, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        Scale(i);
        Transform(i, m_Cube);
    }

    // Add Bumpers
    bumpers.push_back(new RTRCyclinder(38.0f, 8.0f, 8.0f, glm::vec3(-7.7f, 1.0f, -2.0f), glm::vec3(0.5f, 0.5f, 0.5f)));
    bumpers.push_back(new RTRCyclinder(38.0f, 8.0f, 8.0f, glm::vec3(3.7f, 1.0f, 4.0f), glm::vec3(0.5f, 0.5f, 0.5f)));

    for (auto i : bumpers)
    {
        i->Init();
        i->textureID = textures.at(5);
        i->reflect = 0.6f;

        Translate(i);
        Rotate(i, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        Scale(i);
        Transform(i, m_Cube);
    }


    // Create Uniform Grid -> walls/Flippers
    grid = new RTRGrid();
    grid->init(25.0f, 3.0f);

    for (auto flipper : flippers)
        grid->insert(flipper);

    for (auto wall : walls)
        grid->insert(wall);

    for (auto pog : pogs)
        grid->insert(pog);

    for (auto bump : bumpers)
        grid->insert(bump);

    // Create and initialise skybox
    m_SkyBox = new RTRSkybox();
    m_SkyBox->Init();

    // Create and initialise the debug console/overlay
    m_Console = new Console();
    m_Console->Init();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    return 0;
}

void MainApp::Done()
{
    m_Cube->End(); delete m_Cube;
    for (int i = 0; i < balls.size(); i++) 
    {
        balls.at(i)->End(); delete balls.at(i);
    }
    for (int i = 0; i < walls.size(); i++)
    {
        walls.at(i)->End(); delete walls.at(i);
    }
    for (auto flipper : flippers)
    {
        flipper->End(); 
        delete flipper;
    }

    for (auto pog : pogs) 
    {
        pog->End(); delete pog;
    }

    for (auto bump : bumpers)
    {
        bump->End(); delete bump;
    }

    m_Console->End(); delete m_Console;
    m_SkyBox->End(); delete m_SkyBox;
    delete m_DefaultShader;
    delete m_SkyboxShader;
    RTRApp::Done();
}

bool MainApp::Tick()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_QuitApp = false;
    CheckInput();
    
    UpdateTimeState();
    UpdateCameraState();
    
    if (!m_Paused)
        UpdateState();
    
    RenderFrame();

    if (m_DebugGrid)
        grid->debug(m_ProjectionMatrix, m_ViewMatrix, m_Cube->vertices);
    
    for (auto ball : balls) 
    {
        if (m_VelocityVector) 
        {
            ((RTRSphere*) ball)->debug(m_ProjectionMatrix, m_ViewMatrix);
        }
    }

    if (m_DebugBounding)
    {
        m_Cube->debug(m_ProjectionMatrix, m_ViewMatrix);

        for (auto wall : walls)
        {
            wall->debug(m_ProjectionMatrix, m_ViewMatrix);
        }

        for (auto ball : balls)
        {
            ball->debug(m_ProjectionMatrix, m_ViewMatrix);
        }

        for (auto flip : flippers)
        {
            flip->debug(m_ProjectionMatrix, m_ViewMatrix);
        }
    }

    for (int i = 0; i < collisions.size(); i++) 
    {
        auto collide = collisions.at(i);
        if (!m_Paused) 
        {
            collide->tick(delta);
        }
        if (m_DebugCollisions) 
        {
            collide->debug(m_ProjectionMatrix, m_ViewMatrix);
        }

        if (collide->isDone()) 
        {
            delete collide;
            collisions.erase(collisions.begin() + i);
        }
    }

    return m_QuitApp;
}

// TODO: Add MOUSE support for looking around.
// TODO: Might move all this as "core" functionality in RTRApp class.
void MainApp::CheckInput()
{
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT: m_QuitApp = true; break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE: m_QuitApp = true; break;
                    case SDLK_w: m_MovingForward = true; break;
                    case SDLK_s: m_MovingBackward = true; break;
                    case SDLK_a: m_StrafingLeft = true; break;
                    case SDLK_d: m_StrafingRight = true; break;
                    case SDLK_LEFT: m_TurningLeft = true; break;
                    case SDLK_RIGHT: m_TurningRight = true; break;
                    case SDLK_UP: m_TiltingUp = true; break;
                    case SDLK_DOWN: m_TiltingDown = true; break;
                    case SDLK_SPACE: m_Paused = !m_Paused; break;
                    case SDLK_RETURN: add_ball(); break;
                    case SDLK_COMMA: m_LeftFlipperTurning = true; break;
                    case SDLK_PERIOD: m_RightFlipperTurning = true; break;
                    case SDLK_LSHIFT: m_SlowMo = true; break;   
                }
                break;
            case SDL_KEYUP:
                switch (e.key.keysym.sym) {
                    case SDLK_w: m_MovingForward = false; break;
                    case SDLK_s: m_MovingBackward = false; break;
                    case SDLK_a: m_StrafingLeft = false; break;
                    case SDLK_d: m_StrafingRight = false; break;
                    case SDLK_LEFT: m_TurningLeft = false; break;
                    case SDLK_RIGHT: m_TurningRight = false; break;
                    case SDLK_UP: m_TiltingUp = false; break;
                    case SDLK_DOWN: m_TiltingDown = false; break;
                    case SDLK_RETURN: m_AddBall = false; break;
                    case SDLK_COMMA: m_LeftFlipperTurning = false; break;
                    case SDLK_PERIOD: m_RightFlipperTurning = false; break;
                    case SDLK_LSHIFT: m_SlowMo = false; break;
                    case SDLK_z: m_DebugGrid = !m_DebugGrid; break;
                    case SDLK_x: m_VelocityVector = !m_VelocityVector; break;
                    case SDLK_c: m_DebugBounding = !m_DebugBounding; break;
                    case SDLK_v: m_DebugCollisions = !m_DebugCollisions; break;
                }
                break;
        }
    }
}

void MainApp::UpdateState()
{
    UpdateFlipperState(flippers.at(0), m_LeftFlipperTurning, m_LeftFlipper, m_FlipperMin, m_FlipperMax);
    UpdateFlipperState(flippers.at(1), m_RightFlipperTurning, m_RightFlipper, -m_FlipperMin, -m_FlipperMax);

    UpdateBallState();
}

void MainApp::UpdateTimeState()
{
    delta = m_TimeDelta / 1000.0f;

    if (m_SlowMo)
        delta /= 16.0f;
}

void MainApp::UpdateCameraState()
{
    // Update camera position based on keybard state checked earlier and saved
    if (m_MovingForward)  m_Camera->MoveForward(m_TimeDelta);
    if (m_MovingBackward) m_Camera->MoveBackward(m_TimeDelta);
    if (m_TurningLeft)    m_Camera->TurnLeft(m_TimeDelta);
    if (m_TurningRight)   m_Camera->TurnRight(m_TimeDelta);
    if (m_StrafingLeft)   m_Camera->StrafeLeft(m_TimeDelta);
    if (m_StrafingRight)  m_Camera->StrafeRight(m_TimeDelta);
    if (m_TiltingUp)      m_Camera->TiltUp(m_TimeDelta);
    if (m_TiltingDown)    m_Camera->TiltDown(m_TimeDelta);

    // Update directional camera to align with camera forward direction
    m_LightingModel->GetLight(0)->Direction = m_Camera->m_Front;

    // Setup Model and View matrices
    m_ViewMatrix = m_Camera->GetViewMatrix();
}

void MainApp::UpdateBallState()
{
    // Reinit Grid
    delete grid_ball;
    grid_ball = new RTRGrid();
    grid_ball->init(25.0f, 3.0f);
    for (auto ball : balls)
        grid_ball->insert(ball);

    delete grid;
    grid = new RTRGrid();
    grid->init(25.0f, 3.0f);

    for (auto flipper : flippers)
        grid->insert(flipper);

    for (auto wall : walls)
        grid->insert(wall);

    for (auto pog : pogs)
        grid->insert(pog);

    for (auto bump : bumpers)
        grid->insert(bump);

    // Check Collisions
    for (int i = 0; i < balls.size(); i++)
    {
        RTRObject* ball = balls.at(i);

        // Apply Velocity to Ball
        ball->movement->velocity += ball->movement->gravity * delta;
        ball->position += ball->movement->velocity * delta;

        // Check Ball Collision with Floor
        if (physics.SphereOBB_Detection((RTRSphere*)ball, (RTRCube*)m_Cube))
        {
            physics.SphereOBB_Resolution((RTRSphere*)ball, (RTRCube*)m_Cube);
        }

        // Uniform Grid Collision
        grid->check_collision(ball, m_Cube);
        grid_ball->check_sphere_collision(ball, collisions);

        if (ball->position.y < -25.0f)
        {
            delete ball;
            balls.erase(balls.begin() + i);
        }
    }
}

void MainApp::UpdateFlipperState(RTRObject* flipper, bool isTurning, float &flipperDelta, float flipperMin, float flipperMax)
{
    float speed = delta * m_FlipperSpeed;

    flipperDelta += isTurning ? speed : -speed;
    flipperDelta = glm::clamp(flipperDelta, 0.0f, 1.0f);

    SetRotation(flipper, glm::radians(Lerp(flipperMin, flipperMax, flipperDelta)), glm::vec3(0.0f, 1.0f, 0.0f));
    Transform(flipper, m_Cube);

    std::cout.precision(17);
}

void MainApp::RenderFrame()
{
    // Render the shaded cube using the default blinn-phong shader
    glUseProgram(m_DefaultShader->GetId());
    m_DefaultShader->SetFloat("u_CurTime", (float)m_CurTime);
    m_DefaultShader->SetFloat("u_TimeDelta", (float)m_TimeDelta);
    m_DefaultShader->SetMat4("u_ViewMatrix", m_ViewMatrix);
    m_DefaultShader->SetMat4("u_ProjectionMatrix", m_ProjectionMatrix);
    m_DefaultShader->SetCamera("u_Camera", *m_Camera);
    m_DefaultShader->SetLightingModel(*m_LightingModel);
    m_DefaultShader->SetMat4("u_ModelMatrix", m_Cube->model_matrix);
    m_DefaultShader->SetInt("u_SkyBox", 0);
    m_DefaultShader->SetFloat("u_Reflect", m_Cube->reflect);
    m_Cube->Render(m_DefaultShader);

    // Render Walls
    for (int i = 0; i < walls.size(); i++) 
    {
        walls.at(i)->reflect = 0.2f;
        m_DefaultShader->SetMat4("u_ModelMatrix", walls.at(i)->model_matrix);
        m_DefaultShader->SetFloat("u_Reflect", walls.at(i)->reflect);
        walls.at(i)->Render(m_DefaultShader);
    }

    // Render Balls
    for (int i = 0; i < balls.size(); i++) 
    {
        balls.at(i)->model_matrix = glm::translate(m_ModelMatrix, balls.at(i)->position);
        m_DefaultShader->SetMat4("u_ModelMatrix", balls.at(i)->model_matrix);
        m_DefaultShader->SetFloat("u_Reflect", balls.at(i)->reflect);
        balls.at(i)->Render(m_DefaultShader);
    }

    // Render Pegs
    for (auto flipper : flippers) 
    {
        m_DefaultShader->SetMat4("u_ModelMatrix", flipper->model_matrix);
        m_DefaultShader->SetFloat("u_Reflect", flipper->reflect);
        flipper->Render(m_DefaultShader);
    }

    // Render Pogs
    for (auto pog : pogs) 
    {
        m_DefaultShader->SetMat4("u_ModelMatrix", pog->model_matrix);
        m_DefaultShader->SetFloat("u_Reflect", pog->reflect);
        pog->Render(m_DefaultShader);
    }

    // Render Bumpers
    for (auto bump : bumpers)
    {
        m_DefaultShader->SetMat4("u_ModelMatrix", bump->model_matrix);
        m_DefaultShader->SetFloat("u_Reflect", bump->reflect);
        bump->Render(m_DefaultShader);
    }

    // Skybox
    glUseProgram(m_SkyboxShader->GetId());
    m_SkyboxShader->SetInt("skybox", 0);
    m_SkyBox->Render(m_Camera, m_ProjectionMatrix, m_SkyboxShader);
    
    // Print out all debug info
    m_Console->Render("DEBUG", m_FPS,
        m_Camera->m_Position.x, m_Camera->m_Position.y, m_Camera->m_Position.z,
        m_Camera->m_Yaw, m_Camera->m_Pitch, m_Paused, balls.size());
}

void MainApp::add_ball()
{
    if (m_Paused != true) 
    {
        RTRObject* m_Sphere = new RTRSphere();
        m_Sphere->Init();
        m_Sphere->textureID = textures.at(2);
        m_Sphere->reflect = 0.5f;
        m_Sphere->movement->velocity = glm::mat3(m_Cube->orientation_matrix) * glm::vec3(0.0f, 0.0f, -50.0f);
        balls.push_back(m_Sphere);
    }
}

float MainApp::Lerp(float a, float b, float t)
{
    return (1.0f - t) * a + t * b;
}

//-----------------------------------------------------------------------------
static const char* MAIN_WINDOW_TITLE = "RMIT COSC1226: Real-Time Rendering";
int main(int argc, char** argv)
{
    MainApp* app = new MainApp(MAIN_WINDOW_TITLE, false, 1920, 1080);
    if (int err = app->Init() != 0) {
        std::cout << "RTR:ERROR: Failed to initialise application. Please see error messages for details..." << std::endl;
        return -1;
    };
    app->Run();
    app->Done();
    return 0;
}


void Create_World_Objects() 
{
    
}
