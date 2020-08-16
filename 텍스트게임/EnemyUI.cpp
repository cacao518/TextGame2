#include "EnemyUI.h"
#include "Enemy.h"
#include "Timer.h"
EnemyUI::EnemyUI()
	:BaseUI(), m_enemyStatus(STATUS(0.f, 0.f, 0.f)),m_expireTime(5.f), m_activeTimer(0.f)
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

	m_pos = POS(20, 1);
	m_name = L"EnemyUI";

	m_objectName = nullptr;
}

EnemyUI::~EnemyUI()
{
}

void EnemyUI::SetEnemy(std::shared_ptr<Enemy> enemy)
{
	std::shared_ptr<Enemy> curEnemy = m_enemy.lock();
	if(nullptr == curEnemy || curEnemy.get() != enemy.get())
		m_enemy = enemy;
	
	m_activeTimer = 0.f;
}

void EnemyUI::UpdateEnemyStatus()
{
	if (m_activeTimer >= m_expireTime)
	{
		return;
	}
	m_activeTimer += Timer::DeltaTime();

	std::shared_ptr<Enemy> enemy = m_enemy.lock();
	if (!enemy)
		return;
	m_enemyStatus = enemy->GetStatus();
	m_objectName = enemy->GetName();
}

int EnemyUI::Update()
{
	return 0;
}

int EnemyUI::LateUpdate()
{
	UpdateHpBar();

	return 0;
}

void EnemyUI::Render()
{
	if (m_activeTimer >= m_expireTime||m_enemy.expired())
		return;

	if (nullptr != m_objectName)
		ObjectMgr::GetInstance()->Draw(m_objectName, (int)wcslen(m_objectName), 1, (int)m_pos.x+10, (int)m_pos.y - 1, LIGHTCYAN);
	if (nullptr != m_sprite)
		ObjectMgr::GetInstance()->Draw(m_sprite, m_width, m_height, (int)m_pos.x, (int)m_pos.y, CYAN);
}

void EnemyUI::UpdateHpBar()
{
	memcpy(m_sprite, m_BaseImg, sizeof(wchar_t) * m_width * m_height);
	float hpPercent = (m_enemyStatus.hp / m_enemyStatus.maxHp) * 100.f;
	int hpGauge = (int)(hpPercent / 10.f);

	for (int i = 0; i < hpGauge; ++i)
		m_sprite[13 + i] = L'﹥';
}
