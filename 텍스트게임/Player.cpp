#include "Player.h"
#include "Timer.h"
#include "Bullet.h"
#include "RigidBody.h"
#include "BoxCollider.h"
#include "Enemy.h"
#include "Vehicle.h"
#include "ChargeParticle1.h"

Player::Player(POS position)
	:GameObject(position),m_Status(STATUS(100.f,100.f,3.f))
{
	KeyUpdate=std::thread([&] {
		int c;
		while (true) {
			c = _getch();
			if (c < 256) {
				keyLock.lock();
				keyPress[c] = 1;
				keyLock.unlock();
				if (c == 27) {
					break;
				}
			}

		}
	});
	
	m_width = 2;
	m_height = 3;
	

	m_name = L"Player";
	m_color = 9;
	//wchar_t leftImg[6] = { ' ', '0', '<', ']', ' ', 'L' };
	//memcpy(m_leftImg, leftImg, sizeof(wchar_t)*m_width*m_height);

	wchar_t leftImg[6] = { ' ', '0', '<', ']', ' ', 'L' };
	memcpy(m_leftImg, leftImg, sizeof(wchar_t)*m_width*m_height);

	wchar_t rightImg[6] = { '0', ' ', '[', 'r', 'L', ' ' };
	memcpy(m_rightImg, rightImg, sizeof(wchar_t)*m_width*m_height);

	wchar_t attackImg[6] = { '0', ' ', '[', 'r', 'L', ' ' };
	memcpy(m_attackImg, attackImg, sizeof(wchar_t)*m_width*m_height);

	wchar_t tankImg[14] = { L' ',L' ',L' ',L'm',L'=',L'=',L'>',L'(',L'(',L'(',L'-',L')',L')',L')' };
	memcpy(m_tankImg, tankImg, sizeof(wchar_t) * 7 * 2);

	m_sprite = new wchar_t[m_width * m_height];
	memcpy(m_sprite, rightImg, sizeof(wchar_t) * m_width * m_height);
}

Player::~Player()
{
	KeyUpdate.join();
}

int Player::Update()
{
	auto otherObj = GetComponent<BoxCollider>()->OnTriggerEnter(L"Enemy");
	if (otherObj != nullptr)
	{
		std::shared_ptr<Enemy> E = std::dynamic_pointer_cast<Enemy>(otherObj);
		GetDamage(E->GetStatus().attackDamage, E->GetPos());
	}
	//else
		//SetIsAttacked(false);

	keyLock.lock();


	//isDone = keyPress[27];
	if (keyPress['s'] && (GetIsLand() || m_jumpCount < 2)) {
		GetComponent<RigidBody>()->AddForce(0, m_jumpPower);
		m_jumpCount++;
	}
	/*
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)

	{

		printf("아래키누름");

	}*/
	if (keyPress['a']) {
		if (!m_charging)
			Attack(false);
		else
			m_colorCount = -100;
	}
	if (keyPress[75]) {
		if(!m_isRide)
			m_dir = false;
		m_pos.x -= Timer::DeltaTime() * 10;
	}
	if (keyPress[77]) {
		m_dir = true;
		m_pos.x += Timer::DeltaTime() * 10;
	}

	if (keyPress['d']) {
		m_charging = true; 
	}
	if (keyPress[VK_SPACE] && m_isRide) // 슬러그 내리기
	{
		GetComponent<RigidBody>()->AddForce(0, m_jumpPower);
		m_isRide = false;
		m_color = 8;
		m_invincibility = true;
		m_isAttacked = true;
		m_width = 2;
		m_height = 3;
		memcpy(m_sprite, m_rightImg, sizeof(wchar_t) * m_width * m_height);

		std::shared_ptr<Vehicle> tank = std::make_shared<Vehicle>(POS(m_pos.x-2, m_pos.y-1));
		objectMgr->InsertObject(VEHICLE, std::dynamic_pointer_cast<GameObject>(tank));

		RigidBody* rb4 = new RigidBody(std::dynamic_pointer_cast<GameObject>(tank));
		tank->AddComponent(rb4);
		BoxCollider* bc4 = new BoxCollider(std::dynamic_pointer_cast<GameObject>(tank));
		tank->AddComponent(bc4);
	}

	//std::shared_ptr<ChargeParticle1>particle = std::make_shared<ChargeParticle1>(POS(m_pos.x, m_pos.y));
	//objectMgr->InsertObject(PARTICLE, std::dynamic_pointer_cast<GameObject>(particle));
	//피격
	if (m_isAttacked) {
		m_timer += Timer::DeltaTime();
		//무적 종료 , 색 복귀, 타이머 초기화, 반복문종료
		if (m_timer > 2) {
			if (!m_charging) m_invincibility = false; m_color = 9;  m_timer = 0; m_isAttacked = false;
		}
	}
	//차징샷
	if (m_charging)
	{
		//particle->SetUpdatePos(m_pos.x, m_pos.y, m_color);
		m_colorCount += Timer::DeltaTime();
		if ((int)m_colorCount % 2==0)
		{
			
			if (m_color !=14) m_color = 14;
			else m_color = 13;
		}

		//차징샷발사 , 색 복귀, 타이머 초기화, 반복문종료
		if (m_colorCount <0) {
			Attack(true);
			m_color = 9;  m_colorCount = 0;  m_charging = false;
		//	particle->SetIsLife(false);
		}
	}
	if (keyPress[VK_ESCAPE])
		ObjectMgr::GetInstance()->done = true;

	if (GetIsLand() && GetComponent<RigidBody>()->gravitySpeed <= 0)
		m_jumpCount = 0;

	keyPress.reset();
	keyLock.unlock();

	if (m_dir)
		memcpy(m_sprite, m_rightImg, sizeof(wchar_t) * m_width * m_height);
	else
		memcpy(m_sprite, m_leftImg, sizeof(wchar_t) * m_width * m_height);

	if (m_isRide) // 슬러그 탔을때 이미지 변화
	{
		m_width = 7;
		m_height = 2;
		m_dir = true;
		m_color = CYAN;
		memcpy(m_sprite, m_tankImg, sizeof(wchar_t) * m_width * m_height);
	}

	return 1;
}

