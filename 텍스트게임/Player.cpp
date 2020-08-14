#include "Player.h"
#include "Timer.h"
#include "Bullet.h"
Player::Player(POS position)
	:GameObject(position),m_Status(STATUS(10.f,10.f,10.f))
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
	

	m_name = "Player";
	m_color = 9;

	char leftImg[6] = { ' ', '0', '<', ']', ' ', 'L' };
	memcpy(m_leftImg, leftImg, sizeof(char)*m_width*m_height);

	char rightImg[6] = { '0', ' ', '[', 'r', 'L', ' ' };
	memcpy(m_rightImg, rightImg, sizeof(char)*m_width*m_height);

	char attackImg[6] = { '0', ' ', '[', 'r', 'L', ' ' };
	memcpy(m_attackImg, attackImg, sizeof(char)*m_width*m_height);

	m_sprite = new char[m_width * m_height];
	memcpy(m_sprite, rightImg, sizeof(char) * m_width * m_height);
}

Player::~Player()
{
	KeyUpdate.join();
}

int Player::Update()
{
	keyLock.lock();

	//isDone = keyPress[27];

	if (keyPress[72] && GetIsLand()) {
		m_pos.y-=Timer::DeltaTime()*30; //속도같은거 곱하면 됩니다
	}
	if (keyPress[80]) {
		//m_pos.y += Timer::DeltaTime() * 10;
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

	if (!GetIsLand()) // 공중에 떠있는 상태
		m_pos.y += Timer::DeltaTime() * 5.0f;
	else // 충돌한 벽에 서있기
		m_pos.y = GetCollisionObjPos().y;

	keyPress.reset();
	keyLock.unlock();

	if (attack)
	{
		attack = false;
		objectMgr->InsertObject(ObjectMgr::BULLET, std::dynamic_pointer_cast<GameObject>(std::make_shared<Bullet>(m_dir, POS(m_pos.x, m_pos.y + 1))));

	}
	if (m_dir)
		memcpy(m_sprite, m_rightImg, sizeof(char) * m_width * m_height);
	else
		memcpy(m_sprite, m_leftImg, sizeof(char) * m_width * m_height);

	return 1;
}

int Player::LateUpdate()
{
	ScrollMgr::GetInstance()->ScrollMap(m_pos);
	return 1;
}



void Player::SetHp(int damage)
{
	m_Status.hp -= damage;
}



STATUS Player::GetStatus()
{
	return m_Status;
}


