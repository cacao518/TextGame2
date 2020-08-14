#include "BackGround.h"

BackGround::BackGround(POS position)
	:GameObject(position)
{
	char BackGroundImg[6841] = { 0 }; // 2660
	m_width = 228; //  76
	m_height = 30; 
	std::ifstream fp;
	fp.open("BackGround.txt");
	fp.getline(BackGroundImg, 6841);
	fp.close();
	m_sprite = new char[m_width * m_height];
	memcpy(m_sprite, BackGroundImg, sizeof(char) * m_width * m_height);

	m_name = "BackGround";
}
BackGround::~BackGround()
{

}

int BackGround::Update()
{
	return 1;
}

int BackGround::LateUpdate()
{
	return 1;
}
