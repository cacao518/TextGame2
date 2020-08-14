#pragma once
#include "BaseUI.h"
class PlayerUI :
	public BaseUI
{
public:
	PlayerUI();
	virtual ~PlayerUI();
public:
	void UpdatePlayerStatus(const STATUS& status,const wchar_t* name);

public:
	// BaseUI을(를) 통해 상속됨
	virtual int Update() override;
	virtual int LateUpdate() override;
	virtual void Render()override;
private:
	void UpdateHpBar();
private:
	STATUS m_playerStatus;
	const wchar_t* m_objectName;
	wchar_t m_BaseImg[36];
};

