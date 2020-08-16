#include "BossTank.h"
#include "Part.h"
#include "Timer.h"
#include "BoxCollider.h"
#include "Player.h"
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
	case IDLE:
		ProgressIdle();
		break;
	case MOVE:
		ProgressMove();
		break;
	case SHOT:
		ProgressShot();
		break;
	case RUSH:
		ProgressRush();
		break;
	default:
		break;
	}
	m_patternTimer += Timer::DeltaTime();
}

void BossTank::ProgressIdle()
{
	if (m_patternTimer >= 2.f)
	{
		std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(ObjectMgr::GetInstance()->GetFrontObject(PLAYER));

		int lenToPlayer, xDist, yDist;
		xDist = player->GetPos().x - GetPos().x;
		yDist = player->GetPos().y - GetPos().y;
		lenToPlayer = sqrtf(xDist * xDist + yDist * yDist);

		if (lenToPlayer <= 3.f)
			SetPattern(MOVE);
		else if (lenToPlayer <= 8.f)
			SetPattern(SHOT);
		else
			SetPattern(RUSH_READY);
	}
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

void BossTank::ProgressRushReady()
{
}
