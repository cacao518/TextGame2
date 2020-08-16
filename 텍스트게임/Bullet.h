#pragma once
#include "GameObject.h"
class Bullet :public GameObject
{
public:
	enum OBJTYPE { HANDGUN, TANKGUN, HEABYGUN, SHOTGUN };

	Bullet(bool isEnemy, bool charge, int BulletType, bool dir, POS position);
	~Bullet();

	// GameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual int LateUpdate() override;
	float m_bulletDamage;
	

private:
	float m_timer = 0.f;
	bool m_chargeShoot = false;

};

