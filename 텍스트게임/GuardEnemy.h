#pragma once
#include "GameObject.h"
#include "Enemy.h"
class GuardEnemy : public Enemy
{
public:
	GuardEnemy(POS position);
	//virtual ~GuardEnemy();
	/*
	// GameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual int LateUpdate() override;
	void SetHp(float damage);

	void Knockback();
	const STATUS& GetStatus()const { return m_Status; }

private:

	ObjectMgr* objectMgr = ObjectMgr::GetInstance();

	bool m_dir = true; //�������� Ʈ����
	//bool isGround = true;
	float m_MoveCount = 0;
	float m_timer = 0.f;
	STATUS m_Status;
	*/

private:
	STATUS m_Status;
};


