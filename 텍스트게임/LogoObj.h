#pragma once
#include "GameObject.h"
class LogoObj :
	public GameObject
{
public:
	LogoObj();
	virtual ~LogoObj();

	// GameObject��(��) ���� ��ӵ�
	virtual int Update();
	virtual int LateUpdate();
};

