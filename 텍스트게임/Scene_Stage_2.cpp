#include "Scene_Stage_2.h"
#include "ScrollMgr.h"
#include "Player.h"
Scene_Stage_2::Scene_Stage_2()
{
	const int MapWidth = 201;
	const int MapHeight = 80;

	auto& player = m_objectMgr->GetFrontObject(PLAYER);
	if (nullptr == player)
		return;
	player->SetPos(POS(5.f, 3.f));

	ParsingMap("map2.txt", MapWidth, MapHeight);

	ScrollMgr::GetInstance()->SetMapSize((float)MapWidth, (float)MapHeight);
}

Scene_Stage_2::~Scene_Stage_2()
{
	m_objectMgr->EraseObjectS(ENEMY);
	m_objectMgr->EraseObjectS(BOSS);
	m_objectMgr->EraseObjectS(BULLET);
	m_objectMgr->EraseObjectS(BACKGROUND);
	m_objectMgr->EraseObjectS(TERRAIN);
	m_objectMgr->EraseObjectS(ITEMBOX);
	m_objectMgr->EraseObjectS(VEHICLE);
	
	auto& player = m_objectMgr->GetFrontObject(PLAYER);
	if (nullptr == player)
		return;
	player->SetPos(POS(-100.f, -100.f));
	auto& playerUI = m_objectMgr->GetFrontObject(UI);
	if (nullptr == playerUI)
		return;
	playerUI->SetPos(POS(-100.f, -100.f));

}

void Scene_Stage_2::Update()
{
	m_objectMgr->UpdateObjects();
	auto& player = m_objectMgr->GetFrontObject(PLAYER);
	if (nullptr == player)
		return;
	if (player->GetPos().x >= 200.f)
		m_sceneMgr->SceneChange(SceneMgr::ENDING);
	if (GetAsyncKeyState(VK_RETURN))
		m_sceneMgr->SceneChange(SceneMgr::ENDING);
}

void Scene_Stage_2::LateUpdate()
{
	m_objectMgr->LateUpdateObjects();

}

void Scene_Stage_2::Render()
{
	m_objectMgr->RenderObjects();

}
