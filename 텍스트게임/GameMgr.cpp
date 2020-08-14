#include "GameMgr.h"
#include "Player.h"
#include "PlayerUI.h"
GameMgr* GameMgr::instance = nullptr;

HRESULT GameMgr::SetPlayer(std::shared_ptr<Player> player)
{
	if (nullptr == player)
		return E_FAIL;

	m_player = player;
	return S_OK;
}

HRESULT GameMgr::SetPlayerUI(std::shared_ptr<PlayerUI> playerUI)
{
	if (nullptr == playerUI)
		return E_FAIL;

	m_playerUI = playerUI;
	return S_OK;
}

void GameMgr::Update()
{
	std::shared_ptr<Player> player = m_player.lock();
	if (!player)
		return;

	std::shared_ptr<PlayerUI> playerUI = m_playerUI.lock();
	if (!playerUI)
		return;

	playerUI->UpdatePlayerStatus(player->GetStatus(),player->GetName());
	
}

GameMgr::GameMgr()
{
}

GameMgr::~GameMgr()
{
}
