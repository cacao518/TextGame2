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
	virtual void Render() override;

	void SetHp(float damage);
	STATUS m_Status;
	STATUS GetStatus();
	void Knockback(POS otherObjPos);

	void GetDamage(float damage, POS enemyPos);
	void SetIsRide(int flag);
	int GetIsRide();
	void SetWeapon(int weaponType, int weaponSpeed, int bulletNum) {
		m_weaponType = weaponType; m_weaponSpeed = weaponSpeed; m_bulletNum = bulletNum;
	}
	int GetBulletNum() { return m_bulletNum; };
private:
	std::bitset<0xff> keyPress;
	std::mutex keyLock;
	std::thread KeyUpdate;

	void Attack(bool charge);
	ObjectMgr* objectMgr = ObjectMgr::GetInstance();
	wchar_t bulletImg[2] = { '0','0' };
	bool m_dir = true; //오른쪽이 트루임
	float m_attackCount = 0;
	float m_colorCount = 0;
	bool m_charging = false;
	int m_jumpCount = 0;
	int m_jumpPower = 6;
	bool m_invincibility = false;
	float m_timer = 0.f;
	
	const int ATTACK_DELAY_MAX = 10;
	const int DEFAULT_WEAPON_SPEED = 20;
	int m_weaponType;
	int m_weaponSpeed;
	int m_attackDelay; // 0이 되어야 공격 가능하다.
	int m_bulletNum;
	bool m_isRide = false;
	wchar_t m_leftImg[6], m_rightImg[6], m_attackImg[6], m_tankImg[14];
	
};