int Player::LateUpdate()
{
	ScrollMgr::GetInstance()->ScrollMap(m_pos);

	return 1;
}





void Player::SetHp(float damage)
{
	printf("%f", m_Status.hp);
	m_Status.hp -= damage;
}

STATUS Player::GetStatus()
{
	return m_Status;
}

void Player::Knockback(POS otherObjPos)
{
	if (m_dir)
		GetComponent<RigidBody>()->AddForce(Timer::DeltaTime() * -12, 0);
	else
		GetComponent<RigidBody>()->AddForce(Timer::DeltaTime() * 12, 0);
}

void Player::GetDamage(float damage, POS enemyPos)
{
	if (!m_invincibility)
	{
		//색변하고 무적
		m_color = 8;
		m_invincibility = true;
		//차징끊김
		m_charging = false;
		m_colorCount = 0;
		//particle->SetIsLife(false);

		SetIsAttacked(true);
		
		SetHp(damage);
		Knockback(enemyPos);
		printf("플레이어 공격 당함");
	}
}

void Player::SetIsRide(int flag)
{
	m_isRide = flag;
}

int Player::GetIsRide()
{
	return m_isRide;
}



//true면 차지샷
void Player::Attack(bool charge)
{
	int x, y;
	x = m_pos.x;
	y = m_pos.y + 1;
	if (m_isRide) // 슬러그는 앞면만 바라보게 한다.
	{
		x = m_pos.x + 6;
		y = m_pos.y;
	}
	std::shared_ptr<Bullet> bullet = nullptr;
	
	if(!charge)
		bullet=std::make_shared<Bullet>(false, false, Bullet::HANDGUN, m_dir, POS(x, y));
	else
		bullet = std::make_shared<Bullet>(false, true, Bullet::HANDGUN, m_dir, POS(x, y));
	
	if (!charge && m_isRide)
		bullet = std::make_shared<Bullet>(false, false, Bullet::TANKGUN, m_dir, POS(x, y));
	else if(m_isRide)
		bullet = std::make_shared<Bullet>(false, true, Bullet::TANKGUN, m_dir, POS(x, y));

	objectMgr->InsertObject(BULLET, std::dynamic_pointer_cast<GameObject>(bullet));
	BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(bullet));
	bullet->AddComponent(bc);
	bc->SetIsTrigger(true);

 }





