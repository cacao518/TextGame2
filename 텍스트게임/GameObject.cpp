#include "GameObject.h"
GameObject::GameObject(POS initPos)
	:m_pos(initPos),m_sprite(nullptr),m_name(nullptr),m_width(0),m_height(0)
{
	
}

GameObject::~GameObject()
{
	if(nullptr!= m_sprite)
		delete[] m_sprite;
}

void GameObject::Render()
{
	if (nullptr != m_sprite)
		ObjectMgr::GetInstance()->Draw(m_sprite, m_width, m_height,
			(int)(m_pos.x - ScrollMgr::GetInstance()->GetScrollX()),
			(int)(m_pos.y - ScrollMgr::GetInstance()->GetScrollY()));
}

////////Å×½ºÆ®