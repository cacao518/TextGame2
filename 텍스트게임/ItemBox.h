#pragma once
#include "Header.h"
#include "Bullet.h"
#include "GameObject.h"

class ItemBox : public GameObject {

public:
	ItemBox(int type, POS position);
	~ItemBox();

	// GameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual int LateUpdate() override;

	void SetType(int type);
	int GetType();
private:
	int m_type; 
	int m_bulletNum;
	float m_weaponSpeed;
};