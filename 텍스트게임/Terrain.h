#pragma once
#pragma once
#include "GameObject.h"
class Terrain :public GameObject
{
public:
	Terrain(char* sprite, int width, int height, POS position);
	~Terrain();

	// GameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual int LateUpdate() override;

};

