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
	if (m_bulletType != SHOTGUN)
	{
		m_bulletSpeed = 10.f;
		m_MaxTimer = 4.f;
	}
	else
	{
		m_bulletSpeed = 0;
		m_MaxTimer = 0.7f;
	}

	//printf("ÃÑ»ý¼ºµÊ");

	wchar_t Default[2]= { L'-', L'-'};
	wchar_t ChargeDefault[4] = { L'=', L'=',L')',L')' };
	wchar_t MachineGun[2] = { L'=', L'=' };
	wchar_t ChargeMachineGun[5] = { L'=', L'=',L')',L')',L')' };

	wchar_t Missile[5] = { L'>', L'>',L'=',L'=',L')' };
	wchar_t ChargeMissile[7] = { L'~',L'>', L'>',L'=',L'=',L')',L')' };

	wchar_t ShotGun[60] = { L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#' };
	wchar_t ChargeShotGun[60] = { L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#', L'#', L'#',L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#',L'#', L'#' };

	wchar_t boombImg[2] = { L'0',L'0' };
	wchar_t cannonImg[9] = { L'o',L'O',L'o',L'O',L'O',L'O',L'o',L'O',L'o' };

	if (m_bulletType == HANDGUN)
	{
		m_bulletDamage = 3;
		m_width = 2;
		m_height = 1;
		if (!dir) reverseChar(Default, m_width * m_height);
		m_sprite = new wchar_t[m_width * m_height];
		ZeroMemory(m_sprite, sizeof(wchar_t) * m_width * m_height);

		memcpy(m_sprite, Default, sizeof(wchar_t) * m_width * m_height);
		m_color = 12;
	}
	if (m_bulletType == HANDGUN && m_chargeShoot)
	{
		m_bulletDamage = 5;
		m_width = 4;
		m_height = 1;
		if (!dir) reverseChar(ChargeDefault, m_width * m_height);
		m_sprite = new wchar_t[m_width * m_height];
		ZeroMemory(m_sprite, sizeof(wchar_t) * m_width * m_height);

		memcpy(m_sprite, ChargeDefault, sizeof(wchar_t) * m_width * m_height);
		m_color = 12;
	}
	if (m_bulletType == TANKGUN)
	{
		m_bulletDamage = 3;
		m_width = 2;
		m_height = 1;
		if (!dir) reverseChar(MachineGun, m_width * m_height);
		m_sprite = new wchar_t[m_width * m_height];
		ZeroMemory(m_sprite, sizeof(wchar_t) * m_width * m_height);

		memcpy(m_sprite, MachineGun, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTCYAN;
	}
	if (m_bulletType == TANKGUN && m_chargeShoot)
	{
		m_bulletDamage = 5;
		m_width = 5;
		m_height = 1;
		if (!dir) reverseChar(ChargeMachineGun, m_width * m_height);
		m_sprite = new wchar_t[m_width * m_height];
		ZeroMemory(m_sprite, sizeof(wchar_t) * m_width * m_height);

		memcpy(m_sprite, ChargeMachineGun, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTCYAN;
	}
	if (m_bulletType == HEABYGUN)
	{
		m_bulletDamage = 4;
		m_width = 2;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		ZeroMemory(m_sprite, sizeof(wchar_t) * m_width * m_height);

		memcpy(m_sprite, MachineGun, sizeof(wchar_t) * m_width * m_height);
		m_color = YELLOW;
	}
	if (m_bulletType == HEABYGUN && m_chargeShoot)
	{
		m_bulletDamage = 5;
		m_width = 5;
		m_height = 1;
		if (!dir) reverseChar(ChargeMachineGun, m_width * m_height);
		m_sprite = new wchar_t[m_width * m_height];
		ZeroMemory(m_sprite, sizeof(wchar_t) * m_width * m_height);

		memcpy(m_sprite, ChargeMachineGun, sizeof(wchar_t) * m_width * m_height);
		m_color = YELLOW;
	}
	if (m_bulletType == MISSILE )
	{
		m_bulletDamage = 5;
		m_width = 5;
		m_height = 1;
		if (!dir) reverseChar(Missile, m_width * m_height);
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, Missile, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTMAGENTA;
	}
	if (m_bulletType == MISSILE && m_chargeShoot)
	{
		m_bulletDamage = 8;
		m_width = 7;
		m_height = 1;
		if (!dir) reverseChar(ChargeMissile, m_width * m_height);
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, ChargeMissile, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTMAGENTA;
	}
	if (m_bulletType == SHOTGUN)
	{
		m_bulletDamage = 10;
		m_width = 30;
		m_height = 2;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, ShotGun, sizeof(wchar_t) * m_width * m_height);
		m_color = RED;
	}
	if (m_bulletType == SHOTGUN && m_chargeShoot)
	{
		m_bulletDamage = 15;
		m_width = 30;
		m_height = 2;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, ChargeShotGun, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTRED;
	}
	if (m_bulletType == BOSS_CANNON)
	{
		wchar_t cannonImg[9] = { L'o',L'O',L'o',L'O',L'O',L'O',L'o',L'O',L'o' };

		m_bulletSpeed = 10.f;
		m_bulletDamage = 40.f;
		m_width = 3;
		m_height = 3;
		m_sprite = new wchar_t[m_width * m_height];
		ZeroMemory(m_sprite, sizeof(wchar_t) * m_width * m_height);
		memcpy(m_sprite, cannonImg, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTRED;
	}

	if (m_bulletType == BOOMB)
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

	if (BulletType == METEOR)
	{
		wchar_t meteorImg[16] = { L' ',L'@',L'@',L' ',L'@',L'@',L'@',L'@',L'@',L'@',L'@',L'@',L' ',L'@',L'@',L' ' };

		m_bulletSpeed = 10.f;
		m_bulletDamage = 40.f;
		m_width = 4;
		m_height = 4;
		m_sprite = new wchar_t[m_width * m_height];
		ZeroMemory(m_sprite, sizeof(wchar_t) * m_width * m_height);
		memcpy(m_sprite, meteorImg, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTRED;
	}

	if (BulletType == ENEMYBULLET)
	{
		m_bulletSpeed = 5.f;
		m_bulletDamage = 10.f;
		m_width = 2;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, boombImg, sizeof(wchar_t) * m_width * m_height);
		m_color = 2;
	}

	if (BulletType == EARTHQUAKE)
	{
		wchar_t earthquakeImg[24] = { L'^',L'^',L'^',L'^',L'^',L'^',L'^',L'^',
									L'^',L'^',L'^',L'^',L'^',L'^',L'^',L'^',
									L'^',L'^',L'^',L'^',L'^',L'^',L'^',L'^'};

		m_bulletSpeed = 10.f;
		m_bulletDamage = 40.f;
		m_width = 8;
		m_height = 3;
		m_sprite = new wchar_t[m_width * m_height];
		ZeroMemory(m_sprite, sizeof(wchar_t) * m_width * m_height);
		memcpy(m_sprite, earthquakeImg, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTRED;
		m_expireTime = 1.f;
	}
	m_dir = dir;
	m_gravitySpeed = 0.f;
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
			EnemyObj->SetIsAttacked(true);

				std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(EnemyObj);

				if (EnemyObj->GetName() == L"GuardEnemy" &&m_bulletType!=BOOMB)
				enemy->GetDamage(m_bulletDamage, m_dir);
				else
				enemy->GetDamage(m_bulletDamage, GetPos());
				
				GameMgr::GetInstance()->SetEnemy(enemy);
			
			if (m_bulletType != SHOTGUN) SetIsLife(false);
				

		}


		auto bossObj = GetComponent<BoxCollider>()->OnTriggerEnter(L"Boss");
		if (bossObj != nullptr)
		{
			std::shared_ptr<Boss> boss = std::dynamic_pointer_cast<Boss>(bossObj);
			GameMgr::GetInstance()->SetBoss(boss);
			if (m_bulletType != SHOTGUN) SetIsLife(false);
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

	m_timer += Timer::DeltaTime();

	if (m_timer >= m_MaxTimer)
		m_Life = false;

	if (!m_Life)
		return -1;
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
	case METEOR:
		MeteorMove();
		break;
	case EARTHQUAKE:
		EarthquakeMove();
		break;
	default:
		DefaultBulletMove();
		break;
	}
}

void Bullet::BossCannonMove()
{
	if (m_dir)
		m_pos.x += Timer::DeltaTime() * m_bulletSpeed;
	else
		m_pos.x -= Timer::DeltaTime() * m_bulletSpeed;

	m_pos.y += m_gravitySpeed * Timer::DeltaTime();
	m_gravitySpeed += Timer::DeltaTime() * 4.f;
}

void Bullet::MeteorMove()
{
	m_pos.y += Timer::DeltaTime() * m_bulletSpeed;

}

void Bullet::EarthquakeMove()
{
	if(m_timer<=0.5f)
		m_pos.y -= Timer::DeltaTime() * m_bulletSpeed;
	else
		m_pos.y += Timer::DeltaTime() * m_bulletSpeed;


}

void Bullet::DefaultBulletMove()
{
	if (m_dir)
		m_pos.x += Timer::DeltaTime() * m_bulletSpeed;
	else
		m_pos.x -= Timer::DeltaTime() * m_bulletSpeed;
}

void Bullet::reverseChar(wchar_t* w, int size)
{
	for (int i = 0; i < size - 1 - i; ++i)
	{
		wchar_t temp = w[i];
		w[i] = w[size - 1 - i];
		w[size - 1 - i] = temp;
	}
}
