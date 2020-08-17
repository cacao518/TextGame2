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

Scene::Scene()
	:m_objectMgr(ObjectMgr::GetInstance()),m_sceneMgr(SceneMgr::GetInstance()),m_gameMgr(GameMgr::GetInstance())
{
}

Scene::~Scene()
{
}

void Scene::ParsingMap(char* mapName)
{
	const int MapWidth = 160;
	const int MapHeight = 80;

	int map[MapWidth][MapHeight];
	wchar_t GroundBlockImg[5] = { 'm','U','U','U','U' };
	wchar_t HighGroundBlockImg[10] = { 'm','U','U','U','U','U','U','U','U','U' };
	wchar_t AirBlockImg[2] = { 'm','U' };

	std::ifstream fp;
	fp.open(mapName);
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
			if (map[j][i] == 4) { // 몬스터1
				std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(POS(j, i));
				m_objectMgr->InsertObject(ENEMY, std::dynamic_pointer_cast<GameObject>(enemy));

				RigidBody* rb = new RigidBody(std::dynamic_pointer_cast<GameObject>(enemy));
				enemy->AddComponent(rb);
				BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(enemy));
				enemy->AddComponent(bc);
			}
			if (map[j][i] == 6) { // 헤비머신건
				std::shared_ptr<ItemBox> item = std::make_shared<ItemBox>(Bullet::HEABYGUN, POS(j, i));
				m_objectMgr->InsertObject(ITEMBOX, std::dynamic_pointer_cast<GameObject>(item));

				RigidBody* rb = new RigidBody(std::dynamic_pointer_cast<GameObject>(item));
				item->AddComponent(rb);
				BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(item));
				item->AddComponent(bc);
			}
			if (map[j][i] == 7) { // 로켓런처
				std::shared_ptr<ItemBox> item = std::make_shared<ItemBox>(Bullet::MISSILE, POS(j, i));
				m_objectMgr->InsertObject(ITEMBOX, std::dynamic_pointer_cast<GameObject>(item));

				RigidBody* rb = new RigidBody(std::dynamic_pointer_cast<GameObject>(item));
				item->AddComponent(rb);
				BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(item));
				item->AddComponent(bc);
			}
			if (map[j][i] == 8) { // 샷건
				std::shared_ptr<ItemBox> item = std::make_shared<ItemBox>(Bullet::SHOTGUN, POS(j, i));
				m_objectMgr->InsertObject(ITEMBOX, std::dynamic_pointer_cast<GameObject>(item));

				RigidBody* rb = new RigidBody(std::dynamic_pointer_cast<GameObject>(item));
				item->AddComponent(rb);
				BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(item));
				item->AddComponent(bc);
			}
			if (map[j][i] == -1) { // 탈것
				std::shared_ptr<Vehicle> tank = std::make_shared<Vehicle>(POS(j, i));
				m_objectMgr->InsertObject(VEHICLE, std::dynamic_pointer_cast<GameObject>(tank));

				RigidBody* rb = new RigidBody(std::dynamic_pointer_cast<GameObject>(tank));
				tank->AddComponent(rb);
				BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(tank));
				tank->AddComponent(bc);
			}
			if (map[j][i] == 9)
			{
				std::shared_ptr<BossTank> boss = std::make_shared<BossTank>(POS(j, i));
				m_objectMgr->InsertObject(BOSS, std::dynamic_pointer_cast<GameObject>(boss));

				RigidBody* rb = new RigidBody(std::dynamic_pointer_cast<GameObject>(boss));
				boss->AddComponent(rb);
				BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(boss));
				boss->AddComponent(bc);
			}
		}
	}
	fp.close();

	m_objectMgr->InsertObject(BACKGROUND, std::dynamic_pointer_cast<GameObject>(std::make_shared<BackGround>(POS(0, 0))));
}
