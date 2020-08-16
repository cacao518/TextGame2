#include "SceneMgr.h"
#include "Scene_Logo.h"
#include "Scene_Stage_1.h"
SceneMgr* SceneMgr::instance = nullptr;
SceneMgr::SceneMgr():m_scene(nullptr),m_curScene(SCENE_END),m_prevScene(SCENE_END)
{
}

SceneMgr::~SceneMgr()
{
	if (nullptr != m_scene)
		delete m_scene;
}

HRESULT SceneMgr::SceneChange(SCENETYPE eType)
{
	m_curScene = eType;
	if (m_prevScene != m_curScene)
	{
		delete m_scene;

		switch (m_curScene)
		{
		case SceneMgr::LOGO:
			m_scene = new Scene_Logo;
			break;
		case SceneMgr::STAGE_1:
			m_scene = new Scene_Stage_1;
			break;
		case SceneMgr::STAGE_BOSS:
			break;

		}

		if (nullptr == m_scene)
			return E_FAIL;
		m_prevScene = m_curScene;
	}

	return S_OK;
}

void SceneMgr::Update()
{
	if (nullptr != m_scene)
		m_scene->Update();
}

void SceneMgr::LateUpdate()
{
	if (nullptr != m_scene)
		m_scene->LateUpdate();
}

void SceneMgr::Render()
{
	if (nullptr != m_scene)
		m_scene->Render();
}
