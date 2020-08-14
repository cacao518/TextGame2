#include "Player.h"
#include "Timer.h"
#include "Bullet.h"
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
	wchar_t leftImg[6] = { ' ', '0', '<', ']', ' ', 'L' };
	memcpy(m_leftImg, leftImg, sizeof(wchar_t)*m_width*m_height);

	wchar_t rightImg[6] = { '0', ' ', '[', 'r', 'L', ' ' };
	memcpy(m_rightImg, rightImg, sizeof(wchar_t)*m_width*m_height);

	wchar_t attackImg[6] = { '0', ' ', '[', 'r', 'L', ' ' };
	memcpy(m_attackImg, attackImg, sizeof(wchar_t)*m_width*m_height);

	m_sprite = new wchar_t[m_width * m_height];
	memcpy(m_sprite, rightImg, sizeof(wchar_t) * m_width * m_height);
}

Player::~Player()
{
	KeyUpdate.join();
}

int Player::Update()
{
	keyLock.lock();

	//isDone = keyPress[27];
	if (keyPress[72] && (GetIsLand() || m_jumpCount < 2)) {
		m_gravitySpeed += m_jumpPower;
		m_jumpCount++;
	}
	if (keyPress[80]) {
		attack = true;
	}
	if (keyPress[75]) {
		m_dir = false;
		m_pos.x -= Timer::DeltaTime() * 10;
	}
	if (keyPress[77]) {
		m_dir = true;
		m_pos.x += Timer::DeltaTime() * 10;
	}
	if (keyPress[VK_ESCAPE])
		ObjectMgr::GetInstance()->done = true;

	if (m_collisionCount == 0) // 충돌한 벽이 없으면 공중 상태
	{
		m_isLand = false;
		SetCollisionObjPos(POS());
	}
	if (m_gravitySpeed > 0)
	{
		m_pos.y -= Timer::DeltaTime() * 4;
		m_gravitySpeed -= Timer::DeltaTime() * 5.0f;
	}

	//printf("%d", m_gravitySpeed);
	if (!GetIsLand() && m_gravitySpeed <= 0) // 하강
		m_pos.y += Timer::DeltaTime() * 3.0f;
	else if(m_gravitySpeed <= 0)// 충돌한 벽에 서있기
	{
		m_pos.y = GetCollisionObjPos().y;
		m_jumpCount = 0;
		m_gravitySpeed = 0;
	}


	keyPress.reset();
	keyLock.unlock();

	if (attack)
	{
		attack = false;
		objectMgr->InsertObject(ObjectMgr::BULLET, std::dynamic_pointer_cast<GameObject>(std::make_shared<Bullet>(m_dir,m_Status.attackDamage ,POS(m_pos.x, m_pos.y + 1))));

	}
	if (m_dir)
		memcpy(m_sprite, m_rightImg, sizeof(wchar_t) * m_width * m_height);
	else
		memcpy(m_sprite, m_leftImg, sizeof(wchar_t) * m_width * m_height);

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

 





