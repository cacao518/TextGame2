#pragma once
#include "Header.h"
class Player;
class PlayerUI;
class GameMgr
{
	HRESULT SetPlayer(std::shared_ptr<Player> player);
	HRESULT SetPlayerUI(std::shared_ptr<PlayerUI> playerUI);

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
	std::weak_ptr<Player> m_player;
	std::weak_ptr<PlayerUI> m_playerUI;


};

