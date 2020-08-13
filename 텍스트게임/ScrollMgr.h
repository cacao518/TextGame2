#pragma once
#include "Header.h"
#include "Struct.h"
class ScrollMgr
{
public:

	void ScrollMap(POS playerPosition);

	void SetMapSize(float mapWidth, float mapHeight);
	void SetScreenSize(float screenWidth, float screenHeight);

	const float GetScrollX()const { return m_scrollX; }
	const float GetScrollY()const { return m_scrollY; }
private:
	explicit ScrollMgr();
	~ScrollMgr();
public:
	static ScrollMgr* GetInstance()
	{
		if (nullptr == instance)
			instance = new ScrollMgr();

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

private:
	static ScrollMgr* instance;
	
private:
	float m_scrollX;
	float m_scrollY;

	float m_mapWidth;
	float m_mapHeight;
	
	float m_screenWidth;
	float m_screenHeight;
};

