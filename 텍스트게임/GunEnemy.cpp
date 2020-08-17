#include "GunEnemy.h"
#include "Timer.h"
#include "Bullet.h"


GunEnemy::GunEnemy(POS position)
	:Enemy(position), m_Status(STATUS(10.f, 10.f, 10.f))
{/*
	wchar_t monsterImg2_LEFT[15] =
	{ '[',' ','@',' ','@',
	'[','r','-','0',' ',
	'[',' ',' ','0',' ' };
	//memcpy(m_sprite, monsterImg2_LEFT, sizeof(wchar_t) * m_width * m_height);

	wchar_t monsterImg2_RIGHT[15] =
	{ '@',' ','@',' ',']',
	' ','0','-','>',']',
	' ','0',' ',' ',']' };
	*/


	m_width = 2;
	m_height = 3;
	m_sprite = new wchar_t[m_width * m_height];
	memcpy(m_sprite, monsterImg2_LEFT, sizeof(wchar_t) * m_width * m_height);

	m_name = L"GuardEnemy";
	m_color = 4;
}

int GunEnemy::Update()
{

	if (m_dir) m_pos.x += Timer::DeltaTime() * 5;
	else  m_pos.x -= Timer::DeltaTime() * 5;

	m_MoveCount += Timer::DeltaTime();
	if (m_MoveCount > 3)
	{
		m_MoveCount = 0;
		m_dir = !m_dir;


		//	if(m_dir)memcpy(m_sprite, monsterImg2_RIGHT, sizeof(char) * m_width * m_height);
			//else memcpy(m_sprite, monsterImg2_LEFT, sizeof(char) * m_width * m_height);
	}





	if (m_Life)
		return 1;
	else
		return -1;

}


//오버라이딩
void GunEnemy::GetDamage(float damage, bool dir)
{

	//Knockback(bulletPos);
	printf("가드몬터맞음 %f ", m_Status.hp);
	m_Status.hp -= damage;
	if (m_Status.hp <= 0) m_Life = false;



}
