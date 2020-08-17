#include "GuardEnemy.h"
#include "Timer.h"
#include "Bullet.h"
#include "RigidBody.h"
#include "BoxCollider.h"
#include "Guard.h"
GuardEnemy::GuardEnemy(POS position)
	:Enemy(position), m_Status(STATUS(10.f, 10.f, 10.f))
{

	m_width = 3;
	m_height = 3;
	m_sprite = new wchar_t[m_width * m_height];
	memcpy(m_sprite, monsterImg2_LEFT , sizeof(wchar_t) * m_width * m_height);

	m_name = L"GuardEnemy";
	m_color = 4;
	


}

int GuardEnemy::Update()
{

	if (m_dir) m_pos.x += Timer::DeltaTime() * 5;
	else  m_pos.x -= Timer::DeltaTime() * 5;

	m_MoveCount += Timer::DeltaTime();
	if (m_MoveCount > 3)
	{
		m_MoveCount = 0;
		m_dir = !m_dir;

	}


	if (m_Life)
		return 1;
	else
		return -1;

}



