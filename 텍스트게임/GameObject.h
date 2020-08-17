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
	bool m_dir = true; //�������� Ʈ����
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
			return reinterpret_cast<T*>(v); // v�� ������Ÿ���� T* ������ Ÿ������ ��ȯ
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

	bool m_isAttacked = false; // ���� ����
	bool m_isLand = false; // ������ ������
	POS m_collisionObjPos; // �浹 ���� ������Ʈ pos
	bool m_Life = true;
	

	//int m_collisionCount = 0; // �浹 ī��Ʈ
	//float m_gravitySpeed = 0;
};