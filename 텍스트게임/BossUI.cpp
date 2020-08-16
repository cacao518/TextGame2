#include "BossUI.h"
#include "Boss.h"
#include "Timer.h"
BossUI::BossUI()
	:BaseUI(), m_bossStatus(STATUS(0.f, 0.f, 0.f)), m_expireTime(5.f),m_activeTimer(0.f)
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

	m_pos = POS(20, 23);
	m_name = L"BossUI";

	m_objectName = nullptr;
	m_color = MAGENTA;
}

BossUI::~BossUI()
{
}

void BossUI::SetBoss(std::shared_ptr<Boss> boss)
{
	std::shared_ptr<Boss> curBoss = m_boss.lock();
	if (nullptr == curBoss || curBoss.get() != boss.get())
		m_boss = boss;

	m_activeTimer = 0.f;
}

void BossUI::UpdateBossStatus()
{
	if (m_activeTimer >= m_expireTime)
	{
		return;
	}
	m_activeTimer += Timer::DeltaTime();

	std::shared_ptr<Boss> boss = m_boss.lock();
	if (!boss)
		return;
	m_bossStatus = boss->GetStatus();
	m_objectName = boss->GetName();
}

int BossUI::Update()
{
	return 0;
}

int BossUI::LateUpdate()
{
	UpdateHpBar();

	return 0;
}

void BossUI::Render()
{
	if (m_activeTimer >= m_expireTime || m_boss.expired())
		return;

	if (nullptr != m_objectName)
		ObjectMgr::GetInstance()->Draw(m_objectName, (int)wcslen(m_objectName), 1, (int)m_pos.x + 10, (int)m_pos.y - 1, LIGHTMAGENTA);
	if (nullptr != m_sprite)
		ObjectMgr::GetInstance()->Draw(m_sprite, m_width, m_height, (int)m_pos.x, (int)m_pos.y, m_color);
}

void BossUI::UpdateHpBar()
{
	memcpy(m_sprite, m_BaseImg, sizeof(wchar_t) * m_width * m_height);
	float hpPercent = (m_bossStatus.hp / m_bossStatus.maxHp) * 100.f;
	int hpGauge = (int)(hpPercent / 10.f);

	for (int i = 0; i < hpGauge; ++i)
		m_sprite[13 + i] = L'﹥';
}
