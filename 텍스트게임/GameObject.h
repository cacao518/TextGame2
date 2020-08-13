#pragma once
#include "Struct.h"
#include "Header.h"
#include "ObjectMgr.h"
class GameObject
{
public:
	GameObject(char* sprite,int width,int height,POS initPos);
	~GameObject();

public:
	virtual int Update() = 0;
	virtual int LateUpdate() = 0;
	void Render();

protected:
	char* sprite;
	int width, height;
	POS pos;

	const char* name;
};

