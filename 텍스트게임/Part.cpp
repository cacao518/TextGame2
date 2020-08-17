#include "Part.h"
#include "Player.h"
#include "Boss.h"
#include "Bullet.h"
#include "BoxCollider.h"
#include "Timer.h"
#include "GameMgr.h"
Part::Part(const char* fileName, int width, int height, int baseColor, GameObject* parentObj)
	:GameObject(POS()),m_IsDamagedPart(false),m_IsDamagingPart(false),m_parentObj(parentObj)
{

	m_width = width;
	m_height = height;
	int imgSize = width * height;
	wchar_t* baseImg = new wchar_t[imgSize + 1];
	ZeroMemory(baseImg, sizeof(wchar_t) * (imgSize + 1));
	std::wifstream fp;
	std::wstring readTxt;
	fp.open(fileName);
	while (!fp.eof())
	{
		std::getline(fp, readTxt);
		wcscat(baseImg, readTxt.c_str());
	}

	fp.close();
	m_sprite = new wchar_t[m_width * m_height];
	memcpy(m_sprite, baseImg, sizeof(wchar_t) * m_width * m_height);

	m_name = L"Part";
	m_baseColor = baseColor;
	m_color = baseColor;

	m_parentObj = parentObj;

}

Part::~Part()
{
}

int Part::Update()
{
	auto boxCollider = GetComponent<BoxCollider>();
	if (nullptr == boxCollider)
		return 0;

	if (m_IsDamagingPart)
	{
		auto player = boxCollider->OnTriggerEnter(L"Player");
		if (nullptr != player)
		{
			std::dynamic_pointer_cast<Player>(player)->GetDamage(static_cast<Boss*>(m_parentObj)->GetStatus().attackDamage, m_parentObj->GetPos());
		}
	}

	if (m_IsDamagedPart)
	{
		auto bullet = std::dynamic_pointer_cast<Bullet>(boxCollider->OnTriggerEnter(L"Bullet"));
		
		if (nullptr != bullet)
		{
			if (!bullet->GetIsEnemy())
			{
				static_cast<Boss*>(m_parentObj)->GetDamage(bullet->GetBulletDamage());
				if(bullet->GetType() != Bullet::SHOTGUN) bullet->SetIsLife(false);
				SetDamageEffect();
			}
			
		}
	}

	if (m_damaged)
	{
		if (m_timer >= 2.f)
		{
			m_damaged = false;
			m_color = m_baseColor;
		}

		m_timer += Timer::DeltaTime();

	}

	ShowDamageEffect();
	return 0;
}

int Part::LateUpdate()
{
	return 0;
}

void Part::SetDamageEffect()
{
	m_timer = 0.f;
	m_damaged = true;
}

void Part::ShowDamageEffect()
{
	if (!m_damaged)
		return;

	if ((int)(m_timer * 100.f) % 2 == 0)
		m_color = RED;
	else
		m_color = m_baseColor;
}

