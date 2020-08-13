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


private:

	ObjectMgr* objectMgr = ObjectMgr::GetInstance();

	bool m_dir = true; //오른쪽이 트루임
	//bool isGround = true;
	float m_MoveCount = 0;

	float m_timer = 0.f;
};

