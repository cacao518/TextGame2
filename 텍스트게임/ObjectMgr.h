#pragma once
#include "Header.h"
class GameObject;

class ObjectMgr
{
public:
	enum OBJTYPE{BACKGROUND,TERRAIN,PLAYER,ENEMY,BULLET,UI,TYPE_END};
public:
	static const int GetScreenWidth() { return ScreenWidth; }
	static const int GetScreenHeight() { return ScreenHeight; }
public:
	void Update();
	void Draw(const wchar_t* img, int w, int h, int x, int y, int color);

	void UpdateObjects();
	void LateUpdateObjects();
	void RenderObjects();

	void SetColor(int color, int bgcolor) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor & 0xf) << 4) | (color & 0xf)); };
	HRESULT InsertObject(OBJTYPE objType, std::shared_ptr<GameObject>& obj);
private:
	void ShowConsoleCursor(bool showFlag);
	void begin();
	void clearScreen();
	void end();
	void present();

	void CheckCollider(GameObject* obj1, GameObject* obj2);
private:
	explicit ObjectMgr();
	~ObjectMgr();
public:
	static ObjectMgr* GetInstance()
	{
		if (nullptr == instance)
			instance = new ObjectMgr();

		return instance;
	}
	static void DestroyInstance()
	{
		if (nullptr != instance)
		{
			delete instance;
			instance = nullptr;
		}
	}
public:
	bool done;
private:
	static ObjectMgr* instance;
	std::list<std::shared_ptr<GameObject>> m_ObjectList[TYPE_END];


	static const int ScreenWidth = 80;
	static const int ScreenHeight = 30;

	wchar_t scBuff1[ScreenWidth * ScreenHeight];
	wchar_t scBuff2[ScreenWidth * ScreenHeight];

	int scColorBuff1[ScreenWidth * ScreenHeight];
	int scColorBuff2[ScreenWidth * ScreenHeight];

	wchar_t * frontBuff, *backBuff;
	int* frontColorBuff, * backColorBuff;
	std::mutex frontLock, backLock;


};

