#pragma once
#include "GameObject.h"
class Bullet :public GameObject
{
public:
	Bullet(bool charge, bool dir,float bulletDamage,POS position);
	~Bullet();

	// GameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual int LateUpdate() override;
	float m_bulletDamage;
	

private:
	float m_timer = 0.f;
	bool m_chargeShoot = false;

};

