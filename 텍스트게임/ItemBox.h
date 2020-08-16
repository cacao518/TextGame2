#pragma once
#include "Header.h"
#include "GameObject.h"

class ItemBox : public GameObject {

public:
	ItemBox(int type, POS position);
	~ItemBox();

	// GameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual int LateUpdate() override;

	void SetType(int type);
	int GetType();
private:
	int m_type = 0; // 0:���ӽŰ�, 1:����

};