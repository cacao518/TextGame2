#include "Enemy.h"
#include "Timer.h"
#include "Bullet.h"
#include "Timer.h"

Enemy::Enemy(POS position)
	:GameObject(position)
{
	KeyUpdate = std::thread([&] {
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

	char monsterImg[4] = { '*', '*', 'M', 'M'};

	m_width = 2;
	m_height = 2;
	m_sprite = new char[m_width * m_height];
	memcpy(m_sprite, monsterImg, sizeof(char) * m_width * m_height);

	m_name = "Enemy";
}

Enemy::~Enemy()
{
	KeyUpdate.join();
}

int Enemy::Update()
{
	keyLock.lock();

	//isDone = keyPress[27];

	
	if(m_dir) m_pos.x += Timer::DeltaTime() * 5;
	else  m_pos.x -= Timer::DeltaTime() * 5;

	m_MoveCount++;
	if (m_MoveCount == 1000)
	{
		m_MoveCount = 0;
		m_dir = !m_dir;
	}
			
	
	
		



	keyPress.reset();
	keyLock.unlock();


	return 1;
}

int Enemy::LateUpdate()
{
	ScrollMgr::GetInstance()->ScrollMap(m_pos);
	return 1;
}
