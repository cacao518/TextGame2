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
#include "GunEnemy.h"

Scene::Scene()
	:m_objectMgr(ObjectMgr::GetInstance()),m_sceneMgr(SceneMgr::GetInstance()),m_gameMgr(GameMgr::GetInstance())
{
}

Scene::~Scene()
{
}

void Scene::ParsingMap(char* mapName, int mapWidth, int mapHeight)
{

	int* map = new int[mapWidth * mapHeight];
	
	wchar_t GroundBlockImg[5] = { 'm','U','U','U','U' };
	wchar_t HighGroundBlockImg[10] = { 'm','U','U','U','U','U','U','U','U','U' };
	wchar_t AirBlockImg[2] = { 'm','U' };

	std::ifstream fp;
	fp.open(mapName);
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			int index = i * mapWidth + j;
			fp >> map[index];
			if (map[index] == 1) { // ¹Ù´Ú ÁöÇü
				m_objectMgr->InsertObject(TERRAIN,
					std::dynamic_pointer_cast<GameObject>(std::make_shared<Terrain>(GroundBlockImg, 1, 5, POS(j, i))));
			}
			if (map[index] == 2) { // °øÁß ÁöÇü
				m_objectMgr->InsertObject(TERRAIN,
					std::dynamic_pointer_cast<GameObject>(std::make_shared<Terrain>(AirBlockImg, 1, 2, POS(j, i))));
			}
			if (map[index] == 3) { // ¾ð´ö ÁöÇü
				m_objectMgr->InsertObject(TERRAIN,
					std::dynamic_pointer_cast<GameObject>(std::make_shared<Terrain>(HighGroundBlockImg, 1, 10, POS(j, i))));
			}
			if (map[index] == 4) { // ¸ó½ºÅÍ1
				std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(POS(j, i));
				m_objectMgr->InsertObject(ENEMY, std::dynamic_pointer_cast<GameObject>(enemy));

				RigidBody* rb = new RigidBody(std::dynamic_pointer_cast<GameObject>(enemy));
				enemy->AddComponent(rb);
				BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(enemy));
				enemy->AddComponent(bc);
			}
			if (map[index] == 6) { // Çìºñ¸Ó½Å°Ç
				std::shared_ptr<ItemBox> item = std::make_shared<ItemBox>(Bullet::HEABYGUN, POS(j, i));
				m_objectMgr->InsertObject(ITEMBOX, std::dynamic_pointer_cast<GameObject>(item));

				RigidBody* rb = new RigidBody(std::dynamic_pointer_cast<GameObject>(item));
				item->AddComponent(rb);
				BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(item));
				item->AddComponent(bc);
			}
			if (map[index] == 7) { // ·ÎÄÏ·±Ã³
				std::shared_ptr<ItemBox> item = std::make_shared<ItemBox>(Bullet::MISSILE, POS(j, i));
				m_objectMgr->InsertObject(ITEMBOX, std::dynamic_pointer_cast<GameObject>(item));

				RigidBody* rb = new RigidBody(std::dynamic_pointer_cast<GameObject>(item));
				item->AddComponent(rb);
				BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(item));
				item->AddComponent(bc);
			}
			if (map[index] == 8) { // ¼¦°Ç
				std::shared_ptr<ItemBox> item = std::make_shared<ItemBox>(Bullet::SHOTGUN, POS(j, i));
				m_objectMgr->InsertObject(ITEMBOX, std::dynamic_pointer_cast<GameObject>(item));

				RigidBody* rb = new RigidBody(std::dynamic_pointer_cast<GameObject>(item));
				item->AddComponent(rb);
				BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(item));
				item->AddComponent(bc);
			}
			if (map[index] == -1) { // Å»°Í
				std::shared_ptr<Vehicle> tank = std::make_shared<Vehicle>(POS(j, i));
				m_objectMgr->InsertObject(VEHICLE, std::dynamic_pointer_cast<GameObject>(tank));

				RigidBody* rb = new RigidBody(std::dynamic_pointer_cast<GameObject>(tank));
				tank->AddComponent(rb);
				BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(tank));
				tank->AddComponent(bc);
			}
			if (map[index] == 9)
			{
				std::shared_ptr<BossTank> boss = std::make_shared<BossTank>(POS(j, i));
				m_objectMgr->InsertObject(BOSS, std::dynamic_pointer_cast<GameObject>(boss));

				RigidBody* rb = new RigidBody(std::dynamic_pointer_cast<GameObject>(boss));
				boss->AddComponent(rb);
				BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(boss));
				boss->AddComponent(bc);
			}

			if (map[index] == -2) { // °¡µå¸÷
				std::shared_ptr<GuardEnemy> enemy2 = std::make_shared<GuardEnemy>(POS(j, i));
				m_objectMgr->InsertObject(ENEMY, std::dynamic_pointer_cast<GameObject>(enemy2));

				RigidBody* rb = new RigidBody(std::dynamic_pointer_cast<GameObject>(enemy2));
				enemy2->AddComponent(rb);
				BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(enemy2));
				enemy2->AddComponent(bc);
			}
			if (map[index] == -3) { // ÃÑ¸÷
				std::shared_ptr<GunEnemy> enemy3 = std::make_shared<GunEnemy>(POS(j, i));
				m_objectMgr->InsertObject(ENEMY, std::dynamic_pointer_cast<GameObject>(enemy3));

				RigidBody* rb = new RigidBody(std::dynamic_pointer_cast<GameObject>(enemy3));
				enemy3->AddComponent(rb);
				BoxCollider* bc = new BoxCollider(std::dynamic_pointer_cast<GameObject>(enemy3));
				enemy3->AddComponent(bc);
			}
		}
	}
	fp.close();
	delete map;
	m_objectMgr->InsertObject(BACKGROUND, std::dynamic_pointer_cast<GameObject>(std::make_shared<BackGround>(POS(0, 0))));
}
