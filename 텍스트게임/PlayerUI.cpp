#include "PlayerUI.h"
#include "Player.h"
#include "stdio.h"

PlayerUI::PlayerUI()
	:BaseUI(),m_playerStatus(STATUS(0.f,0.f,0.f))
{
	wchar_t baseImg[36] = { 
						 L'旨' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'旬',
						 L'早' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'早',
						 L'曲' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'天' ,L'旭' };
	m_width = 12;
	m_height = 3;

	memcpy(m_BaseImg, baseImg, sizeof(wchar_t) * m_width * m_height);

	m_sprite = new wchar_t[m_width * m_height];
	memcpy(m_sprite, m_BaseImg, sizeof(wchar_t) * m_width * m_height);

	m_pos = POS(2, 1);
	m_name = L"PlayerUI";

	m_objectName = nullptr;
	m_bulletNumImg = nullptr;
	m_BombNumImg = nullptr;
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::SetPlayer(std::shared_ptr<Player> player)
{
	m_player = player;
}

void PlayerUI::UpdatePlayerStatus()
{
	std::shared_ptr<Player> player = m_player.lock();
	if (!player)
		return;
	m_playerStatus = player->GetStatus();
	m_objectName = player->GetName();

	wchar_t img[3];
	if(player->GetBulletNum() < 10)
		wsprintf(img, L"0%d", player->GetBulletNum());
	else
		wsprintf(img, L"%d", player->GetBulletNum());
	m_bulletNumImg = new wchar_t[3];
	memcpy(m_bulletNumImg, img, sizeof(wchar_t) * 3);

	wchar_t img2[3];
	if (player->GetBombNum() < 10)
		wsprintf(img2, L"0%d", player->GetBombNum());
	else
		wsprintf(img2, L"%d", player->GetBombNum());
	m_BombNumImg = new wchar_t[3];
	memcpy(m_BombNumImg, img2, sizeof(wchar_t) * 3);
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

void PlayerUI::Render()
{
	if (nullptr != m_objectName)
		ObjectMgr::GetInstance()->Draw(m_objectName, (int)wcslen(m_objectName), 1, (int)m_pos.x, (int)m_pos.y - 1,LIGHTBLUE);
	if (nullptr != m_sprite)
		ObjectMgr::GetInstance()->Draw(m_sprite, m_width, m_height, (int)m_pos.x, (int)m_pos.y,BLUE);
	if (nullptr != m_bulletNumImg)
		ObjectMgr::GetInstance()->Draw(m_bulletNumImg, 3, 1, (int)m_pos.x+7, (int)m_pos.y-1, YELLOW);
	if (nullptr != m_BombNumImg)
		ObjectMgr::GetInstance()->Draw(m_BombNumImg, 3, 1, (int)m_pos.x + 11, (int)m_pos.y - 1, LIGHTRED);
}

void PlayerUI::UpdateHpBar()
{
	memcpy(m_sprite, m_BaseImg, sizeof(wchar_t) * m_width * m_height);
	float hpPercent = (m_playerStatus.hp / m_playerStatus.maxHp) * 100.f; 
	int hpGauge = (int)(hpPercent / 10.f);

	for (int i = 0; i < hpGauge; ++i)
		m_sprite[13 + i] = L'﹥';
}
