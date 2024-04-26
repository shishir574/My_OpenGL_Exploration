#include "texture.h"
#include<iostream>
using namespace std;

texture::texture()
{
	textureID = 0;
	width = 0;
	height = 0;
	bitdepth = 0;
	fileLocation = NULL;
}

texture::texture(char* fileLoc)
{
	textureID = 0;
	width = 0;
	height = 0;
	bitdepth = 0;
	fileLocation = fileLoc;
}

void texture::LoadTexture()
{
	unsigned char* texData = stbi_load(fileLocation,&width,&height,&bitdepth,STBI_rgb_alpha);
	if (!texData)
	{
		cout << "Failed to find tex data: " << fileLocation;
		return;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(texData);
}

void texture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void texture::ClearTexture()
{
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	bitdepth = 0;
	fileLocation = NULL;
}

texture::~texture()
{
	ClearTexture();
}
