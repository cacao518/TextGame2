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
	virtual void Render();
	const char* GetName();
	POS GetPos();

	bool GetIsAttacked();
	void SetIsAttacked(bool flag);
	bool GetIsLand();
	void SetIsLand(bool flag);
	int GetWidth();
	int GetHeight();
protected:
	char* m_sprite;
	int m_width, m_height;
	POS m_pos;

	const char* m_name = nullptr;

	bool m_isAttacked = false; // 공격 당함
	bool m_isLand = false; // 지형에 서있음
};

