#pragma once
#include "GameObject.h"
class Bullet :public GameObject
{
public:
	enum OBJTYPE { HANDGUN, TANKGUN, HEABYGUN, SHOTGUN };

	Bullet(bool isEnemy, bool charge, int BulletType, bool dir, POS position);
	~Bullet();

	// GameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual int LateUpdate() override;
	

private:
	float m_timer = 0.f;
	float m_damage;
	bool m_chargeShoot = false;

};

