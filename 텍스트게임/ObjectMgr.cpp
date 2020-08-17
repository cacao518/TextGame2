#include "ObjectMgr.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "GameMgr.h"
#include "BoxCollider.h"
//#include<ChargeParticle1.h>
ObjectMgr* ObjectMgr::instance = nullptr;

ObjectMgr::ObjectMgr() :done(false), scBuff1(), scBuff2(), frontBuff(nullptr), backBuff(nullptr) {

	ShowConsoleCursor(false);

	int x, y;

	for (x = 0; x < ScreenWidth; x++) {
		for (y = 0; y < ScreenHeight; y++) {
			scBuff1[y* ScreenWidth + x] = ' ';
			scBuff2[y * ScreenWidth + x] = ' ';
			scColorBuff1[y * ScreenWidth + x] = 0;
			scColorBuff2[y * ScreenWidth + x] = 0;
		}

	}

	frontBuff = scBuff1;
	backBuff = scBuff2;
	frontColorBuff = scColorBuff1;
	backColorBuff = scColorBuff2;
	done = false;
}

ObjectMgr::~ObjectMgr()
{
}

void ObjectMgr::ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void ObjectMgr::begin()
{
	backLock.lock();
}

void ObjectMgr::clearScreen()
{
	int x, y;

	for (x = 0; x < ScreenWidth; x++) {
		for (y = 0; y < ScreenHeight; y++) {
			backBuff[y * ScreenWidth + x] = ' ';
			backColorBuff[y * ScreenWidth + x] = 0;
		}
	}
}

void ObjectMgr::end()
{
	backLock.unlock();
}

void ObjectMgr::present()
{
	frontLock.lock();
	backLock.lock();

	if (frontBuff == scBuff1) {
		frontBuff = scBuff2;
		backBuff = scBuff1;
		frontColorBuff = scColorBuff2;
		backColorBuff = scColorBuff1;
	}
	else {
		frontBuff = scBuff1;
		backBuff = scBuff2;
		frontColorBuff = scColorBuff1;
		backColorBuff = scColorBuff2;
	}

	frontLock.unlock();
	backLock.unlock();
}

void ObjectMgr::Draw(const wchar_t * img, int w, int h, int x, int y, int color)
{
	int i, j;
	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			int ty = y + j;
			int tx = x + i;
			if (tx < 0 || tx >= ScreenWidth) {
				continue;
			}
			if (ty < 0 || ty >= ScreenHeight) {
				continue;
			}
			backBuff[ty*ScreenWidth + tx] = img[j*w + i];
			backColorBuff[ty * ScreenWidth + tx] = color;
		}
	}
}

void ObjectMgr::Update()
{
	COORD pos;
	while (done == false) {
		frontLock.lock();
		int x, y;
		for (y = 0; y < ScreenHeight; y++) {
			pos.X = 0;
			pos.Y = y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			for (x = 0; x < ScreenWidth; x++) {
				SetColor(frontColorBuff[y * ScreenWidth + x], 0);
				putwchar((int)frontBuff[y * ScreenWidth + x]);
			}
		}
		ShowConsoleCursor(false);
		frontLock.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void ObjectMgr::UpdateObjects()
{
	for (int i = 0; i < TYPE_END; ++i)
	{
		for (auto iter = m_ObjectList[i].begin(); iter != m_ObjectList[i].end();)
		{
			(*iter).get()->ComponentUpdate();
			if ((*iter).get()->Update() < 0)
				m_ObjectList[i].erase(iter++);
			else
				++iter;
		}
	}
}

void ObjectMgr::LateUpdateObjects()
{
	for (int i = 0; i < TYPE_END; ++i)
	{
		for (auto iter = m_ObjectList[i].begin(); iter != m_ObjectList[i].end();)
		{
			if ((*iter).get()->LateUpdate() < 0)
				m_ObjectList[i].erase(iter++);
			else
				++iter;
		}
	}

}

void ObjectMgr::RenderObjects()
{
	begin();
	clearScreen();

	for (int i = 0; i < TYPE_END; ++i)
	{
		for (auto& object : m_ObjectList[i])
		{
			object->Render();
		}
	}
	end();
	present();
}

HRESULT ObjectMgr::InsertObject(OBJTYPE objType, std::shared_ptr<GameObject>& obj)
{
	if (obj.get() == nullptr)
		return E_FAIL;
	m_ObjectList[objType].push_back(obj);
	return S_OK;
}

HRESULT ObjectMgr::EraseObjectS(OBJTYPE objType)
{
	m_ObjectList[objType].remove_if([](const std::shared_ptr<GameObject>& obj) {return true; });
	return S_OK;
}

std::shared_ptr<GameObject>& ObjectMgr::GetFrontObject(OBJTYPE type)
{
	// TODO: 여기에 return 문을 삽입합니다.
	return m_ObjectList[type].front();
}
