#pragma once
#include "Header.h"
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
	int m_type = 0; // 0:헤비머신건, 1:샷건

};