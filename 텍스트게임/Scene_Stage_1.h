#pragma once
#include "Scene.h"
class Scene_Stage_1 :
	public Scene
{
public:
	Scene_Stage_1();
	virtual ~Scene_Stage_1();
	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

