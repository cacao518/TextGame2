#include "BossWizard.h"
#include "Part.h"
#include "Timer.h"
#include "BoxCollider.h"
#include "RigidBody.h"
#include "Player.h"
#include "Bullet.h"
#include "ObjectMgr.h"
BossWizard::BossWizard(POS pos)
	:Boss(pos), m_leftPart(nullptr), m_rightPart(nullptr),m_centerPart(nullptr),m_setAttackPosition(false),m_attackPosCount(0)
{
	m_width = 24;
	m_height = 23;
	m_leftPart = std::make_shared<Part>("Boss2_LeftPart.txt", 6, 11, YELLOW, this);
	m_rightPart = std::make_shared<Part>("Boss2_RightPart.txt", 6, 11, YELLOW, this);
	m_centerPart = std::make_shared<Part>("Boss2_CenterPart.txt", 13, 25, BLUE, this);
	
	BoxCollider* leftCollider = new BoxCollider(std::dynamic_pointer_cast<GameObject>(m_leftPart));
	leftCollider->SetIsTrigger(true);
	m_leftPart->AddComponent(leftCollider);


	BoxCollider* rightCollider = new BoxCollider(std::dynamic_pointer_cast<GameObject>(m_rightPart));
	rightCollider->SetIsTrigger(true);
	m_rightPart->AddComponent(rightCollider);

	BoxCollider* centerCollider = new BoxCollider(std::dynamic_pointer_cast<GameObject>(m_centerPart));
	centerCollider->SetIsTrigger(true);
	m_centerPart->AddComponent(centerCollider);


	m_leftPart->SetIsDamagedPart(true);
	m_leftPart->SetIsDamagingPart(true);

	m_rightPart->SetIsDamagedPart(true);
	m_rightPart->SetIsDamagingPart(true);

	m_centerPart->SetIsDamagingPart(true);

	m_name = L"Boss";
	m_status = STATUS(100.f, 8.f, 10.f);
	m_curPattern = NOT_RECOGNIZE;
	m_dir = false;
	UpdateCenterPos();
}

BossWizard::~BossWizard()
{
}

int BossWizard::Update()
{
	UpdateCenterPos();
	if (m_status.hp <= 0)
		return -1;
	ProgressPattern();

	m_leftPart->SetPos(POS(GetPos().x, GetPos().y+9.f));
	m_centerPart->SetPos(POS(GetPos().x+6.f, GetPos().y));
	m_rightPart->SetPos(POS(GetPos().x+19.f, GetPos().y+9.f));


	m_leftPart->Update();
	m_centerPart->Update();
	m_rightPart->Update();
	return 0;
}

int BossWizard::LateUpdate()
{
	m_leftPart->LateUpdate();
	m_centerPart->LateUpdate();
	m_rightPart->LateUpdate();
	return 0;
}

void BossWizard::Render()
{
	if (m_leftPart)
		m_leftPart->Render();
	if (m_centerPart)
		m_centerPart->Render();
	if (m_rightPart)
		m_rightPart->Render();

	if (m_setAttackPosition)
	{
		wchar_t meteorPos[4] = { L'=',L'=',L'=',L'=' };
		wchar_t earthquakePos[8] = { L'~', L'~', L'~', L'~', L'~', L'~', L'~', L'~' };
		for (auto iter = m_attackPosition.begin(); iter != m_attackPosition.end(); ++iter)
		{
			switch (m_curPattern)
			{
			case BossWizard::METEOR_READY:
			case BossWizard::METEOR:
				ObjectMgr::GetInstance()->Draw(meteorPos, 4, 1, (int)((*iter).x-ScrollMgr::GetInstance()->GetScrollX()), (int)((*iter).y-ScrollMgr::GetInstance()->GetScrollY()), LIGHTGREEN);
				break;
			case BossWizard::EARTHQUAKE_READY:
			case BossWizard::EARTHQUAKE:
				ObjectMgr::GetInstance()->Draw(earthquakePos, 8, 1, (int)((*iter).x - ScrollMgr::GetInstance()->GetScrollX()), (int)((*iter).y - ScrollMgr::GetInstance()->GetScrollY()), LIGHTGREEN);
				break;
		
			}
		}
	}
}

void BossWizard::UpdateCenterPos()
{
	m_centerPos = m_pos + POS(13.f, 14.f);

}

