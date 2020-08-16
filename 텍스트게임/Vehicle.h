#pragma once
#include "Header.h"
#include "GameObject.h"

class Vehicle : public GameObject {

public:
	
	Vehicle(POS position);
	~Vehicle();

	// GameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual int LateUpdate() override;

private:
	std::shared_ptr<GameObject> player;
	bool m_isRide = false;
};