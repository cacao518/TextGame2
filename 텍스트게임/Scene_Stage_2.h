#pragma once
#include "Scene.h"
class Scene_Stage_2 :
	public Scene
{
public:
	Scene_Stage_2();
	virtual ~Scene_Stage_2();
	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

