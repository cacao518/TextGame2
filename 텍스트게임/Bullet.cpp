#include "Bullet.h"
#include"Timer.h"
#include"BoxCollider.h"
#include "Enemy.h"

Bullet::Bullet(bool isEnemy, bool charge, int BulletType, bool dir,  POS position)
	:GameObject(position)
{
	m_chargeShoot = charge;
	printf("�ѻ�����");

	wchar_t Default[2]= { L'-', L'-'};
	wchar_t ChargeDefault[4] = { L'=', L'=',L')',L')' };
	wchar_t MachineGun[2] = { L'=', L'=' };
	wchar_t ChargeMachineGun[5] = { L'=', L'=',L')',L')',L')' };
	
	if (BulletType == HANDGUN)
	{
		m_damage = 3;
		m_width = 2;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, Default, sizeof(wchar_t) * m_width * m_height);
		m_color = 12;
	}
	if (BulletType == HANDGUN && m_chargeShoot)
	{
		m_damage = 5;
		m_width = 4;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, ChargeDefault, sizeof(wchar_t) * m_width * m_height);
		m_color = 12;
	}
	if (BulletType == TANKGUN)
	{
		m_damage = 4;
		m_width = 2;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, MachineGun, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTCYAN;
	}
	if (BulletType == TANKGUN && m_chargeShoot)
	{
		m_damage = 6;
		m_width = 5;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, ChargeMachineGun, sizeof(wchar_t) * m_width * m_height);
		m_color = LIGHTCYAN;
	}
	if (BulletType == HEABYGUN)
	{
		m_damage = 4;
		m_width = 2;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, MachineGun, sizeof(wchar_t) * m_width * m_height);
		m_color = YELLOW;
	}
	if (BulletType == HEABYGUN && m_chargeShoot)
	{
		m_damage = 6;
		m_width = 5;
		m_height = 1;
		m_sprite = new wchar_t[m_width * m_height];
		memcpy(m_sprite, ChargeMachineGun, sizeof(wchar_t) * m_width * m_height);
		m_color = YELLOW;
	}
	m_dir = dir;
	m_name = L"Bullet";
	
}

Bullet::~Bullet()
{
}

int Bullet::Update()
{

	auto otherObj = GetComponet<BoxCollider>()->OnTriggerEnter(L"Enemy");
	if (otherObj != nullptr )
	{
		//obj2->SetIsAttacked(true);
		//obj1->SetIsAttacked(true);

		std::shared_ptr<Enemy> E = std::dynamic_pointer_cast<Enemy>(otherObj);
		E->SetHp(m_damage);
		//E->Knockback();
		printf("����");
		SetIsLife(false);

	}
	else {}
	//else
	//{
		//obj1->SetIsAttacked(false);
		//obj2->SetIsAttacked(false);
	//}

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

