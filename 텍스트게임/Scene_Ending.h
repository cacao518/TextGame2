#pragma once
#include "Scene.h"
class Scene_Ending :
	public Scene
{
public:
	Scene_Ending();
	virtual ~Scene_Ending();
	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

