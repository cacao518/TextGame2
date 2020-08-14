#include "GameMgr.h"
#include "Player.h"
#include "PlayerUI.h"
GameMgr* GameMgr::instance = nullptr;



HRESULT GameMgr::SetPlayerUI(std::shared_ptr<PlayerUI> playerUI, std::shared_ptr<Player> player)
{
	if (nullptr == playerUI||nullptr==player)
		return E_FAIL;

	m_playerUI = playerUI;
	
	m_playerUI.lock()->SetPlayer(player);
	return S_OK;
}

void GameMgr::Update()
{
	std::shared_ptr<PlayerUI> playerUI = m_playerUI.lock();
	if (!playerUI)
		return;

	playerUI->UpdatePlayerStatus();
	
}

GameMgr::GameMgr()
{
}

GameMgr::~GameMgr()
{
}
