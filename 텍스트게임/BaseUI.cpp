#include "BaseUI.h"

BaseUI::BaseUI():GameObject(POS(0.f,0.f))
{
}

BaseUI::~BaseUI()
{
}

void BaseUI::Render()
{
	if (nullptr != m_sprite)
		ObjectMgr::GetInstance()->Draw(m_sprite, m_width, m_height, (int)m_pos.x, (int)m_pos.y);
}
