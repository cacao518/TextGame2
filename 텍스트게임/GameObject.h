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
	virtual int ComponentUpdate();
	virtual void Render();
	const wchar_t* GetName();
	POS GetPos();
	void SetPos(POS pos);
	bool GetIsAttacked();
	void SetIsAttacked(bool flag);
	bool GetIsLand();
	void SetIsLand(bool flag);
	void SetIsLife(bool flag);
	void SetColor(int color);
	int GetWidth();
	int GetHeight();
	POS GetCollisionObjPos();
	void SetCollisionObjPos(POS pos);
	int GetCollisionCount();
	void AddCollisionCount();
	void SubCollisionCount();
	bool m_dir = true; //오른쪽이 트루임
	//float GetGravitiySpeed();
	//void SetGravitiySpeed(float gs);
	template<typename T>
	void AddComponent(T* t)
	{
		auto typeName = typeid(T).name();
		componets[typeName] = t;
	}

	template<typename T>
	T* GetComponent()
	{
		auto typeName = typeid(T).name();
		if (componets.find(typeName) != componets.end())
		{
			auto v = componets.at(typeName);
			return reinterpret_cast<T*>(v); // v의 포인터타입을 T* 포인터 타입으로 변환
		}
		return nullptr;
	}

protected:
	std::unordered_map<std::string, void*> componets;
	
	wchar_t* m_sprite;
	int m_width, m_height;
	POS m_pos;
	int m_color;
	const wchar_t* m_name = nullptr;

	bool m_isAttacked = false; // 공격 당함
	bool m_isLand = false; // 지형에 서있음
	POS m_collisionObjPos; // 충돌 당한 오브젝트 pos
	bool m_Life = true;
	

	//int m_collisionCount = 0; // 충돌 카운트
	//float m_gravitySpeed = 0;
};