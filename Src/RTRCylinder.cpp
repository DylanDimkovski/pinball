#include "RTRCyclinder.h"


void RTRCyclinder::Init() 
{
    buildVerticiesSmooth();
    RTRObject::Init();
}

void RTRCyclinder::End()
{
    RTRObject::End();
}

void RTRCyclinder::buildVerticiesSmooth()
{

    // get unit circle vectors on XY-plane
    std::vector<float> unitVertices = getUnitCircleVerticies();

    std::vector<glm::vec3> v;
    std::vector<glm::vec3> n;
    std::vector<glm::vec2> tv;

    float radius;

    // put side vertices to arrays
    for (int i = 0; i < 2; ++i)
    {
        float h = -height / 2.0f + i * height;           // z value; -h/2 to h/2
        float t = 1.0f - i;                              // vertical tex coord; 1 to 0

        radius = base_radius + (float)i / stackCount * (top_radius - base_radius);

        for (int j = 0, k = 0; j <= sectorCount; ++j, k += 3)
        {
            float ux = unitVertices[k];
            float uy = unitVertices[k + 1];
            float uz = unitVertices[k + 2];

            v.push_back(glm::vec3(ux * radius, uy * radius, h));
            n.push_back(glm::vec3(ux, uy, uz));
            tv.push_back(glm::vec2((float)j / sectorCount, t));
        }
    }

    // the starting index for the base/top surface
    //NOTE: it is used for generating indices later
    int baseCenterIndex = (int)vertices.size() / 3;
    int topCenterIndex = baseCenterIndex + sectorCount + 1; // include center vertex

    // put vertices of base of cylinder
    float x = 0;
    float y = 0;
    float z = -height * 0.5f;

    v.push_back(glm::vec3(0, 0, z));
    n.push_back(glm::vec3(0, 0, -1));
    tv.push_back(glm::vec2(0.5f, 0.5f));

    for (int i = 0, j = 0; i < sectorCount; ++i, j += 3)
    {
        float x = unitVertices[j];
        float y = unitVertices[j + 1];

        v.push_back(glm::vec3(x * base_radius, y * base_radius, z));
        n.push_back(glm::vec3(0, 0, -1));
        tv.push_back(glm::vec2(-x * 0.5f + 0.5f, -y * 0.5f + 0.5f));    // flip horizontal
    }

    // remember where the base vertices start
    unsigned int topVertexIndex = (unsigned int)vertices.size() / 3;

    // put vertices of top of cylinder
    z = height * 0.5f;
    v.push_back(glm::vec3(0, 0, z));
    n.push_back(glm::vec3(0, 0, 1));
    tv.push_back(glm::vec2(0.5f, 0.5f));
    for (int i = 0, j = 0; i < sectorCount; ++i, j += 3)
    {
        x = unitVertices[j];
        y = unitVertices[j + 1];
        v.push_back(glm::vec3(x * top_radius, y * top_radius, z));
        n.push_back(glm::vec3(0, 0, 1));
        tv.push_back(glm::vec2(x * 0.5f + 0.5f, -y * 0.5f + 0.5f));
    }

    // generate CCW index list of cylinder triangles
    std::vector<int> indices;
    int k1 = 0;                         // 1st vertex index at base
    int k2 = sectorCount + 1;           // 1st vertex index at top

    // indices for the side surface
    for (int i = 0; i < sectorCount; ++i, ++k1, ++k2)
    {
        // 2 triangles per sector
        // k1 => k1+1 => k2
        indices.push_back(k1);
        indices.push_back(k1 + 1);
        indices.push_back(k2);

        // k2 => k1+1 => k2+1
        indices.push_back(k2);
        indices.push_back(k1 + 1);
        indices.push_back(k2 + 1);
    }

    // indices for the base surface
    //NOTE: baseCenterIndex and topCenterIndices are pre-computed during vertex generation
    //      please see the previous code snippet
    for (int i = 0, k = baseCenterIndex + 1; i < sectorCount; ++i, ++k)
    {
        if (i < sectorCount - 1)
        {
            indices.push_back(baseCenterIndex);
            indices.push_back(k + 1);
            indices.push_back(k);
        }
        else // last triangle
        {
            indices.push_back(baseCenterIndex);
            indices.push_back(baseCenterIndex + 1);
            indices.push_back(k);
        }
    }

    // indices for the top surface
    for (int i = 0, k = topCenterIndex + 1; i < sectorCount; ++i, ++k)
    {
        if (i < sectorCount - 1)
        {
            indices.push_back(topCenterIndex);
            indices.push_back(k);
            indices.push_back(k + 1);
        }
        else // last triangle
        {
            indices.push_back(topCenterIndex);
            indices.push_back(k);
            indices.push_back(topCenterIndex + 1);
        }
    }

    auto rotate = glm::mat3(glm::rotate(glm::identity<glm::mat4>(), glm::radians(45.0f), glm::vec3(0, 0, 1)));

    for (int i : indices)
    {
        vertices.push_back(rotate * v.at(i));
        normals.push_back(rotate * n.at(i));
        texCoords.push_back(glm::vec2(rotate * glm::vec3(tv.at(i), 1.0)));
    }
}

std::vector<float> RTRCyclinder::getUnitCircleVerticies()
{
    const float PI = 3.1415926f;
    float sectorStep = 2 * PI / sectorCount;
    float sectorAngle;  // radian

    std::vector<float> unitCircleVertices;
    for (int i = 0; i <= sectorCount; ++i)
    {
        sectorAngle = i * sectorStep;
        unitCircleVertices.push_back(cos(sectorAngle)); // x
        unitCircleVertices.push_back(sin(sectorAngle)); // y
        unitCircleVertices.push_back(0);                // z
    }
    return unitCircleVertices;
}

