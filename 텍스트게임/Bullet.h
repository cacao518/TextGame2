#pragma once
#include "GameObject.h"
class Bullet :public GameObject
{
public:
	Bullet(bool dir,POS position);
	~Bullet();

	// GameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual int LateUpdate() override;

private:
	std::bitset<0xff> keyPress;
	std::mutex keyLock;
	std::thread KeyUpdate;
	bool m_dir;
};

