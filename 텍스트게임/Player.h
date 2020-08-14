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
	void SetHp(float damage);
	STATUS m_Status;
	STATUS GetStatus();
	

private:
	std::bitset<0xff> keyPress;
	std::mutex keyLock;
	std::thread KeyUpdate;

	ObjectMgr* objectMgr = ObjectMgr::GetInstance();
	wchar_t bulletImg[2] = { '0','0' };
	bool m_dir = true; //오른쪽이 트루임
	bool attack;
	
	int m_jumpCount = 0;
	int m_jumpPower = 6;
	float m_gravitySpeed = 0;

	wchar_t m_leftImg[6], m_rightImg[6], m_attackImg[6];
};

