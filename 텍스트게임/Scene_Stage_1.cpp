#include "Scene_Stage_1.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerUI.h"
#include "EnemyUI.h"
#include "Terrain.h"
#include "BackGround.h"
#include "BoxCollider.h"
#include "RigidBody.h"
Scene_Stage_1::Scene_Stage_1()
{
	const int MapWidth = 160;
	const int MapHeight = 80;
	int x = 3, y = 19;

	int map[MapWidth][MapHeight];
	wchar_t GroundBlockImg[5] = { 'm','U','U','U','U' };
	wchar_t HighGroundBlockImg[10] = { 'm','U','U','U','U','U','U','U','U','U' };
	wchar_t AirBlockImg[2] = { 'm','U' };
	{
		std::shared_ptr<Player> player = std::make_shared<Player>(POS(x, y));
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
	}
	x += 11;
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(POS(x, y - 4));
	m_objectMgr->InsertObject(ENEMY, std::dynamic_pointer_cast<GameObject>(enemy));

	RigidBody* rb = new RigidBody(std::dynamic_pointer_cast<GameObject>(enemy));
	enemy->AddComponent(rb);
	BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(enemy));
	enemy->AddComponent(bc);

	x += 43;
	std::shared_ptr<Enemy> enemy2 = std::make_shared<Enemy>(POS(x, y - 6));
	m_objectMgr->InsertObject(ENEMY, std::dynamic_pointer_cast<GameObject>(enemy2));

	RigidBody* rb2 = new RigidBody(std::dynamic_pointer_cast<GameObject>(enemy2));
	enemy2->AddComponent(rb2);
	BoxCollider* bc2 = new BoxCollider(std::dynamic_pointer_cast<GameObject>(enemy2));
	enemy2->AddComponent(bc2);

	
	std::ifstream fp;
	fp.open("map.txt");
	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			fp >> map[j][i];
			if (map[j][i] == 1) { // 바닥 지형
				m_objectMgr->InsertObject(TERRAIN,
						std::dynamic_pointer_cast<GameObject>(std::make_shared<Terrain>(GroundBlockImg, 1, 5, POS(j, i))));
			}
			if (map[j][i] == 2) { // 공중 지형
				m_objectMgr->InsertObject(TERRAIN,
						std::dynamic_pointer_cast<GameObject>(std::make_shared<Terrain>(AirBlockImg, 1, 2, POS(j, i))));
			}
			if (map[j][i] == 3) { // 언덕 지형
				m_objectMgr->InsertObject(TERRAIN,
						std::dynamic_pointer_cast<GameObject>(std::make_shared<Terrain>(HighGroundBlockImg, 1, 10, POS(j, i))));
			}
		}
	}
	fp.close();

	m_objectMgr->InsertObject(BACKGROUND, std::dynamic_pointer_cast<GameObject>(std::make_shared<BackGround>(POS(0, 0))));

	ScrollMgr::GetInstance()->SetMapSize((float)MapWidth, (float)MapHeight);
}

Scene_Stage_1::~Scene_Stage_1()
{
}

void Scene_Stage_1::Update()
{
	m_objectMgr->UpdateObjects();
}

void Scene_Stage_1::LateUpdate()
{
	m_objectMgr->LateUpdateObjects();
}

void Scene_Stage_1::Render()
{
	m_objectMgr->RenderObjects();
}
