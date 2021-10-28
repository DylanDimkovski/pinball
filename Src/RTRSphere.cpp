#include "RTRSphere.h"
#include <iostream>

void RTRSphere::Init()
{
    size = { 0.275f, 0.275f, 0.275f };
    position = { 7.0f, -3.0f, 10.0f };
    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / size.x;    // normal
    float s, t;                                     // texCoord

    float sectorStep = (2 * glm::pi<float>()) / sectorCount;
    float stackStep = glm::pi<float>() / stackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i)
    {
        stackAngle = glm::pi<float>() / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = size.x * cosf(stackAngle);             // r * cos(u)
        z = size.x * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            vertices.insert(vertices.end(), {
                glm::vec3(x, y, z)
            });

            // normalized vertex normal
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            normals.push_back({ nx, ny, nz });

            // vertex tex coord between [0, 1]
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            texCoords.push_back({ s, t });
        }
    }

    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned int k1, k2;
    for (int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if (i != 0)
            {
                indices.insert(indices.end(), {
                    k1, k2, k1 + 1
                });
            }

            if (i != (stackCount - 1))
            {
                indices.insert(indices.end(), {
                    k1+1, k2, k2 + 1
                });
            }
        }
    }
    //textureID = texture->load_texture("Src/textures/ball/Marble012_4K_Color.png");
    RTRObject::Init();
}

void RTRSphere::End()
{
    std::vector<glm::vec3>().swap(normals);
    std::vector<glm::vec2>().swap(texCoords);
    RTRObject::End();
}