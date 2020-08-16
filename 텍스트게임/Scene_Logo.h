#pragma once
#include "Scene.h"
class Scene_Logo :
	public Scene
{
public:
	Scene_Logo();
	virtual ~Scene_Logo();
	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

