#pragma once
#include "GameObject.h"
class EndingObj :
	public GameObject
{
public:
	EndingObj();
	virtual ~EndingObj();

	// GameObject��(��) ���� ��ӵ�
	virtual int Update();
	virtual int LateUpdate();
};

