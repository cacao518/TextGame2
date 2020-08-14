#include "EnemyUI.h"

EnemyUI::EnemyUI()
	:BaseUI(), m_enemyStatus(STATUS(0.f, 0.f, 0.f))
{
}

EnemyUI::~EnemyUI()
{
}

void EnemyUI::SetEnemy(std::shared_ptr<Enemy> enemy)
{
}

void EnemyUI::UpdateEnemyStatus()
{
}

int EnemyUI::Update()
{
	return 0;
}

int EnemyUI::LateUpdate()
{
	return 0;
}

void EnemyUI::Render()
{
}
