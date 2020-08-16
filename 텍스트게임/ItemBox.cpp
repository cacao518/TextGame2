#include "ItemBox.h"

ItemBox::ItemBox(int type, POS position)
	:GameObject(position)
{
	m_type = type;
	wchar_t img1[6] = { L' ', L' ',L' ',L'[', L'H',L']'};
	wchar_t img2[3] = { L'[', L'S', L']' };
	m_width = 3;
	m_height = 2;
	m_sprite = new wchar_t[m_width * m_height];
	if (m_type == 0)
	{
		memcpy(m_sprite, img1, sizeof(wchar_t) * m_width * m_height);
		m_color = YELLOW;
	}
	else if (m_type == 1)
	{
		memcpy(m_sprite, img2, sizeof(wchar_t) * m_width * m_height);
		m_color = GREEN;
	}
	m_name = L"ItemBox";
}

ItemBox::~ItemBox()
{
}

int ItemBox::Update()
{
	return 1;
}

int ItemBox::LateUpdate()
{
	return 1;
}

void ItemBox::SetType(int type)
{
	m_type = type;
}

int ItemBox::GetType()
{
	return m_type;
}
