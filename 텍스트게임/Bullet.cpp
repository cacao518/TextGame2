#include "Bullet.h"
#include<iostream>

Bullet::Bullet(char* sprite, int width, int height, POS position)
	:GameObject(sprite, width, height, position)
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

	name = "Bullet";

}

Bullet::~Bullet()
{
	KeyUpdate.join();
}

int Bullet::Update()
{
	keyLock.lock();

	//isDone = keyPress[27];

	pos.x += 1;



	keyPress.reset();
	keyLock.unlock();
	return 1;
}

int Bullet::LateUpdate()
{
	return 1;
}

