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
	std::bitset<0xff> keyPress;
	std::mutex keyLock;
	std::thread KeyUpdate;

	ObjectMgr* objectMgr = ObjectMgr::GetInstance();

	bool m_dir = true; //오른쪽이 트루임
	//bool isGround = true;
	float m_MoveCount = 0;
};

