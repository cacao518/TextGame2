#include "Bullet.h"
#include"Timer.h"
#include"BoxCollider.h"
#include "Enemy.h"
#include "GameMgr.h"
#include "Boss.h"
#include "Player.h"
Bullet::Bullet(bool isEnemy, bool charge, int BulletType, bool dir,  POS position)
	:GameObject(position),m_isEnemy(isEnemy)
{
	m_type = BulletType;
	m_chargeShoot = charge;
	if (m_type != SHOTGUN)
	{
		m_bulletSpeed = 10;
		m_MaxTimer = 4.f;
	}
	else
	{
		m_bulletSpeed = 0;
		m_MaxTimer = 0.7f;
	}

	printf("ÃÑ»ý¼ºµÊ");

	wchar_t Default[2]= { L'-', L'-'};
	wchar_t ChargeDefault[4] = { L'=', L'=',L')',L')' };
	wchar_t MachineGun[2] = { L'=', L'=' };
	wchar_t ChargeMachineGun[5] = { L'=', L'=',L')',L')',L')' };

	wchar_t Missile[5] = { L'>', L'>',L'=',L'=',L')' };
	wchar_t ChargeMissile[7] = { L'~',L'>', L'>',L'=',L'=',L')',L')' };

	wchar_t ShotGun[60] = { L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#' };
	wchar_t ChargeShotGun[60] = { L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#' };
	if (m_type == HANDGUN)
	{
		m_bulletDamage = 1;
		m_width = 2;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, Default, sizeof(wchar_t) * m_width * m_height);
		m_color = 12;
	}
	if (m_type == HANDGUN && m_chargeShoot)
	{
		m_bulletDamage = 3;
		m_width = 4;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, ChargeDefault, sizeof(wchar_t) * m_width * m_height);
		m_color = 12;
	}
	if (m_type == TANKGUN)
	{
		m_bulletDamage = 2;
		m_width = 2;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, MachineGun, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTCYAN;
	}
	if (m_type == TANKGUN && m_chargeShoot)
	{
		m_bulletDamage = 5;
		m_width = 5;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, ChargeMachineGun, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTCYAN;
	}
	if (m_type == HEABYGUN)
	{
		m_bulletDamage = 2;
		m_width = 2;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, MachineGun, sizeof(wchar_t) * m_width * m_height);
		m_color = YELLOW;
	}
	if (m_type == HEABYGUN && m_chargeShoot)
	{
		m_bulletDamage = 4;
		m_width = 5;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, ChargeMachineGun, sizeof(wchar_t) * m_width * m_height);
		m_color = YELLOW;
	}
	if (m_type == MISSILE )
	{
		m_bulletDamage = 5;
		m_width = 5;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, Missile, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTMAGENTA;
	}
	if (m_type == MISSILE && m_chargeShoot)
	{
		m_bulletDamage = 8;
		m_width = 7;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, ChargeMissile, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTMAGENTA;
	}
	if (m_type == SHOTGUN)
	{
		m_bulletDamage = 10;
		m_width = 30;
		m_height = 2;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, ShotGun, sizeof(wchar_t) * m_width * m_height);
		m_color = RED;
	}
	if (m_type == SHOTGUN && m_chargeShoot)
	{
		m_bulletDamage = 15;
		m_width = 30;
		m_height = 2;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, ChargeShotGun, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTRED;
	}
	if (m_type == BOSS_CANNON)
	{
		wchar_t cannonImg[9] = { L'o',L'@',L'o',L'@',L'@',L'@',L'o',L'@',L'o' };
		m_bulletDamage = 40.f;
		m_width = 3;
		m_height = 3;
		m_sprite = new wchar_t[m_width, m_height];
		memcpy(m_sprite, cannonImg, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTRED;
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
		auto otherObj = GetComponent<BoxCollider>()->OnTriggerEnter(L"Enemy");
		if (otherObj != nullptr)
		{
			//obj2->SetIsAttacked(true);
			//obj1->SetIsAttacked(true);

			std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(otherObj);
			enemy->SetHp(m_bulletDamage);
			enemy->Knockback(enemy->GetPos());
			GameMgr::GetInstance()->SetEnemy(enemy);
			if(m_type != SHOTGUN)
				SetIsLife(false);
		}

		auto bossObj = GetComponent<BoxCollider>()->OnTriggerEnter(L"Boss");
		if (bossObj != nullptr)
		{
			std::shared_ptr<Boss> boss = std::dynamic_pointer_cast<Boss>(bossObj);
			GameMgr::GetInstance()->SetBoss(boss);
			if (m_type != SHOTGUN)
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
		}
	}
	

	if (m_dir)
		m_pos.x += Timer::DeltaTime() * m_bulletSpeed;
	else
		m_pos.x -= Timer::DeltaTime() * m_bulletSpeed;


	m_timer += Timer::DeltaTime();

	if (m_timer >= m_MaxTimer)
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

