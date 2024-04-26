#pragma once
#include<glew.h>
#include "stb_image.h"

class texture
{
private:
	GLuint textureID;
	int width, height, bitdepth;
	char* fileLocation;

public:
	texture();
	texture(char* fileLoc);

	void LoadTexture();
	void UseTexture();
	void ClearTexture();

	~texture();
};

