#include "Boss.h"

Boss::Boss(POS pos)
	:GameObject(pos),m_status(STATUS(0.f,0.f,0.f))
{
}

Boss::~Boss()
{
}

void Boss::GetDamage(float damage)
{
	m_status.hp -= damage;
	if (m_status.hp < 0)
		m_status.hp = 0;
}
