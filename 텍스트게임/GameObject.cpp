#include "GameObject.h"

GameObject::GameObject(POS initPos)
	:pos(initPos),sprite(nullptr),width(0),height(0)
{
	
}

GameObject::~GameObject()
{
	if(nullptr!=sprite)
		delete[] sprite;
}

void GameObject::Render()
{
	if(nullptr!=sprite)
		ObjectMgr::GetInstance()->Draw(sprite, width, height, pos.x, pos.y);
}
