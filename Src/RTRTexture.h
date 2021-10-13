#pragma once
#include <stb/stb_image.h>
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include "RTRShader.h"

class RTRTexture
{
public:
	//Texture
	unsigned int load_texture(char const* path);
	unsigned int load_skybox(std::vector<std::string> faces);
};