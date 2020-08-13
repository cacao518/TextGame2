#pragma once
#include "Struct.h"
#include "Header.h"
#include "ObjectMgr.h"
#include "ScrollMgr.h"

class GameObject
{
public:
	GameObject(POS initPos);
	virtual ~GameObject();

public:
	virtual int Update() = 0;
	virtual int LateUpdate() = 0;
	void Render();

protected:
	char* m_sprite;
	int m_width, m_height;
	POS m_pos;

	const char* m_name = nullptr;
};

