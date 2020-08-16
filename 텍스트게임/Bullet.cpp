#include "Bullet.h"
#include"Timer.h"

Bullet::Bullet(bool charge, bool dir,float bulletDamage, POS position)
	:GameObject(position)
{
	m_chargeShoot = charge;
	m_bulletDamage = bulletDamage;
	printf("ÃÑ»ý¼ºµÊ");

	wchar_t bulletImg[4]= { L'-', L'-', L' ', L' ' };
	m_width = 2;
	m_height = 1;

	if (m_chargeShoot) {
		bulletImg[0] = { L'=' }; //{ L'=', L'=', L')', L')' };
		bulletImg[1] = { L'=' };
		bulletImg[2] = { L')' };
		bulletImg[3] = { L')' };
		m_width = 4;
		m_height = 1;
	}

	m_sprite = new wchar_t[m_width * m_height];
	memcpy(m_sprite, bulletImg, sizeof(wchar_t) * m_width * m_height);
	


	


	m_dir = dir;
	m_name = L"Bullet";

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
		m_Life = false;

	if (m_Life)
		return 1;
	else
		return -1;

}

int Bullet::LateUpdate()
{
	return 1;
}

