#include "GameMgr.h"
#include "Player.h"
#include "PlayerUI.h"
#include "Enemy.h"
#include "EnemyUI.h"
GameMgr* GameMgr::instance = nullptr;



HRESULT GameMgr::SetPlayerUI(std::shared_ptr<PlayerUI> playerUI, std::shared_ptr<Player> player)
{
	if (nullptr == playerUI||nullptr==player)
		return E_FAIL;

	m_playerUI = playerUI;
	
	m_playerUI.lock()->SetPlayer(player);
	return S_OK;
}

HRESULT GameMgr::SetEnemyUI(std::shared_ptr<EnemyUI> enemyUI)
{
	if (nullptr == enemyUI)
		return E_FAIL;
	m_enemyUI = enemyUI;
	return S_OK;
}

HRESULT GameMgr::SetEnemy(std::shared_ptr<Enemy> enemy)
{
	std::shared_ptr<EnemyUI> enemyUI = m_enemyUI.lock();
	if (nullptr == enemyUI)
		return E_FAIL;

	enemyUI->SetEnemy(enemy);
	return S_OK;
}

void GameMgr::Update()
{
	{
		std::shared_ptr<PlayerUI> playerUI = m_playerUI.lock();
		if (!playerUI)
			return;

		playerUI->UpdatePlayerStatus();
	}
	
	{
		std::shared_ptr<EnemyUI> enemyUI = m_enemyUI.lock();
		if (!enemyUI)
			return;

		enemyUI->UpdateEnemyStatus();
	}
}

GameMgr::GameMgr()
{
}

GameMgr::~GameMgr()
{
}
