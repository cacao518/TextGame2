#include "Header.h"
#include "Struct.h"
#include "ObjectMgr.h"
#include "ScrollMgr.h"
#include "GameMgr.h"
#include "Timer.h"
#include "Player.h"
#include "Terrain.h"
#include "Enemy.h"
#include "BackGround.h"
#include "PlayerUI.h"
#include "EnemyUI.h"
#include "RigidBody.h"
#include "BoxCollider.h"
using namespace std;

const int MapWidth = 160;
const int MapHeight = 80;

int main() {
	setlocale(LC_ALL, "");
	ObjectMgr* objectMgr = ObjectMgr::GetInstance();
	ScrollMgr* scrollMgr = ScrollMgr::GetInstance();
	GameMgr* gameMgr = GameMgr::GetInstance();

	std::thread t1(&ObjectMgr::Update, objectMgr);

	scrollMgr->SetScreenSize((float)ObjectMgr::GetScreenWidth(), (float)ObjectMgr::GetScreenHeight());
	scrollMgr->SetMapSize((float)MapWidth, (float)MapHeight);
	int x = 3, y = 19;

	int map[MapWidth][MapHeight];
	wchar_t GroundBlockImg[5] = { 'm','U','U','U','U' };
	wchar_t HighGroundBlockImg[10] = { 'm','U','U','U','U','U','U','U','U','U' };
	wchar_t AirBlockImg[2] = { 'm','U' };
	{
		std::shared_ptr<Player> player = std::make_shared<Player>(POS(x, y));
		objectMgr->InsertObject(PLAYER, std::dynamic_pointer_cast<GameObject>(player));
		auto rb = RigidBody(std::dynamic_pointer_cast<GameObject>(player));
		player->AddComponent(rb);
		auto bc = BoxCollider(std::dynamic_pointer_cast<GameObject>(player));
		player->AddComponent(bc);
		bc.SetIsTrigger(true);

		std::shared_ptr<PlayerUI> playerUI = std::make_shared<PlayerUI>();
		gameMgr->SetPlayerUI(playerUI, player);
		objectMgr->InsertObject(UI, std::dynamic_pointer_cast<GameObject>(playerUI));

		std::shared_ptr<EnemyUI> enemyUI = std::make_shared<EnemyUI>();
		gameMgr->SetEnemyUI(enemyUI);
		objectMgr->InsertObject(UI, std::dynamic_pointer_cast<GameObject>(enemyUI));
	}
	x += 11;
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(POS(x, y+1 ));
	objectMgr->InsertObject(ENEMY, std::dynamic_pointer_cast<GameObject>(enemy));

	RigidBody rb = RigidBody(std::dynamic_pointer_cast<GameObject>(enemy));
	enemy->AddComponent(rb);
	BoxCollider bc = BoxCollider(std::dynamic_pointer_cast<GameObject>(enemy));
	enemy->AddComponent(bc);

	x += 43;
	std::shared_ptr<Enemy> enemy2= std::make_shared<Enemy>(POS(x, y +1));
	objectMgr->InsertObject(ENEMY, std::dynamic_pointer_cast<GameObject>(enemy2));

	RigidBody rb2 = RigidBody(std::dynamic_pointer_cast<GameObject>(enemy2));
	enemy2->AddComponent(rb2);
	BoxCollider bc2 = BoxCollider(std::dynamic_pointer_cast<GameObject>(enemy2));
	enemy2->AddComponent(bc2);

	ifstream fp;
	fp.open("map.txt");
	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			fp >> map[j][i];
			if (map[j][i] == 1) { // 바닥 지형
				objectMgr->InsertObject(TERRAIN,
					std::dynamic_pointer_cast<GameObject>(std::make_shared<Terrain>(GroundBlockImg, 1, 5, POS(j, i))));
			}
			if (map[j][i] == 2) { // 공중 지형
				objectMgr->InsertObject(TERRAIN,
					std::dynamic_pointer_cast<GameObject>(std::make_shared<Terrain>(AirBlockImg, 1, 2, POS(j, i))));
			}
			if (map[j][i] == 3) { // 언덕 지형
				objectMgr->InsertObject(TERRAIN,
					std::dynamic_pointer_cast<GameObject>(std::make_shared<Terrain>(HighGroundBlockImg, 1, 10, POS(j, i))));
			}
		}
	}
	fp.close();

	objectMgr->InsertObject(BACKGROUND, std::dynamic_pointer_cast<GameObject>(std::make_shared<BackGround>(POS(0, 0))));

	Timer::Reset();

	std::thread Update([&] {
		while (true) {
			Timer::Update();

			gameMgr->Update();

			objectMgr->UpdateObjects();
			objectMgr->LateUpdateObjects();
			objectMgr->RenderObjects();

			if (objectMgr->done == true) {
				break;
			}
		}
		});

	t1.join();
	Update.join();

	objectMgr->DestroyInstance();
	scrollMgr->DestroyInstance();
	printf("종료!");


}