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
	if (parentObject->GetIsLand() == false) // ���� ����
	{
		//parentObject->SetIsLand(false);
		parentObject->SetCollisionObjPos(POS());
	}
	if (gravitySpeed > 0) // ���
	{
		parentObject->SetPos(POS(parentObject->GetPos().x, parentObject->GetPos().y - Timer::DeltaTime() * 4));
		gravitySpeed -= Timer::DeltaTime() * 5.0f;
	}

	if (!parentObject->GetIsLand() && gravitySpeed <= 0) // �ϰ�
		parentObject->SetPos(POS(parentObject->GetPos().x, parentObject->GetPos().y + Timer::DeltaTime() * mass));
	else if (gravitySpeed <= 0)// �浹�� ���� ���ֱ�
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
