#pragma once
#include "GameObject.h"
class BaseUI :
	public GameObject
{
public:
	BaseUI();
	virtual ~BaseUI();

	// GameObject을(를) 통해 상속됨
	virtual int Update() = 0;
	virtual int LateUpdate() = 0;
	virtual void Render();
};

