#include "Bullet.h"
#include"Timer.h"

Bullet::Bullet(bool dir, POS position)
	:GameObject(position)
{

	char bulletImg[2] = { '-','-' };

	m_width = 2;
	m_height = 1;
	m_sprite = new char[m_width * m_height];
	memcpy(m_sprite, bulletImg, sizeof(char) * m_width * m_height);

	m_dir = dir;
	m_name = "Bullet";

	m_color = 12;
}

Bullet::~Bullet()
{
}

int Bullet::Update()
{

	if (m_dir)
		m_pos.x += Timer::DeltaTime() * 10;
	else
		m_pos.x -= Timer::DeltaTime() * 10;


	m_timer += Timer::DeltaTime();

	if (m_timer >= 4.f)
		m_isAttacked = true;

	if (!m_isAttacked)
		return 1;
	else
		return -1;

}

int Bullet::LateUpdate()
{
	return 1;
}

