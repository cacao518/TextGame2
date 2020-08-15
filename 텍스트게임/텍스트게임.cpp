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