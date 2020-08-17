#include "ItemBox.h"
#include "BoxCollider.h"
#include "Player.h"
ItemBox::ItemBox(int type, POS position)
	:GameObject(position)
{
	m_type = type;
	wchar_t img1[6] = { L' ', L' ',L' ',L'[', L'H',L']'};
	wchar_t img2[6] = { L' ', L' ',L' ',L'[', L'R',L']' };
	wchar_t img3[6] = { L' ', L' ',L' ',L'[', L'S',L']' };
	m_width = 3;
	m_height = 2;
	m_sprite = new wchar_t[m_width * m_height];
	if (m_type == Bullet::HEABYGUN)
	{
		m_weaponSpeed = 20.f;
		m_bulletNum = 50;
		memcpy(m_sprite, img1, sizeof(wchar_t) * m_width * m_height);
		m_color = YELLOW;
	}
	else if (m_type == Bullet::MISSILE)
	{
		m_weaponSpeed = 10.f;
		m_bulletNum = 20;
		memcpy(m_sprite, img2, sizeof(wchar_t) * m_width * m_height);
		m_color = BLUE;
	}
	else if (m_type == Bullet::SHOTGUN)
	{
		m_weaponSpeed = 5.f;
		m_bulletNum = 10;
		memcpy(m_sprite, img3, sizeof(wchar_t) * m_width * m_height);
		m_color = GREEN;
	}
	m_name = L"ItemBox";
}

ItemBox::~ItemBox()
{
}

int ItemBox::Update()
{
	auto otherObj = GetComponent<BoxCollider>()->OnTriggerEnter(L"Player");
	if (otherObj != nullptr)
	{
		std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(otherObj);
		player->SetWeapon(m_type, m_weaponSpeed, m_bulletNum);
		return -1;
	}

	return 1;
}

int ItemBox::LateUpdate()
{
	return 1;
}

void ItemBox::SetType(int type)
{
	m_type = type;
}

int ItemBox::GetType()
{
	return m_type;
}
