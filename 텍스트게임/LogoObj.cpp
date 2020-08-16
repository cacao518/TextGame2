#include "LogoObj.h"

LogoObj::LogoObj():GameObject(POS(0.f,0.f))
{
	m_width = 50; //  76
	m_height = 24;
	wchar_t logoImg[50*24+1] = { L"" }; // 2660
	std::wifstream fp;
	std::wstring readTxt;
	fp.open("Logo.txt");
	while (!fp.eof())
	{
		std::getline(fp, readTxt);
		wcscat_s(logoImg, readTxt.c_str());
	}

	fp.close();
	m_sprite = new wchar_t[m_width * m_height];
	memcpy(m_sprite, logoImg, sizeof(wchar_t) * m_width * m_height);

	m_name = L"Logo";
	m_color = 8;
}

LogoObj::~LogoObj()
{
}

int LogoObj::Update()
{
	return 0;
}

int LogoObj::LateUpdate()
{
	return 0;
}

