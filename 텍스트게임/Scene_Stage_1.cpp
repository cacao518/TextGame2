#include "Scene_Stage_1.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerUI.h"
#include "EnemyUI.h"
#include "Terrain.h"
#include "BackGround.h"
#include "BoxCollider.h"
#include "RigidBody.h"
#include "ItemBox.h"
#include "Bullet.h"
#include "BossTank.h"
#include "BossUI.h"
#include "Vehicle.h"
#include "GuardEnemy.h"
#include "Guard.h"
#include "GunEnemy.h"
#include "BossWizard.h"
Scene_Stage_1::Scene_Stage_1()
{
	const int MapWidth = 160;
	const int MapHeight = 80;

	int x = 3, y = 18;
	{
		std::shared_ptr<Player> player = std::make_shared<Player>(POS(x, y-2));
		m_objectMgr->InsertObject(PLAYER, std::dynamic_pointer_cast<GameObject>(player));
		RigidBody* rb = new RigidBody(std::dynamic_pointer_cast<GameObject>(player));
		player->AddComponent(rb);
		BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(player));
		player->AddComponent(bc);
		bc->SetIsTrigger(true);

		std::shared_ptr<PlayerUI> playerUI = std::make_shared<PlayerUI>();
		m_gameMgr->SetPlayerUI(playerUI, player);
		m_objectMgr->InsertObject(UI, std::dynamic_pointer_cast<GameObject>(playerUI));

		std::shared_ptr<EnemyUI> enemyUI = std::make_shared<EnemyUI>();
		m_gameMgr->SetEnemyUI(enemyUI);
		m_objectMgr->InsertObject(UI, std::dynamic_pointer_cast<GameObject>(enemyUI));

		std::shared_ptr<BossUI> bossUI = std::make_shared<BossUI>();
		m_gameMgr->SetBossUI(bossUI);
		m_objectMgr->InsertObject(UI, std::dynamic_pointer_cast<GameObject>(bossUI));
	}

	ParsingMap("map1.txt",MapWidth,MapHeight);

	ScrollMgr::GetInstance()->SetMapSize((float)MapWidth, (float)MapHeight);
}

Scene_Stage_1::~Scene_Stage_1()
{
	m_objectMgr->EraseObjectS(ENEMY);
	m_objectMgr->EraseObjectS(BOSS);
	m_objectMgr->EraseObjectS(BULLET);
	m_objectMgr->EraseObjectS(BACKGROUND);
	m_objectMgr->EraseObjectS(TERRAIN);
	m_objectMgr->EraseObjectS(ITEMBOX);
	m_objectMgr->EraseObjectS(VEHICLE);



}

void Scene_Stage_1::Update()
{
	m_objectMgr->UpdateObjects();
	auto& player = m_objectMgr->GetFrontObject(PLAYER);
	if (nullptr == player)
		return;
	if (player->GetPos().x >= 150.f)
		m_sceneMgr->SceneChange(SceneMgr::STAGE_2);
	if (GetAsyncKeyState(VK_RETURN))
		m_sceneMgr->SceneChange(SceneMgr::STAGE_2);

}

void Scene_Stage_1::LateUpdate()
{
	m_objectMgr->LateUpdateObjects();
}

void Scene_Stage_1::Render()
{
	m_objectMgr->RenderObjects();
}
