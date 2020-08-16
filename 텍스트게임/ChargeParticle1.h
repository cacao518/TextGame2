#pragma once
#include "GameObject.h"
class ChargeParticle1 :public GameObject
{
public:
	ChargeParticle1(POS position);
	~ChargeParticle1();

	// GameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual int LateUpdate() override;
	void EndParticle();

	//���� �Ѱ��� �����ε��ϱ�
	void SetUpdatePos(float m_Parent_x, float m_Parent_y,int m_ParentColor);

private:
	float m_Parent_x ;
	float m_Parent_y ;
	int m_ParentColor;
	float m_timer = 0.f;
	

};

