#pragma once
#include "Header.h"
class GameObject;
class ObjectMgr
{
public:
	enum OBJTYPE{BACKGROUND,TERRAIN,PLAYER,ENEMY,BULLET,TYPE_END};
public:
	static const int GetScreenWidth() { return ScreenWidth; }
	static const int GetScreenHeight() { return ScreenHeight; }
public:
	void Update();
	void Draw(const char* img, int w, int h, int x, int y);

	void UpdateObjects();
	void LateUpdateObjects();
	void RenderObjects();

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

	char scBuff1[ScreenWidth * ScreenHeight];
	char scBuff2[ScreenWidth * ScreenHeight];

	char * frontBuff, *backBuff;
	std::mutex frontLock, backLock;


};

