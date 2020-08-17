#include "Bullet.h"
#include"Timer.h"
#include"BoxCollider.h"
#include "Enemy.h"
#include "GuardEnemy.h"
#include "GameMgr.h"
#include "Boss.h"
#include "Player.h"
#include "Bullet.h"
#include "RigidBody.h"
#include "Guard.h"

Bullet::Bullet(bool isEnemy, bool charge, int BulletType, bool dir, POS position)
	:GameObject(position), m_isEnemy(isEnemy), m_bulletDamage(0.f), m_timer(0.f),m_bulletType((OBJTYPE)BulletType)
{
	m_chargeShoot = charge;
	printf("ÃÑ»ý¼ºµÊ");

	wchar_t Default[2]= { L'-', L'-'};
	wchar_t ChargeDefault[4] = { L'=', L'=',L')',L')' };
	wchar_t MachineGun[2] = { L'=', L'=' };
	wchar_t ChargeMachineGun[5] = { L'=', L'=',L')',L')',L')' };
	wchar_t boombImg[2] = { L'0',L'0' };

	wchar_t cannonImg[9] = { L'o',L'O',L'o',L'O',L'O',L'O',L'o',L'O',L'o' };

	if (BulletType == HANDGUN)
	{
		
	
		m_bulletDamage = 3;
		m_width = 2;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		ZeroMemory(m_sprite, sizeof(wchar_t) * m_width * m_height);

		memcpy(m_sprite, Default, sizeof(wchar_t) * m_width * m_height);
		m_color = 12;

		
		
		
	}
	if (BulletType == HANDGUN && m_chargeShoot)
	{
		m_bulletDamage = 5;
		m_width = 4;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		ZeroMemory(m_sprite, sizeof(wchar_t) * m_width * m_height);

		memcpy(m_sprite, ChargeDefault, sizeof(wchar_t) * m_width * m_height);
		m_color = 12;
	}
	if (BulletType == TANKGUN)
	{
		m_bulletDamage = 4;
		m_width = 2;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		ZeroMemory(m_sprite, sizeof(wchar_t) * m_width * m_height);

		memcpy(m_sprite, MachineGun, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTCYAN;
	}
	if (BulletType == TANKGUN && m_chargeShoot)
	{
		m_bulletDamage = 6;
		m_width = 5;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		ZeroMemory(m_sprite, sizeof(wchar_t) * m_width * m_height);

		memcpy(m_sprite, ChargeMachineGun, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTCYAN;
	}
	if (BulletType == HEABYGUN)
	{
		m_bulletDamage = 4;
		m_width = 2;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		ZeroMemory(m_sprite, sizeof(wchar_t) * m_width * m_height);

		memcpy(m_sprite, MachineGun, sizeof(wchar_t) * m_width * m_height);
		m_color = YELLOW;
	}
	if (BulletType == HEABYGUN && m_chargeShoot)
	{
		m_bulletDamage = 6;
		m_width = 5;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		ZeroMemory(m_sprite, sizeof(wchar_t) * m_width * m_height);

		memcpy(m_sprite, ChargeMachineGun, sizeof(wchar_t) * m_width * m_height);
		m_color = YELLOW;
	}
	if (BulletType == BOSS_CANNON)
	{
		m_bulletDamage = 40.f;
		m_width = 3;
		m_height = 3;
		m_sprite = new wchar_t[m_width * m_height];
		ZeroMemory(m_sprite, sizeof(wchar_t) * m_width * m_height);
		memcpy(m_sprite, cannonImg, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTRED;
	}

	if (BulletType == BOOMB)
	{
		m_bulletSpeed = 4.f;
		boombStep = 1;
		m_bulletDamage = 10.f;
		m_width = 2;
		m_height = 1;
		m_sprite = new wchar_t[m_width* m_height];
		memcpy(m_sprite, boombImg, sizeof(wchar_t) * m_width * m_height);
		m_color = 12;

	}
	m_dir = dir;
	m_name = L"Bullet";
}

Bullet::~Bullet()
{
}

int Bullet::Update()
{
	

	if (!m_isEnemy)
	{
		auto EnemyObj = GetComponent<BoxCollider>()->OnTriggerEnter(L"Enemy");
		if (EnemyObj != nullptr)
		{
			//obj2->SetIsAttacked(true);
			//obj1->SetIsAttacked(true);
			


			if (EnemyObj->GetName() == L"Guard")
			{

				printf("°¡µå¸ÂÀ½");
				SetIsLife(false);
			}

		 else
			{
				std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(EnemyObj);

				if (EnemyObj->GetName() == L"GuardEnemy")
				enemy->GetDamage(m_bulletDamage, GetPos(),false);
				else
				enemy->GetDamage(m_bulletDamage, GetPos(), true);

				GameMgr::GetInstance()->SetEnemy(enemy);
				SetIsLife(false);
			}
			
		
		
			
		}


		auto bossObj = GetComponent<BoxCollider>()->OnTriggerEnter(L"Boss");
		if (bossObj != nullptr)
		{
			std::shared_ptr<Boss> boss = std::dynamic_pointer_cast<Boss>(bossObj);
			GameMgr::GetInstance()->SetBoss(boss);
			SetIsLife(false);
		}
	}
	else
	{
		auto playerObj = GetComponent<BoxCollider>()->OnTriggerEnter(L"Player");
		if (playerObj != nullptr)
		{
			std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(playerObj);
			player->GetDamage(m_bulletDamage, m_pos);
			SetIsLife(false);
		}
	}
	
	if (boombStep == 1) {

		GetComponent<RigidBody>()->AddForce(0, 3);
		boombStep = 2;
	}
	if (boombStep == 2 && (GetIsLand() && GetComponent<RigidBody>()->gravitySpeed <= 0))
	{
		return -1;
	}




	BulletMove();
	




	if (m_timer >= 4.f)
		m_Life = false;

	if (m_Life)
		return 1;
	else
		return -1;


	m_timer += Timer::DeltaTime();



}

int Bullet::LateUpdate()
{
	return 1;
}

void Bullet::BulletMove()
{
	switch (m_bulletType)
	{
	case BOSS_CANNON:
		BossCannonMove();
		break;
	default:
		DefaultBulletMove();
		break;
	}
}

void Bullet::BossCannonMove()
{
}

void Bullet::DefaultBulletMove()
{
	if (m_dir)
		m_pos.x += Timer::DeltaTime() * 10;
	else
		m_pos.x -= Timer::DeltaTime() * 10;
}

