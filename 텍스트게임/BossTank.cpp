#include "BossTank.h"
#include "Part.h"
#include "Timer.h"
#include "BoxCollider.h"
#include "RigidBody.h"
#include "Player.h"
#include "Bullet.h"
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
	m_status = STATUS(50.f, 2.f, 10.f);
	m_curPattern = NOT_RECOGNIZE;
	m_dir = false;
	UpdateCenterPos();
}

BossTank::~BossTank()
{
}

int BossTank::Update()
{
	UpdateCenterPos();
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

void BossTank::UpdateCenterPos()
{
	m_centerPos = m_pos + POS(15.f, 12.f);
}

void BossTank::ProgressPattern()
{
	switch (m_curPattern)
	{
	case NOT_RECOGNIZE:
		ProgressNotRecognize();
		break;
	case IDLE:
		ProgressIdle();
		break;
	case MOVE:
		ProgressMove();
		break;
	case SHOT_READY:
		ProgressShotReady();
		break;
	case SHOT:
		ProgressShot();
		break;
	case RUSH_READY:
		ProgressRushReady();
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
		if (nullptr == player)
			return;
		//플레이어와 거리 비교
		float lenToPlayer, xDist, yDist;
		xDist = player->GetPos().x - m_centerPos.x;
		yDist = player->GetPos().y - m_centerPos.y;
		lenToPlayer = sqrtf(xDist * xDist + yDist * yDist);

		if (lenToPlayer <= 25.f)
			SetPattern(MOVE);
		else if (lenToPlayer <= 40.f)
			SetPattern(SHOT_READY);
		else
			SetPattern(RUSH_READY);
	}
}

void BossTank::ProgressMove()
{
	std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(ObjectMgr::GetInstance()->GetFrontObject(PLAYER));
	if (nullptr == player)
		return;

	
	//플레이어와 거리 비교
	float lenToPlayer, xDist, yDist;
	xDist = player->GetPos().x - m_centerPos.x;
	yDist = player->GetPos().y - m_centerPos.y;
	lenToPlayer = sqrtf(xDist * xDist + yDist * yDist);

	float dir = GetPos().x - player->GetPos().x;
	dir /= fabs(dir);
	if (lenToPlayer <= 30.f)
	{
		SetPos(GetPos() + POS(dir * m_status.moveSpeed*Timer::DeltaTime(), 0));
	}
	else if (lenToPlayer >= 40.f)
	{
		SetPos(GetPos() + POS(-dir * m_status.moveSpeed*Timer::DeltaTime(), 0));
	}

	if (m_patternTimer >= 3.f)
		SetPattern(IDLE);
}

void BossTank::ProgressShot()
{
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(true, false, Bullet::BOSS_CANNON, m_dir, POS(GetPos().x + 2, GetPos().y + 5));
	ObjectMgr::GetInstance()->InsertObject(BULLET, std::dynamic_pointer_cast<GameObject>(bullet));
	BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(bullet));
	bullet->AddComponent(bc);
	bc->SetIsTrigger(true);

	SetPattern(IDLE);
}

void BossTank::ProgressShotReady()
{
	m_upPart->SetColor(LIGHTGREEN);
	if (m_patternTimer >= 3.f)
	{
		SetPattern(SHOT);
		m_upPart->SetBaseColor();
	}
}

void BossTank::ProgressRush()
{
	
	if (m_patternTimer <= 2.f)
		SetPos(GetPos() + POS(-m_status.moveSpeed * 7.f * Timer::DeltaTime(), 0));
	else if (m_patternTimer <= 4.f)
		SetPos(GetPos() + POS(m_status.moveSpeed * 7.f * Timer::DeltaTime(), 0));
	else
		SetPattern(IDLE);

}

void BossTank::ProgressRushReady()
{
	m_upPart->SetColor(LIGHTGREEN);
	m_downPart->SetColor(LIGHTGREEN);
	if (m_patternTimer >= 3.f)
	{
		SetPattern(RUSH);
		m_upPart->SetBaseColor();
		m_downPart->SetBaseColor();
	}
}

void BossTank::ProgressNotRecognize()
{
	std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(ObjectMgr::GetInstance()->GetFrontObject(PLAYER));
	if (nullptr == player)
		return;


	//플레이어와 거리 비교
	float lenToPlayer, xDist, yDist;
	xDist = player->GetPos().x - m_centerPos.x;
	yDist = player->GetPos().y - m_centerPos.y;
	lenToPlayer = sqrtf(xDist * xDist + yDist * yDist);

	if (lenToPlayer <= 40.f)
		SetPattern(IDLE);
}
