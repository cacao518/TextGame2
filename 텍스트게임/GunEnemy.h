#pragma once
#include "GameObject.h"
#include "Enemy.h"
class GunEnemy : public Enemy
{
public:
	GunEnemy(POS position);
	void GetDamage(float damage, bool dir);
	int Update();



private:
	STATUS m_Status;
	wchar_t monsterImg2_RIGHT[6] =
	{ '0', ' ', '[', 'r', 'L', ' ' };

	wchar_t monsterImg2_LEFT[6] =
	{ ' ', '0', '<', ']', ' ', 'L' };
};


