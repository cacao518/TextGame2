#pragma once
#include "GameObject.h"
#include "Enemy.h"
class GuardEnemy : public Enemy
{
public:
	GuardEnemy(POS position);

	int Update();
	


private:
	STATUS m_Status;
	wchar_t monsterImg2_LEFT[9] =
	{ 
		 '[',' ','0',
		 '[','-','I',
		 '[',' ','L' };
	

	wchar_t monsterImg2_RIGHT[9] =
	{ 
			 '0',' ',']',
			 'I','-',']',
			 'L',' ',']' };
	int baseColor;

};


