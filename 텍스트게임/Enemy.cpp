#include "Enemy.h"
#include "Timer.h"
#include "Bullet.h"
#include "Timer.h"

Enemy::Enemy(POS position)
	:GameObject(position)
{


	char monsterImg[4] = { '*', '*', 'M', 'M' };

	m_width = 2;
	m_height = 2;
	m_sprite = new char[m_width * m_height];
	memcpy(m_sprite, monsterImg, sizeof(char) * m_width * m_height);

	m_name = "Enemy";
}

Enemy::~Enemy()
{

}

int Enemy::Update()
{
	if (m_dir) m_pos.x += Timer::DeltaTime() * 5;
	else  m_pos.x -= Timer::DeltaTime() * 5;

	m_MoveCount+= Timer::DeltaTime();
	if (m_MoveCount > 1 )
	{
		m_MoveCount =0;
		m_dir = !m_dir;
	}

	/*
	m_timer += Timer::DeltaTime();
	bool isDie = false;
	if (m_timer >= 2.f)
		isDie = true;


		*/
	if (!m_isAttacked)
		return 1;
	else
		return -1;
}

int Enemy::LateUpdate()
{
	return 1;
}
