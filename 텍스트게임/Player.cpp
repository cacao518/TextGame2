#include "Player.h"
#include "Bullet.h"



Player::Player(POS position)
	:GameObject(sprite,width,height,position)
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

	/*
	if (keyPress[72] && isGround) {
		pos.y -= 5;
	}
	if (keyPress[80]) {
		attack = true;
	}
	if (keyPress[75]) {
		pos.x--;
	}
	if (keyPress[77]) {
		pos.x++;
	}
	*/

	if (keyPress[72]) {
		pos.y-=5; isGround = false;
	}
	if (keyPress[80]) {
		pos.y++; attack = true;
	}
	if (keyPress[75]) {
		pos.x--; dir = false;
	}
	if (keyPress[77]) {
		pos.x++; dir = true;
	}
	
	if (pos.y >= 20)
	isGround = true;

	if (pos.y < 20)
		isGround = false;

	if (!isGround)
		pos.y += 1;
		
	if (attack)
	{
		attack = false;
		objectMgr->InsertObject(ObjectMgr::BULLET, std::dynamic_pointer_cast<GameObject>(std::make_shared<Bullet>(bulletImg, 2, 1, POS(pos.x, pos.y))));

	}

	keyPress.reset();
	keyLock.unlock();
	return 1;
}

int Player::LateUpdate()
{
	return 1;
}
