#include "Bullet.h"
#include<iostream>

Bullet::Bullet(bool dir,POS position)
	:GameObject(position)
{
	
	char bulletImg[2] = { '0','0' };

	m_width = 2;
	m_height = 1;
	m_sprite = new char[m_width * m_height];
	memcpy(m_sprite, bulletImg, sizeof(char) * m_width * m_height);

	m_dir = dir;
	m_name = "Bullet";

}

Bullet::~Bullet()
{
}

int Bullet::Update()
{
	
	if(m_dir)
		m_pos.x += 0.1;
	else
		m_pos.x -= 0.1;

	return 1;
}

int Bullet::LateUpdate()
{
	return 1;
}

