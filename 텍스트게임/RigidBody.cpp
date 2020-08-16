#include "RigidBody.h"
#include "Timer.h"

RigidBody::RigidBody(std :: shared_ptr<GameObject>& obj)
{
	mass = 3;
	gravitySpeed = 0;
	parentObject = obj;
}

RigidBody::~RigidBody()
{
}

void RigidBody::Update()
{
	std::shared_ptr<GameObject> parentobj = parentObject.lock();
	if (!parentobj)
		return;

	if (parentobj->GetIsLand() == false) // 공중 상태
	{
		//parentObject->SetIsLand(false);
		parentobj->SetCollisionObjPos(POS());
	}
	if (gravitySpeed > 0) // 상승
	{
		parentobj->SetPos(POS(parentobj->GetPos().x, parentobj->GetPos().y - Timer::DeltaTime() * 4));
		gravitySpeed -= Timer::DeltaTime() * 5.0f;
	}

//	if (!parentObject->GetIsLand() && gravitySpeed <= 0) // 하강
	//	parentObject->SetPos(POS(parentObject->GetPos().x, parentObject->GetPos().y + Timer::DeltaTime() * mass));
	else if (gravitySpeed <= 0)// 충돌한 벽에 서있기
	{
		parentobj->SetPos(POS(parentobj->GetPos().x, parentobj->GetCollisionObjPos().y));
		//m_jumpCount = 0;
		gravitySpeed = 0;
	}
}


void RigidBody::AddForce(int powerX, int powerY)
{
	std::shared_ptr<GameObject> parentobj = parentObject.lock();
	if (!parentobj)
		return;
	parentobj->SetPos(POS(parentobj->GetPos().x + powerX, parentobj->GetPos().y));
	gravitySpeed += powerY;
}
