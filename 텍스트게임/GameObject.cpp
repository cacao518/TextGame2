#include "GameObject.h"
#include "RigidBody.h"
#include "BoxCollider.h"
GameObject::GameObject(POS initPos)
	:m_pos(initPos),m_sprite(nullptr),m_name(nullptr),m_width(0),m_height(0),m_color(15), m_collisionObjPos(initPos),m_Life(true)
{
	
}

GameObject::~GameObject()
{
	if(nullptr!= m_sprite)
		delete[] m_sprite;
}

int GameObject::ComponentUpdate()
{

	if (GetComponent<RigidBody>() != nullptr)
		GetComponent<RigidBody>()->Update(); 

	if (GetComponent<BoxCollider>() != nullptr)
		GetComponent<BoxCollider>()->Update();

	return 1;
}

void GameObject::Render()
{
	if (nullptr != m_sprite)
		ObjectMgr::GetInstance()->Draw(m_sprite, m_width, m_height,
			(int)(m_pos.x - ScrollMgr::GetInstance()->GetScrollX()),
			(int)(m_pos.y - ScrollMgr::GetInstance()->GetScrollY()),m_color);
}

const wchar_t* GameObject::GetName()
{
	return m_name;
}

POS GameObject::GetPos()
{
	return m_pos;
}
void GameObject::SetPos(POS pos)
{
	m_pos = pos;
}
bool GameObject::GetIsAttacked()
{
	return m_isAttacked;
}
void GameObject::SetIsAttacked(bool flag)
{
	m_isAttacked = flag;
}
bool GameObject::GetIsLand()
{
	return m_isLand;
}
void GameObject::SetIsLand(bool flag)
{
	m_isLand = flag;
}

void GameObject::SetIsLife(bool flag)
{
	m_Life = flag;
}

void GameObject::SetColor(int color)
{
	m_color = color;
}

int GameObject::GetWidth()
{
	return m_width;
}

int GameObject::GetHeight()
{
	return m_height;
}


POS GameObject::GetCollisionObjPos()
{
	return m_collisionObjPos;
}

void GameObject::SetCollisionObjPos(POS pos)
{
	m_collisionObjPos = pos;
}
/*
int GameObject::GetCollisionCount()
{
	return m_collisionCount;
}
void GameObject::AddCollisionCount()
{
	m_collisionCount++;
}
void GameObject::SubCollisionCount()
{
	if(m_collisionCount != 0)
		m_collisionCount--;
}
float GameObject::GetGravitiySpeed()
{
	return m_gravitySpeed;
}
void GameObject::SetGravitiySpeed(float gs)
{
	m_gravitySpeed = gs;
}
*/