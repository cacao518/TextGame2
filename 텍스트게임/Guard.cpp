#include "GuardEnemy.h"
#include "Timer.h"
#include "Bullet.h"
#include "Guard.h"

Guard::Guard(POS position)
	:GuardEnemy(position), m_Status(STATUS(10.f, 10.f, 10.f))
{

	m_width = 2;
	m_height = 3;
	m_sprite = new wchar_t[m_width * m_height];
	memcpy(m_sprite, monsterImg2_LEFT, sizeof(wchar_t) * m_width * m_height);

	m_name = L"Guard";
	m_color = 5;
}



