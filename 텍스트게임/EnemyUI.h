#pragma once
#include "BaseUI.h"
class Enemy;
class EnemyUI :
	public BaseUI
{
public:
	EnemyUI();
	virtual ~EnemyUI();
public:
	void SetEnemy(std::shared_ptr<Enemy> enemy);
	void UpdateEnemyStatus();

public:
	// BaseUI을(를) 통해 상속됨
	virtual int Update() override;
	virtual int LateUpdate() override;
	virtual void Render()override;
private:
	void UpdateHpBar();
private:
	STATUS m_enemyStatus;
	const wchar_t* m_objectName;
	wchar_t m_BaseImg[36];

	std::weak_ptr<Enemy> m_enemy;
	float m_activeTimer;
	const float m_expireTime;
};

