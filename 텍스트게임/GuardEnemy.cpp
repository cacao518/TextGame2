#include "GuardEnemy.h"
#include "Timer.h"
#include "Bullet.h"


GuardEnemy::GuardEnemy(POS position)
	:Enemy(position), m_Status(STATUS(10.f, 10.f, 0.1f))
{
	wchar_t monsterImg2[15] =
	{ '[',' ','@',' ','@',
	'[','r','-','0',' ',
	'[',' ',' ','0',' ' };

	m_width = 5;
	m_height = 3;
	m_sprite = new wchar_t[m_width * m_height];
	memcpy(m_sprite, monsterImg2, sizeof(wchar_t) * m_width * m_height);

	m_name = L"GuardEnemy";
	m_color = 4;
}


/*
GuardEnemy::~GuardEnemy()
{

}

int GuardEnemy::Update()
{
	if (m_dir) m_pos.x += Timer::DeltaTime() * 5;
	else  m_pos.x -= Timer::DeltaTime() * 5;

	m_MoveCount += Timer::DeltaTime();
	if (m_MoveCount > 1)
	{
		m_MoveCount = 0;
		m_dir = !m_dir;
	}




	/*
	m_timer += Timer::DeltaTime();
	bool isDie = false;
	if (m_timer >= 2.f)
		isDie = true;


		*/

		/*
			if (m_Life)
				return 1;
			else
				return -1;
		}

		int GuardEnemy::LateUpdate()
		{
			return 1;
		}




		void GuardEnemy::Knockback()
		{
			if (m_dir)
			{
				m_pos.x -= Timer::DeltaTime() * 10;
			}
			else
			{
				m_pos.x += Timer::DeltaTime() * 10;
			}
			m_pos.y -= Timer::DeltaTime() * 10;
		}
		*/