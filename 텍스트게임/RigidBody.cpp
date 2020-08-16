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
	if (parentObject->GetIsLand() == false) // 공중 상태
	{
		//parentObject->SetIsLand(false);
		parentObject->SetCollisionObjPos(POS());
	}
	if (gravitySpeed > 0) // 상승
	{
		parentObject->SetPos(POS(parentObject->GetPos().x, parentObject->GetPos().y - Timer::DeltaTime() * 4));
		gravitySpeed -= Timer::DeltaTime() * 5.0f;
	}

	if (!parentObject->GetIsLand() && gravitySpeed <= 0) // 하강
		parentObject->SetPos(POS(parentObject->GetPos().x, parentObject->GetPos().y + Timer::DeltaTime() * mass));
	else if (gravitySpeed <= 0)// 충돌한 벽에 서있기
	{
		parentObject->SetPos(POS(parentObject->GetPos().x, parentObject->GetCollisionObjPos().y - parentObject->GetHeight()));
		//m_jumpCount = 0;
		gravitySpeed = 0;
	}
}


void RigidBody::AddForce(int powerX, int powerY)
{
	parentObject->SetPos(POS(parentObject->GetPos().x + powerX, parentObject->GetPos().y));
	gravitySpeed += powerY;
}
