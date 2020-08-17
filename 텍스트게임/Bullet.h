#pragma once
#include "GameObject.h"
class Bullet :public GameObject
{
public:
	enum OBJTYPE { HANDGUN, TANKGUN, HEABYGUN, MISSILE, SHOTGUN, BOSS_CANNON, BOOMB, EARTHQUAKE, METEOR, TYPE_END};

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
	void MeteorMove();
	void EarthquakeMove();
	void DefaultBulletMove();
	void reverseChar(wchar_t* w, int size);
private:
	float m_MaxTimer;
	float m_timer = 0.f;
	bool m_chargeShoot = false;
	float m_bulletDamage;
	float m_bulletSpeed=10.f;
	float m_gravitySpeed = 0.f;
	bool m_isEnemy;

	OBJTYPE m_type = TYPE_END;
	int boombStep=0;
};

