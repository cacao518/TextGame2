#pragma once
#include "Header.h"
#include "GameObject.h"

// 기본적으로 Terrain에 착지할 수 있고, 충돌 체크하려면 두 객체 모두 BoxCollider를 가지고 있어야 하고
// 한 객체 이상 isTrigger가 켜져 있어야 한다. 
class BoxCollider {

private:
	std::weak_ptr<GameObject> parentObject;
	//std::list<std::shared_ptr<GameObject>> m_ObjList[TYPE_END];
public:
	bool isTrigger; // ture 이면 나를 주체로 모든 obj 순회를 돈다.

public:
	BoxCollider(std::shared_ptr<GameObject>& obj);
	~BoxCollider();

	void Update();
	
	std::shared_ptr<GameObject> OnTriggerEnter(wchar_t* otherObjName); // 충돌한 오브젝트를 반환합니다.
	bool GetIsTrigger();
	void SetIsTrigger(bool mode);

private:
	int TerrainCheck(std::shared_ptr<GameObject>& obj1, std::shared_ptr<GameObject>& obj2);
	std::shared_ptr<GameObject> TriggerCheck(wchar_t* otherObjName);

};