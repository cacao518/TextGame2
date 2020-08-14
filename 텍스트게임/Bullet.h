#pragma once
#include "GameObject.h"
class Bullet :public GameObject
{
public:
	Bullet(bool dir,float bulletDamage,POS position);
	~Bullet();

	// GameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual int LateUpdate() override;
	float m_bulletDamage;
	bool m_dir;

private:
	float m_timer = 0.f;

};

