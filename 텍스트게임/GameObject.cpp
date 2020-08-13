#include "GameObject.h"

GameObject::GameObject(char * sprite, int width, int height, POS initPos)
	:width(width),height(height),pos(initPos)
{
	this->sprite = new char[width*height];
	ZeroMemory(this->sprite, sizeof(char)*width * height);

	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			this->sprite[j*width + i] = sprite[j*width + i];
		}
	}
	//strcpy_s(this->sprite,width*height,sprite);
}

GameObject::~GameObject()
{
	delete[] sprite;
}

void GameObject::Render()
{
	ObjectMgr::GetInstance()->Draw(sprite, width, height, pos.x, pos.y);
}
