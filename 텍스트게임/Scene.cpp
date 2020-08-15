#include "Scene.h"

Scene::Scene()
	:m_objectMgr(ObjectMgr::GetInstance()),m_sceneMgr(SceneMgr::GetInstance()),m_gameMgr(GameMgr::GetInstance())
{
}

Scene::~Scene()
{
}