void BossWizard::ProgressPattern()
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
	case METEOR_READY:
		ProgressMeteorReady();
		break;
	case METEOR:
		ProgressMeteor();
		break;
	case EARTHQUAKE_READY:
		ProgressEarthquakeReady();
		break;
	case EARTHQUAKE:
		ProgressEarthquake();
		break;
	default:
		break;
	}
	m_patternTimer += Timer::DeltaTime();
}

void BossWizard::EnableAttackPosition()
{
	if (m_setAttackPosition)
		return;

	m_setAttackPosition = true;

	std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(ObjectMgr::GetInstance()->GetFrontObject(PLAYER));
	if (nullptr == player)
		return;

	POS playerPos = player->GetPos();
	POS attackPos;
	if (METEOR_READY == m_curPattern)
	{
		m_attackPosCount = 3;

		
		attackPos = POS(playerPos.x - 10.f,4.f);
		m_attackPosition.push_back(attackPos);

		attackPos = POS(playerPos.x,4.f);
		m_attackPosition.push_back(attackPos);

		attackPos = POS(playerPos.x + 10.f,4.f);
		m_attackPosition.push_back(attackPos);
	}
	else if (EARTHQUAKE_READY == m_curPattern)
	{
		m_attackPosCount = 1;

		attackPos = POS(playerPos.x-4.f, playerPos.y+3.f);
		m_attackPosition.push_back(attackPos);
	}
}
	

void BossWizard::DisableAttackPosition()
{
	m_setAttackPosition = false;
	m_attackPosCount = 0;
	m_attackPosition.clear();
}

void BossWizard::ProgressIdle()
{
	if (m_patternTimer >= 1.5f)
	{
		//std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(ObjectMgr::GetInstance()->GetFrontObject(PLAYER));
		//if (nullptr == player)
		//	return;
		////플레이어와 거리 비교
		//float lenToPlayer, xDist, yDist;
		//xDist = player->GetPos().x - m_centerPos.x;
		//yDist = player->GetPos().y - m_centerPos.y;
		//lenToPlayer = sqrtf(xDist * xDist + yDist * yDist);
		srand(time(nullptr));
		int randNum = rand() % 3;
		switch (randNum)
		{
		case 0:
			SetPattern(MOVE);
			break;
		case 1:
			SetPattern(METEOR_READY);
			break;
		case 2:
			SetPattern(EARTHQUAKE_READY);
			break;
		}
	}
}

void BossWizard::ProgressMove()
{
	SetPos(GetPos() + POS(0.f, -m_status.moveSpeed * Timer::DeltaTime()));



	if (m_patternTimer >= 1.5f)
		SetPattern(IDLE);
}

void BossWizard::ProgressMeteor()
{
	for (auto iter = m_attackPosition.begin(); iter != m_attackPosition.end(); ++iter)
	{
		std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(true, false, Bullet::METEOR, m_dir, *iter);
		ObjectMgr::GetInstance()->InsertObject(BULLET, std::dynamic_pointer_cast<GameObject>(bullet));
		BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(bullet));
		bullet->AddComponent(bc);
		bc->SetIsTrigger(true);
	}
	
	DisableAttackPosition();
	SetPattern(IDLE);
}

void BossWizard::ProgressMeteorReady()
{
	EnableAttackPosition();
	m_leftPart->SetColor(LIGHTGREEN);
	m_rightPart->SetColor(LIGHTGREEN);
	if (m_patternTimer >= 2.f)
	{
		SetPattern(METEOR);
		m_leftPart->SetBaseColor();
		m_rightPart->SetBaseColor();
	}
}

void BossWizard::ProgressEarthquake()
{
	for (auto iter = m_attackPosition.begin(); iter != m_attackPosition.end(); ++iter)
	{
		std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(true, false, Bullet::EARTHQUAKE, m_dir, *iter);
		ObjectMgr::GetInstance()->InsertObject(BULLET, std::dynamic_pointer_cast<GameObject>(bullet));
		BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(bullet));
		bullet->AddComponent(bc);
		bc->SetIsTrigger(true);
	}

	DisableAttackPosition();
	SetPattern(IDLE);
}

void BossWizard::ProgressEarthquakeReady()
{
	EnableAttackPosition();
	m_leftPart->SetColor(LIGHTGREEN);
	m_centerPart->SetColor(LIGHTGREEN);
	m_rightPart->SetColor(LIGHTGREEN);
	if (m_patternTimer >= 2.f)
	{
		SetPattern(EARTHQUAKE);
		m_leftPart->SetBaseColor();
		m_centerPart->SetBaseColor();
		m_rightPart->SetBaseColor();
	}
}

void BossWizard::ProgressNotRecognize()
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
