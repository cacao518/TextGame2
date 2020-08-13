#pragma once
#include "GameObject.h"
class Player:public GameObject
{
public:
	Player(char* sprite, int width, int height, POS position);
	~Player();

	// GameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual int LateUpdate() override;

private:
	std::bitset<0xff> keyPress;
	std::mutex keyLock;
	std::thread KeyUpdate;
};

