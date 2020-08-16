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
        std::shared_ptr<GameObject> parentobj = parentObject.lock();
        if (!parentobj)
            break;

        if (TerrainCheck(parentobj, object) == 1)
            break;

        parentobj->SetIsLand(false);
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
    else if (!wcscmp(otherObjName, L"Boss"))Type = BOSS;

    for (auto& otherObj : ObjectMgr::GetInstance()->m_ObjectList[Type])
    {
        std::shared_ptr<GameObject> parentobj = parentObject.lock();
        if (!parentobj)
            break;

		if (parentobj->GetPos().x< otherObj->GetPos().x + otherObj->GetWidth() &&
			parentobj->GetPos().x + parentobj->GetWidth() > otherObj->GetPos().x &&
			parentobj->GetPos().y< otherObj->GetPos().y + otherObj->GetHeight() &&
			parentobj->GetPos().y + parentobj->GetHeight() >otherObj->GetPos().y)
            {
                if (otherObj->GetComponent<BoxCollider>() != nullptr)
                    if (isTrigger || otherObj->GetComponent<BoxCollider>()->GetIsTrigger()) // 두 객체중 한 객체라도 isTrigger가 on 이면 충돌 가능.
                        return otherObj;
            }
	}
	return nullptr;
}
int BoxCollider::TerrainCheck(std::shared_ptr<GameObject>& obj1, std::shared_ptr<GameObject>& obj2)
{
	if (obj1->GetPos().x + obj1->GetWidth() - 1 >= obj2->GetPos().x &&
		obj1->GetPos().x <= obj2->GetPos().x && !(obj1->GetIsLand()))
	{
		if (obj1->GetPos().y + obj1->GetHeight() - 1 >= obj2->GetPos().y - 1 && obj1->GetPos().y <= obj2->GetPos().y - 1)
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