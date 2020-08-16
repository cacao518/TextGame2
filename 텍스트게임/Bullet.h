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
	
	const float GetBulletDamage()const { return m_bulletDamage; }
	float m_bulletDamage;
	bool m_dir;

	
private:
	float m_timer = 0.f;
	bool m_chargeShoot = false;

};

