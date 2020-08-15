#pragma once
#include "GameObject.h"
class LogoObj :
	public GameObject
{
public:
	LogoObj();
	virtual ~LogoObj();

	// GameObject을(를) 통해 상속됨
	virtual int Update();
	virtual int LateUpdate();
};

