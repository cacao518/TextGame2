#pragma once
#include "GameObject.h"
class Bullet :public GameObject
{
public:
	enum OBJTYPE { HANDGUN, TANKGUN, HEABYGUN, SHOTGUN,BOSS_CANNON };

	Bullet(bool isEnemy, bool charge, int BulletType, bool dir, POS position);
	~Bullet();

	// GameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual int LateUpdate() override;
	
	const float GetBulletDamage()const { return m_bulletDamage; }
	const bool GetIsEnemy()const { return m_isEnemy; }

private:
	float m_timer = 0.f;
	bool m_chargeShoot = false;
	float m_bulletDamage;

	bool m_isEnemy;
};

