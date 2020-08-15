#include "Header.h"
#include "Struct.h"
#include "ObjectMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "GameMgr.h"
#include "Timer.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "");
	SceneMgr* sceneMgr = SceneMgr::GetInstance();

	std::thread t1(&ObjectMgr::Update, ObjectMgr::GetInstance());

	ScrollMgr::GetInstance()->SetScreenSize((float)ObjectMgr::GetScreenWidth(), (float)ObjectMgr::GetScreenHeight());
	
	Timer::Reset();
	sceneMgr->SceneChange(SceneMgr::LOGO);
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
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(POS(x, y - 4));
	objectMgr->InsertObject(ENEMY, std::dynamic_pointer_cast<GameObject>(enemy));

	RigidBody rb = RigidBody(std::dynamic_pointer_cast<GameObject>(enemy));
	enemy->AddComponent(rb);
	BoxCollider bc = BoxCollider(std::dynamic_pointer_cast<GameObject>(enemy));
	enemy->AddComponent(bc);

	x += 43;
	std::shared_ptr<Enemy> enemy2= std::make_shared<Enemy>(POS(x, y - 6));
	objectMgr->InsertObject(ENEMY, std::dynamic_pointer_cast<GameObject>(enemy2));

	RigidBody rb2 = RigidBody(std::dynamic_pointer_cast<GameObject>(enemy2));
	enemy2->AddComponent(rb2);
	BoxCollider bc2 = BoxCollider(std::dynamic_pointer_cast<GameObject>(enemy2));
	enemy2->AddComponent(bc2);


	std::thread Update([&] {
		while (true) {
			Timer::Update();

			GameMgr::GetInstance()->Update();

			sceneMgr->Update();
			sceneMgr->LateUpdate();
			sceneMgr->Render();

			if (ObjectMgr::GetInstance()->done == true) {
				break;
			}
		}
		});

	t1.join();
	Update.join();

	sceneMgr->DestroyInstance();
	GameMgr::GetInstance()->DestroyInstance();
	ObjectMgr::GetInstance()->DestroyInstance();
	ScrollMgr::GetInstance()->DestroyInstance();
	printf("Á¾·á!");


}