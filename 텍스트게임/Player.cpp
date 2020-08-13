#include "Player.h"
#include "Timer.h"
#include "Bullet.h"
Player::Player(POS position)
	:GameObject(position)
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

	char heroImg[6] = { '0',' ','[','r','L',' ' };
	m_width = 2;
	m_height = 3;
	m_sprite = new char[m_width * m_height];
	memcpy(m_sprite, heroImg, sizeof(char) * m_width * m_height);

	m_name = "Player";
}

Player::~Player()
{
	KeyUpdate.join();
}

int Player::Update()
{
	keyLock.lock();

	//isDone = keyPress[27];

	if (keyPress[72] && isGround) {
		m_pos.y-=Timer::DeltaTime()*10; //속도같은거 곱하면 됩니다
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

	if (m_pos.y >= 20)
		isGround = true;

	if (m_pos.y < 20)
		isGround = false;

	if (!isGround)
		m_pos.y += Timer::DeltaTime() * 0.7;


	if (attack)
	{
		attack = false;
		objectMgr->InsertObject(ObjectMgr::BULLET, std::dynamic_pointer_cast<GameObject>(std::make_shared<Bullet>(m_dir,POS(m_pos.x, m_pos.y))));

	}

	keyPress.reset();
	keyLock.unlock();


	return 1;
}

int Player::LateUpdate()
{
	ScrollMgr::GetInstance()->ScrollMap(m_pos);
	return 1;
}
