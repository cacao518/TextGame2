#pragma once
#include "GameObject.h"
class Enemy :public GameObject
{
public:
	Enemy(POS position);
	virtual ~Enemy();

	// GameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual int LateUpdate() override;

	void Knockback(POS otherObjPos);
	const STATUS& GetStatus()const { return m_Status; }
	void GetDamage(float damage, POS bulletPos);
	void GetDamage(float damage, bool bulletDir);

protected:
	ObjectMgr* objectMgr = ObjectMgr::GetInstance();
	
	//bool isGround = true;
	float m_MoveCount = 0;
	float m_timer = 0.f;
	STATUS m_Status;
	int baseColor;
	void damagedColor();

};

