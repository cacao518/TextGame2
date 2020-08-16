#pragma once
#include "GameObject.h"
class Boss :
	public GameObject
{
public:
	Boss(POS pos);
	virtual ~Boss();

	// GameObject��(��) ���� ��ӵ�
	virtual int Update() = 0;
	virtual int LateUpdate() = 0;

	STATUS& GetStatus() { return m_status; }
	void GetDamage(float damage);
protected:


	STATUS m_status;
	
};

