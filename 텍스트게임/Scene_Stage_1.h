#pragma once
#include "Scene.h"
class Scene_Stage_1 :
	public Scene
{
public:
	Scene_Stage_1();
	virtual ~Scene_Stage_1();
	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

