#include "Terrain.h"

Terrain::Terrain(wchar_t* sprite, int width, int height, POS position)
	:GameObject(position)
{
	m_width = width;
	m_height = height;

	m_sprite = new wchar_t[m_width * m_height];
	memcpy(m_sprite, sprite, sizeof(wchar_t) * width * height);

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
