#include "Player.h"



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

	char heroImg[4] = { '[',']','[',']' };
	this->width = 2;
	this->height = 2;
	this->sprite = new char[width * height];
	memcpy(sprite, heroImg, sizeof(char) * width * height);

	name = "Player";
}

Player::~Player()
{
	KeyUpdate.join();
}

int Player::Update()
{
	keyLock.lock();

	//isDone = keyPress[27];

	if (keyPress[72]) {
		pos.y--;
	}
	if (keyPress[80]) {
		pos.y++;
	}
	if (keyPress[75]) {
		pos.x--;
	}
	if (keyPress[77]) {
		pos.x++;
	}

	keyPress.reset();
	keyLock.unlock();
	return 1;
}

int Player::LateUpdate()
{
	return 1;
}
