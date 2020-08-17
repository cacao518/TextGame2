#pragma once
#include "GameObject.h"
#include "Enemy.h"
class GunEnemy : public Enemy
{
public:
	GunEnemy(POS position);
	int Update();



private:
	STATUS m_Status;
	

	ObjectMgr* objectMgr = ObjectMgr::GetInstance();
	
	void DistanceCheck();
	void Attack();
	bool m_bulletDir = false;

	bool Attacking = false;
	wchar_t monsterImg2_RIGHT[6] =
	{ L'0', L' ', L'[', L'r', L'L', L' ' };

	wchar_t monsterImg2_LEFT[6] =
	{ L' ', L'0', L'<', L']', L' ', L'L' };
};


