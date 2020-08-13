#pragma once
#include "GameObject.h"
class Player :public GameObject
{
public:
	Player(POS position);
	virtual ~Player();

	// GameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual int LateUpdate() override;
	bool attack;

private:
	std::bitset<0xff> keyPress;
	std::mutex keyLock;
	std::thread KeyUpdate;

	ObjectMgr* objectMgr = ObjectMgr::GetInstance();

	bool m_dir = true; //오른쪽이 트루임
	bool isGround = true;

	char m_leftImg[6], m_rightImg[6], m_attackImg[6];
};

