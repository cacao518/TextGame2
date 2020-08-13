#pragma once
#include "GameObject.h"
class Bullet :public GameObject
{
public:
	Bullet(char* sprite, int width, int height, POS position);
	~Bullet();

	// GameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual int LateUpdate() override;

private:
	std::bitset<0xff> keyPress;
	std::mutex keyLock;
	std::thread KeyUpdate;

};

