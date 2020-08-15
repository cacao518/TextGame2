#include "Scene_Logo.h"
#include "LogoObj.h"
Scene_Logo::Scene_Logo()
{
	m_objectMgr->InsertObject(ObjectMgr::UI, std::dynamic_pointer_cast<GameObject>(std::make_shared<LogoObj>()));
}

Scene_Logo::~Scene_Logo()
{
	m_objectMgr->EraseObjectS(ObjectMgr::UI);
}

void Scene_Logo::Update()
{
	m_objectMgr->UpdateObjects();

	if (GetAsyncKeyState(VK_RETURN))
		m_sceneMgr->SceneChange(SceneMgr::STAGE_1);

}

void Scene_Logo::LateUpdate()
{
	m_objectMgr->LateUpdateObjects();

}

void Scene_Logo::Render()
{
	m_objectMgr->RenderObjects();

}
