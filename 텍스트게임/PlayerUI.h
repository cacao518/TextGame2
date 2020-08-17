#pragma once
#include "BaseUI.h"
class Player;
class PlayerUI :
	public BaseUI
{
public:
	PlayerUI();
	virtual ~PlayerUI();
public:
	void SetPlayer(std::shared_ptr<Player> player);
	void UpdatePlayerStatus();

public:
	// BaseUI��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual int LateUpdate() override;
	virtual void Render()override;
private:
	void UpdateHpBar();
private:
	STATUS m_playerStatus;
	const wchar_t* m_objectName;
	wchar_t m_BaseImg[36];
	wchar_t* m_bulletNumImg;

	std::weak_ptr<Player> m_player;
};

