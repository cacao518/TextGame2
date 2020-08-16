#pragma once
#include "BaseUI.h"
class Boss;
class BossUI :
	public BaseUI
{
public:
	BossUI();
	virtual ~BossUI();
public:
	void SetBoss(std::shared_ptr<Boss> boss);
	void UpdateBossStatus();

public:
	// BaseUI을(를) 통해 상속됨
	virtual int Update() override;
	virtual int LateUpdate() override;
	virtual void Render()override;
private:
	void UpdateHpBar();
private:
	STATUS m_bossStatus;
	const wchar_t* m_objectName;
	wchar_t m_BaseImg[36];

	std::weak_ptr<Boss> m_boss;
	float m_activeTimer;
	const float m_expireTime;
};

