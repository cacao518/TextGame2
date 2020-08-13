#include "Terrain.h"

Terrain::Terrain(char* sprite, int width, int height, POS position)
	:GameObject(position)
{
	this->width = width;
	this->height = height;

	this->sprite = new char[width * height];
	memcpy(this->sprite, sprite, sizeof(char) * width * height);
}
Terrain::~Terrain()
{

}

int Terrain::Update()
{
	return 1;
}

int Terrain::LateUpdate()
{
	return 1;
}
