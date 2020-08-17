#pragma once
#include "GameObject.h"
class Bullet :public GameObject
{
public:
	enum OBJTYPE { HANDGUN, TANKGUN, HEABYGUN, SHOTGUN,BOSS_CANNON,BOOMB,TYPE_END };

	Bullet(bool isEnemy, bool charge, int BulletType, bool dir, POS position);
	~Bullet();

	// GameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual int LateUpdate() override;
	
	const float GetBulletDamage()const { return m_bulletDamage; }
	const bool GetIsEnemy()const { return m_isEnemy; }
private:
	void BulletMove();
	void BossCannonMove();
	void DefaultBulletMove();
private:
	float m_timer = 0.f;
	bool m_chargeShoot = false;
	float m_bulletDamage;
	float m_bulletSpeed=10.f;
	bool m_isEnemy;

	OBJTYPE m_bulletType = TYPE_END;
	int boombStep=0;
};

