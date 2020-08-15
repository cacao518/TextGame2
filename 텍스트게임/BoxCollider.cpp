#include "BoxCollider.h"

BoxCollider::BoxCollider(std::shared_ptr<GameObject>& obj)
{
	isTrigger = false;
	parentObject = obj;
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Update()
{
	for (auto& object : ObjectMgr::GetInstance()->m_ObjectList[TERRAIN])
	{
		if (TerrainCheck(parentObject, object) == 1)
			break;

		parentObject->SetIsLand(false);
	}
}
std::shared_ptr<GameObject> BoxCollider::OnTriggerEnter(wchar_t* otherObjName)
{
	return TriggerCheck(otherObjName);
}
std::shared_ptr<GameObject> BoxCollider::TriggerCheck(wchar_t* otherObjName)
{
	int Type = 0;
	if (!wcscmp(otherObjName, L"Player")) Type = PLAYER;
	else if (!wcscmp(otherObjName, L"Enemy")) Type = ENEMY;
	else if (!wcscmp(otherObjName, L"Bullet")) Type = BULLET;

	for (auto& otherObj : ObjectMgr::GetInstance()->m_ObjectList[Type])
	{
		if (parentObject->GetPos().x + parentObject->GetWidth() - 1 >= otherObj->GetPos().x &&
			parentObject->GetPos().x <= otherObj->GetPos().x &&
			parentObject->GetPos().y + parentObject->GetHeight() - 1 >= otherObj->GetPos().y &&
			parentObject->GetPos().y <= otherObj->GetPos().y)
		{
			if(otherObj->GetComponet<BoxCollider>() != nullptr)
				if(isTrigger || otherObj->GetComponet<BoxCollider>()->GetIsTrigger()) // 두 객체중 한 객체라도 isTrigger가 on 이면 충돌 가능.
					return otherObj;
		}
	}
	return nullptr;
}
int BoxCollider::TerrainCheck(std::shared_ptr<GameObject>& obj1, std::shared_ptr<GameObject>& obj2)
{
	if (obj1->GetPos().x + obj1->GetWidth() - 1 >= obj2->GetPos().x &&
		obj1->GetPos().x <= obj2->GetPos().x &&
		obj1->GetPos().y + obj1->GetHeight() - 1 >= obj2->GetPos().y - 1 &&
		obj1->GetPos().y <= obj2->GetPos().y - 1)
	{
		if (!(obj1->GetIsLand()))
		{
			obj1->SetIsLand(true);
			obj1->SetCollisionObjPos(obj2->GetPos());
			return 1;
		}
	}
	return 0;
}


bool BoxCollider::GetIsTrigger()
{
	return isTrigger;
}

void BoxCollider::SetIsTrigger(bool mode)
{
	isTrigger = mode;
}
