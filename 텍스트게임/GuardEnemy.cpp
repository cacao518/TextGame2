#include "GuardEnemy.h"
#include "Timer.h"
#include "Bullet.h"
#include "RigidBody.h"
#include "BoxCollider.h"
#include "Guard.h"
GuardEnemy::GuardEnemy(POS position)
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

	
	//	if(m_dir)memcpy(m_sprite, monsterImg2_RIGHT, sizeof(char) * m_width * m_height);
		//else memcpy(m_sprite, monsterImg2_LEFT, sizeof(char) * m_width * m_height);
	}


	if (m_first)
	{

		m_first = false;
		std::shared_ptr<Guard> enemy10 = std::make_shared<Guard>(POS(m_pos.x - 2, m_pos.y));
		objectMgr->InsertObject(ENEMY, std::dynamic_pointer_cast<GameObject>(enemy10));

		RigidBody* rb10 = new RigidBody(std::dynamic_pointer_cast<GameObject>(enemy10));
		enemy10->AddComponent(rb10);
		BoxCollider* bc10 = new BoxCollider(std::dynamic_pointer_cast<GameObject>(enemy10));
		enemy10->AddComponent(bc10);
	}
	

	if (m_Life)
		return 1;
	else
		return -1;

}



