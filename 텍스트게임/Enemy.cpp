#include "Enemy.h"
#include "Timer.h"
#include "Bullet.h"
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

	char heroImg[6] = { '*', '*', 'M', 'M'};

	m_width = 2;
	m_height = 2;
	m_sprite = new char[m_width * m_height];
	memcpy(m_sprite, heroImg, sizeof(char) * m_width * m_height);

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

	
	//if(m_dir) m_pos.x += 0.1;
	//else  m_pos.x -= 0.1;

	//m_MoveCount++;
	//if(m_MoveCount==100) m_dir
			
	
	//else {
	//	m_MoveCount--;
	//	m_pos.x -= 0.1;
	//}
		


	keyPress.reset();
	keyLock.unlock();
	return 1;

	keyPress.reset();
	keyLock.unlock();


	return 1;
}

int Enemy::LateUpdate()
{
	ScrollMgr::GetInstance()->ScrollMap(m_pos);
	return 1;
}
