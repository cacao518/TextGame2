#pragma once
#include "Boss.h"
class BossTank :
	public Boss
{
	BossTank(POS pos);
	virtual ~BossTank();
	// Boss을(를) 통해 상속됨
	virtual int Update() override;
	virtual int LateUpdate() override;
};

