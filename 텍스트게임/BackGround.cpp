#include "BackGround.h"

BackGround::BackGround(POS position)
	:GameObject(position)
{
	wchar_t BackGroundImg[6841] = { 0 }; // 2660
	m_width = 228; //  76
	m_height = 30; 
	std::wifstream fp;
	fp.open("BackGround.txt");
	fp.getline(BackGroundImg, 6841);
	fp.close();
	m_sprite = new wchar_t[m_width * m_height];
	memcpy(m_sprite, BackGroundImg, sizeof(wchar_t) * m_width * m_height);

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
