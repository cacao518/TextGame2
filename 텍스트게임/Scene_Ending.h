#pragma once
#include "Scene.h"
class Scene_Ending :
	public Scene
{
public:
	Scene_Ending();
	virtual ~Scene_Ending();
	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

