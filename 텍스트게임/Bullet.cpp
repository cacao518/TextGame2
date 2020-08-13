#include "Bullet.h"
#include<iostream>

Bullet::Bullet(POS position)
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
	char bulletImg[2] = { '0','0' };

	m_width = 2;
	m_height = 1;
	m_sprite = new char[m_width * m_height];
	memcpy(m_sprite, bulletImg, sizeof(char) * m_width * m_height);


	m_name = "Bullet";

}

Bullet::~Bullet()
{
	KeyUpdate.join();
}

int Bullet::Update()
{
	keyLock.lock();

	//isDone = keyPress[27];

	m_pos.x += 0.1;



	keyPress.reset();
	keyLock.unlock();
	return 1;
}

int Bullet::LateUpdate()
{
	return 1;
}

