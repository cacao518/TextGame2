#pragma once
#include "Scene.h"
class Scene_Logo :
	public Scene
{
public:
	Scene_Logo();
	virtual ~Scene_Logo();
	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

