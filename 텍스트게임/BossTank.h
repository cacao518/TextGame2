#pragma once
#include "Boss.h"
class BossTank :
	public Boss
{
	BossTank(POS pos);
	virtual ~BossTank();
	// Boss��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual int LateUpdate() override;
};

