#include "ChargeParticle1.h"
#include"Timer.h"

ChargeParticle1::ChargeParticle1(POS position)
	:GameObject(position)
{
	

	printf("ÆÄÆ¼»ý¼ºµÊ");
	/*
	wchar_t ParticleImg[30] = { L' ',L'*',L' ',L' ',L'*',L' ' 
								 ,L' ',L' ',L' ',L' ',L' ',L' '
								 ,L'*',L' ',L' ',L' ',L' ',L'*'
								 ,L' ',L' ',L' ',L' ',L' ',L' '
								 ,L' ',L'*',L' ',L' ',L'*',L' '
							};
							*/

	wchar_t ParticleImg[3] = { L'*',L'*',L'*'};
	m_width = 3;
	m_height = 1;
	m_sprite = new wchar_t[m_width * m_height];
	memcpy(m_sprite, ParticleImg, sizeof(wchar_t) * m_width * m_height);

	
	m_name = L"ChargeParticle";

	m_color = 12;
}

ChargeParticle1::~ChargeParticle1()
{
}

int ChargeParticle1::Update()
{



	if (m_Life)
		return 1;
	else
		return -1;

}

int ChargeParticle1::LateUpdate()
{
	return 1;
}

void ChargeParticle1::EndParticle()
{
	m_Life = false;
}

void ChargeParticle1::SetUpdatePos(float m_Parent_x, float m_Parent_y, int m_ParentColor)
{
	m_pos.x = m_Parent_x;
	m_pos.y = m_Parent_y;
	m_color = m_ParentColor;

}



