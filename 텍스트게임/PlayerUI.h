#pragma once
#include "BaseUI.h"
class PlayerUI :
	public BaseUI
{
public:
	PlayerUI();
	virtual ~PlayerUI();
public:
	void UpdatePlayerStatus(const STATUS& status);

public:
	// BaseUI을(를) 통해 상속됨
	virtual int Update() override;
	virtual int LateUpdate() override;
private:
	void UpdateHpBar();
private:
	STATUS m_playerStatus;
	char m_BaseImg[36];
};

