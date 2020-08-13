#include "Terrain.h"

Terrain::Terrain(char* sprite, int width, int height, POS position)
	:GameObject(position)
{
	m_width = width;
	m_height = height;

	m_sprite = new char[m_width * m_height];
	memcpy(m_sprite, sprite, sizeof(char) * width * height);

	m_name = "Terrain";
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
