#pragma once
#include "GameObject.h"
class Bullet :public GameObject
{
public:
	Bullet(bool dir,POS position);
	~Bullet();

	// GameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual int LateUpdate() override;

private:

	bool m_dir;
};

