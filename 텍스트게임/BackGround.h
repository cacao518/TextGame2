#pragma once
#pragma once
#pragma once
#include "GameObject.h"
#include <fstream>
#include <iostream>

class BackGround :public GameObject
{
public:
	BackGround(POS position);
	~BackGround();

	// GameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual int LateUpdate() override;

};

