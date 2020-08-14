#pragma once
#include "GameObject.h"
class Enemy :public GameObject
{
public:
	Enemy(POS position);
	virtual ~Enemy();

	// GameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual int LateUpdate() override;
	void SetHp(float damage);
	STATUS m_Status;

private:

	ObjectMgr* objectMgr = ObjectMgr::GetInstance();

	bool m_dir = true; //�������� Ʈ����
	//bool isGround = true;
	float m_MoveCount = 0;
	float m_timer = 0.f;
	
};

