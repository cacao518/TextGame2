#include "GunEnemy.h"
#include "Timer.h"
#include "Bullet.h"

#include "BoxCollider.h"
#include "RigidBody.h"

#include "Player.h"
GunEnemy::GunEnemy(POS position)
	:Enemy(position), m_Status(STATUS(10.f, 10.f, 10.f))
{
	
	m_width = 2;
	m_height = 3;
	m_sprite = new wchar_t[m_width * m_height];
	memcpy(m_sprite, monsterImg2_LEFT, sizeof(wchar_t) * m_width * m_height);

	m_name = L"GunEnemy";
	m_color = 5;
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
	}

	DistanceCheck();



	if (m_Life)
		return 1;
	else
		return -1;

}

void GunEnemy::DistanceCheck()
{
	std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(ObjectMgr::GetInstance()->GetFrontObject(PLAYER));
	if (nullptr == player)
		return;
	//플레이어와 거리 비교
	float lenToPlayer, xDist, yDist;
	xDist = player->GetPos().x - m_pos.x;
	yDist = player->GetPos().y - m_pos.y;
	lenToPlayer = sqrtf(xDist * xDist + yDist * yDist);

	if (lenToPlayer <= 12.f  )
		Attack();


	if (player->GetPos().x > m_pos.x)
	{
		m_bulletDir = true;
		memcpy(m_sprite, monsterImg2_RIGHT, sizeof(wchar_t) * m_width * m_height);
	}
	else
	{
		m_bulletDir = false;
		memcpy(m_sprite, monsterImg2_LEFT, sizeof(wchar_t) * m_width * m_height);
	}
		



}

void GunEnemy::Attack()
{
		std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(true, false, Bullet::ENEMYBULLET, m_bulletDir , POS(GetPos().x , GetPos().y+1 ));
		ObjectMgr::GetInstance()->InsertObject(BULLET, std::dynamic_pointer_cast<GameObject>(bullet));
		BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(bullet));
		bullet->AddComponent(bc);
		bc->SetIsTrigger(true);
}



