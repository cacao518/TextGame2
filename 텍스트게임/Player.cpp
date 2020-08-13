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
	m_width = 2;
	m_height = 2;
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

	if (keyPress[72]) {
		m_pos.y--;
	}
	if (keyPress[80]) {
		m_pos.y++;
	}
	if (keyPress[75]) {
		m_pos.x--;
	}
	if (keyPress[77]) {
		m_pos.x++;
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
