#include "BossTank.h"
#include "Part.h"
#include "BoxCollider.h"
BossTank::BossTank(POS pos)
	:Boss(pos),m_upPart(nullptr),m_downPart(nullptr)
{
	m_width = 24;
	m_height = 23;
	m_upPart = std::make_shared<Part>("Boss1_UpPart.txt", 30, 11, YELLOW,this);
	m_downPart = std::make_shared<Part>("Boss1_DownPart.txt", 30, 12, BLUE,this);
	BoxCollider* upCollider = new BoxCollider(std::dynamic_pointer_cast<GameObject>(m_upPart));
	upCollider->SetIsTrigger(true);
	m_upPart->AddComponent(upCollider);



	m_upPart->SetIsDamagedPart(true);
	m_upPart->SetIsDamagingPart(true);

	m_downPart->SetIsDamagingPart(true);

	m_name = L"Boss";
	m_status = STATUS(50.f, 5.f, 10.f);
	m_curPattern = IDLE;
}

BossTank::~BossTank()
{
}

int BossTank::Update()
{
	if (m_status.hp <= 0)
		return -1;
	ProgressPattern();

	m_upPart->SetPos(POS(GetPos().x, GetPos().y));
	m_downPart->SetPos(POS(GetPos().x, GetPos().y + m_upPart->GetHeight()));


	m_upPart->Update();
	m_downPart->Update();
	return 0;
}

int BossTank::LateUpdate()
{
	m_upPart->LateUpdate();
	m_downPart->LateUpdate();
	return 0;
}

void BossTank::Render()
{
	if (m_upPart)
		m_upPart->Render();
	if (m_downPart)
		m_downPart->Render();
}

void BossTank::ProgressPattern()
{
	switch (m_curPattern)
	{
	default:
		break;
	}
}

void BossTank::ProgressIdle()
{
}

void BossTank::ProgressMove()
{
}

void BossTank::ProgressShot()
{
}

void BossTank::ProgressRush()
{
}
