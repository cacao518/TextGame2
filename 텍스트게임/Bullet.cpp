#include "Bullet.h"
#include"Timer.h"
#include"BoxCollider.h"
#include "Enemy.h"
#include "GameMgr.h"
#include "Boss.h"
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

	auto otherObj = GetComponent<BoxCollider>()->OnTriggerEnter(L"Enemy");
	if (otherObj != nullptr )
	{
		//obj2->SetIsAttacked(true);
		//obj1->SetIsAttacked(true);

		std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(otherObj);
		enemy->SetHp(m_bulletDamage);
		enemy->Knockback();
		GameMgr::GetInstance()->SetEnemy(enemy);
		SetIsLife(false);
		
	}
	
	auto bossObj = GetComponent<BoxCollider>()->OnTriggerEnter(L"Boss");
	if (bossObj != nullptr)
	{
		std::shared_ptr<Boss> boss = std::dynamic_pointer_cast<Boss>(bossObj);
		GameMgr::GetInstance()->SetBoss(boss);
		SetIsLife(false);
	}

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

