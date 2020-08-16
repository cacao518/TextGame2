#pragma once
#include "Header.h"
class Scene;
class SceneMgr
{
public:
	enum SCENETYPE { LOGO, STAGE_1, STAGE_BOSS, SCENE_END };
private:
	explicit SceneMgr();
	~SceneMgr();
public:
	static SceneMgr* GetInstance()
	{
		if (nullptr == instance)
			instance = new SceneMgr();

		return instance;
	}
	static void DestroyInstance()
	{
		if (nullptr != instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

public:
	HRESULT SceneChange(SCENETYPE eType);
	void Update();
	void LateUpdate();
	void Render();

private:
	static SceneMgr* instance;

	SCENETYPE m_curScene;
	SCENETYPE m_prevScene;
	Scene* m_scene;
};

