#include "Scene_Ending.h"
#include "EndingObj.h"
Scene_Ending::Scene_Ending()
{
	m_objectMgr->InsertObject(UI, std::dynamic_pointer_cast<GameObject>(std::make_shared<EndingObj>()));

}

Scene_Ending::~Scene_Ending()
{
	m_objectMgr->EraseObjectS(UI);

}

void Scene_Ending::Update()
{
	m_objectMgr->UpdateObjects();

	if (GetAsyncKeyState(VK_RETURN))
		m_objectMgr->done = true;
}

void Scene_Ending::LateUpdate()
{
	m_objectMgr->LateUpdateObjects();

}

void Scene_Ending::Render()
{
	m_objectMgr->RenderObjects();

}
