#include "EndingObj.h"

EndingObj::EndingObj() :GameObject(POS(0.f, 0.f))
{
	m_width = 50; 
	m_height = 22;
	wchar_t logoImg[50 * 23 + 1] = { L"" }; 
	std::wifstream fp;
	std::wstring readTxt;
	fp.open("Ending.txt");
	while (!fp.eof())
	{
		std::getline(fp, readTxt);
		wcscat_s(logoImg, readTxt.c_str());
	}

	fp.close();
	m_sprite = new wchar_t[m_width * m_height];
	memcpy(m_sprite, logoImg, sizeof(wchar_t) * m_width * m_height);

	m_name = L"Logo";
	m_color = LIGHTGRAY;
}

EndingObj::~EndingObj()
{
}

int EndingObj::Update()
{
	return 0;
}

int EndingObj::LateUpdate()
{
	return 0;
}
