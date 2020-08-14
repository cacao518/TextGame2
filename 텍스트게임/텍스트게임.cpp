#include "Header.h"
#include "Struct.h"
#include "ObjectMgr.h"
#include "ScrollMgr.h"
#include "Timer.h"
#include "Player.h"
#include "Terrain.h"
#include "Enemy.h"
#include "BackGround.h"
using namespace std;

const int MapWidth = 160;
const int MapHeight = 80;

int main() {
	ObjectMgr* objectMgr = ObjectMgr::GetInstance();
	ScrollMgr* scrollMgr = ScrollMgr::GetInstance();


	std::thread t1(&ObjectMgr::Update, objectMgr);

	scrollMgr->SetScreenSize((float)ObjectMgr::GetScreenWidth(), (float)ObjectMgr::GetScreenHeight());
	scrollMgr->SetMapSize((float)MapWidth, (float)MapHeight);
	int x = 3, y = 19;

	int map[MapWidth][MapHeight];
	char GroundBlockImg[5] = { 'm','U','U','U','U' };
	char AirBlockImg[2] = { 'm','U' };

	objectMgr->InsertObject(ObjectMgr::PLAYER, std::dynamic_pointer_cast<GameObject>(std::make_shared<Player>(POS(x, y))));

	x = 20;
	objectMgr->InsertObject(ObjectMgr::ENEMY, std::dynamic_pointer_cast<GameObject>(std::make_shared<Enemy>(POS(x, y + 1))));

	x = 40;
	objectMgr->InsertObject(ObjectMgr::ENEMY, std::dynamic_pointer_cast<GameObject>(std::make_shared<Enemy>(POS(x, y+1))));

	x = 60;
	objectMgr->InsertObject(ObjectMgr::ENEMY, std::dynamic_pointer_cast<GameObject>(std::make_shared<Enemy>(POS(x, y + 1))));
	ifstream fp;
	fp.open("map.txt");
	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			fp >> map[j][i];
			if (map[j][i] == 1) { // 바닥 지형
				objectMgr->InsertObject(ObjectMgr::TERRAIN,
					std::dynamic_pointer_cast<GameObject>(std::make_shared<Terrain>(GroundBlockImg, 1, 5, POS(j, i))));
			}
			if (map[j][i] == 2) { // 공중 지형
				objectMgr->InsertObject(ObjectMgr::TERRAIN,
					std::dynamic_pointer_cast<GameObject>(std::make_shared<Terrain>(AirBlockImg, 1, 2, POS(j, i))));
			}
		}
	}
	fp.close();

	objectMgr->InsertObject(ObjectMgr::BACKGROUND, std::dynamic_pointer_cast<GameObject>(std::make_shared<BackGround>(POS(0, 0))));

	Timer::Reset();

	std::thread Update([&] {
		while (true) {
			Timer::Update();


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