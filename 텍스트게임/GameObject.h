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
	POS GetCollisionObjPos();
	void SetCollisionObjPos(POS pos);
	int GetCollisionCount();
	void AddCollisionCount();
	void SubCollisionCount();
protected:
	wchar_t* m_sprite;
	int m_width, m_height;
	POS m_pos;

	const char* m_name = nullptr;

	bool m_isAttacked = false; // 공격 당함
	bool m_isLand = false; // 지형에 서있음
	POS m_collisionObjPos; // 충돌 당한 오브젝트 pos
	int m_collisionCount = 0; // 충돌 카운트
};

