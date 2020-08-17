#pragma once
#include "GameObject.h"
class EndingObj :
	public GameObject
{
public:
	EndingObj();
	virtual ~EndingObj();

	// GameObject을(를) 통해 상속됨
	virtual int Update();
	virtual int LateUpdate();
};

