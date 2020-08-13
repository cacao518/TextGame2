#include "Terrain.h"

Terrain::Terrain(char* sprite, int width, int height, POS position)
	:GameObject(sprite, width, height, position)
{

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
