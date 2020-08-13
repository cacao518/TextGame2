#include "Header.h"
#include "Struct.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "Terrain.h"
using namespace std;

const int MapWidth = 160;
const int MapHeight = 80;

int main() {
	ObjectMgr* objectMgr=ObjectMgr::GetInstance();
	std::thread t1(&ObjectMgr::Update, objectMgr);

	int x = 3, y = 20;
	
	int map[MapWidth][MapHeight];
	char heroImg[4] = { '[',']','[',']' };
	char GroundBlockImg[3] = { 'm','U','U' };
	char AirBlockImg[2] = { 'm','U' };

	objectMgr->InsertObject(ObjectMgr::PLAYER, std::dynamic_pointer_cast<GameObject>(std::make_shared<Player>(heroImg, 2, 2, POS(x,y))));
	
	ifstream fp;
	fp.open("map.txt");
	for (int i = 0; i < MapHeight; i++){
		for (int j = 0; j < MapWidth; j++){
			fp >> map[j][i];
			if (map[j][i] == 1){ // 바닥 지형
				objectMgr->InsertObject(ObjectMgr::TERRAIN,
					std::dynamic_pointer_cast<GameObject>(std::make_shared<Terrain>(GroundBlockImg, 1, 3, POS(j, i))));
			}
			if (map[j][i] == 2) { // 공중 지형
				objectMgr->InsertObject(ObjectMgr::TERRAIN,
					std::dynamic_pointer_cast<GameObject>(std::make_shared<Terrain>(AirBlockImg, 1, 2, POS(j, i))));
			}
		}
	}
	
	std::thread Update([&] {
		while (true) {

			bool isDone = false;
			objectMgr->UpdateObjects();
			objectMgr->LateUpdateObjects();
			objectMgr->RenderObjects();

			if (isDone) {
				objectMgr->done = true;
				break;
			}
		}
	});

	Update.join();
	t1.join();

	objectMgr->DestroyInstance();

	printf("종료!");


}