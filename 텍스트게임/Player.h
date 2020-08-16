#pragma once
#include "GameObject.h"
#include "ChargeParticle1.h"
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
	void Knockback(POS otherObjPos);

	void GetDamage(float damage, POS enemyPos);
private:
	std::bitset<0xff> keyPress;
	std::mutex keyLock;
	std::thread KeyUpdate;

	
	ObjectMgr* objectMgr = ObjectMgr::GetInstance();
	wchar_t bulletImg[2] = { '0','0' };
	bool m_dir = true; //오른쪽이 트루임
	bool m_attack = false;
	float m_attackCount = 0;
	float m_colorCount = 0;
	bool m_charging = false;
	int m_jumpCount = 0;
	int m_jumpPower = 6;
	bool m_invincibility = false;
	float m_timer = 0.f;
	

	wchar_t m_leftImg[6], m_rightImg[6], m_attackImg[6];
	
};

