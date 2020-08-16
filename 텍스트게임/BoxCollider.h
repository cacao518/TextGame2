#pragma once
#include "Header.h"
#include "GameObject.h"

// �⺻������ Terrain�� ������ �� �ְ�, �浹 üũ�Ϸ��� �� ��ü ��� BoxCollider�� ������ �־�� �ϰ�
// �� ��ü �̻� isTrigger�� ���� �־�� �Ѵ�. 
class BoxCollider {

private:
	std::weak_ptr<GameObject> parentObject;
	//std::list<std::shared_ptr<GameObject>> m_ObjList[TYPE_END];
public:
	bool isTrigger; // ture �̸� ���� ��ü�� ��� obj ��ȸ�� ����.

public:
	BoxCollider(std::shared_ptr<GameObject>& obj);
	~BoxCollider();

	void Update();
	
	std::shared_ptr<GameObject> OnTriggerEnter(wchar_t* otherObjName); // �浹�� ������Ʈ�� ��ȯ�մϴ�.
	bool GetIsTrigger();
	void SetIsTrigger(bool mode);

private:
	int TerrainCheck(std::shared_ptr<GameObject>& obj1, std::shared_ptr<GameObject>& obj2);
	std::shared_ptr<GameObject> TriggerCheck(wchar_t* otherObjName);

};