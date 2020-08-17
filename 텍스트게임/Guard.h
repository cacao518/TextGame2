#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include"GuardEnemy.h"
class Guard : public GuardEnemy
{
public:
	Guard(POS position);
	void GetDamage(float damage, bool dir);
	

private:
	STATUS m_Status;

	wchar_t monsterImg2_LEFT[6] =
	{ '[','[','[', '[','[','[' };
};


