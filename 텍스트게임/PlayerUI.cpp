#include "PlayerUI.h"

PlayerUI::PlayerUI()
	:BaseUI(),m_playerStatus(STATUS(0.f,0.f,0.f))
{
	char baseImg[36] = { '旨' ,'收' ,'收' ,'收' ,'收' ,'收' ,'收' ,'收' ,'收' ,'收' ,'收' ,'旬',
						 '早' ,'=' ,'=' ,'=' ,'=' ,'=' ,'=' ,'=' ,'=' ,'=' ,'=' ,'早',
						 '曲' ,'收', '收' ,'收' ,'收' ,'收' ,'收' ,'收' ,'收' ,'收' ,'收' ,'旭' };
	m_width = 12;
	m_height = 3;

	memcpy(m_BaseImg, baseImg, sizeof(char) * m_width * m_height);

	m_sprite = new char[m_width * m_height];
	memcpy(m_sprite, m_BaseImg, sizeof(char) * m_width * m_height);

	m_pos = POS(10, 10);

}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::UpdatePlayerStatus(const STATUS& status)
{
	m_playerStatus = status;
}

int PlayerUI::Update()
{

	return 0;
}

int PlayerUI::LateUpdate()
{
	UpdateHpBar();
	return 0;
}

void PlayerUI::UpdateHpBar()
{
	memcpy(m_sprite, m_BaseImg, sizeof(char) * m_width * m_height);
	float hpPercent = (m_playerStatus.hp / m_playerStatus.maxHp) * 100.f; 
	int hpGauge = (int)(hpPercent / 10.f);

	for (int i = 0; i < hpGauge; ++i)
		m_sprite[13 + i] = '0';
}
