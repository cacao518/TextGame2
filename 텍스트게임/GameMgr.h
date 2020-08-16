#pragma once
#include "Header.h"
class Player;
class PlayerUI;
class Enemy;
class EnemyUI;
class Boss;
class BossUI;
class GameMgr
{
public:
	
	HRESULT SetPlayerUI(std::shared_ptr<PlayerUI> playerUI, std::shared_ptr<Player> player);
	
	HRESULT SetEnemyUI(std::shared_ptr<EnemyUI> enemyUI);
	HRESULT SetEnemy(std::shared_ptr<Enemy> enemy);

	HRESULT SetBossUI(std::shared_ptr<BossUI> bossUI);
	HRESULT SetBoss(std::shared_ptr<Boss> boss);
	
	void Update();
private:
	explicit GameMgr();
	~GameMgr();
public:
	static GameMgr* GetInstance()
	{
		if (nullptr == instance)
			instance = new GameMgr();

		return instance;
	}
	static void DestroyInstance()
	{
		if (nullptr != instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

private:
	static GameMgr* instance;

private:
	std::weak_ptr<PlayerUI> m_playerUI;
	std::weak_ptr<EnemyUI> m_enemyUI;
	std::weak_ptr<BossUI> m_bossUI;

};

