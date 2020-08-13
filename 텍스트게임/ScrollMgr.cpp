#include "ScrollMgr.h"
ScrollMgr* ScrollMgr::instance = nullptr;
ScrollMgr::ScrollMgr():m_scrollX(0.f),m_scrollY(0.f)
{
}

ScrollMgr::~ScrollMgr()
{
}


void ScrollMgr::ScrollMap(POS playerPosition)
{
	if (playerPosition.x < m_screenWidth/2.f)
		m_scrollX = 0.f;
	else if (playerPosition.x > m_mapWidth - m_screenWidth / 2.f)
		m_scrollX = m_mapWidth - m_screenWidth;
	else
		m_scrollX = playerPosition.x - m_screenWidth / 2.f;

	if (playerPosition.y < m_screenHeight)
		m_scrollY = 0.f;
	else if (playerPosition.y > m_mapHeight - m_screenHeight / 2.f)
		m_scrollY = m_mapHeight - m_screenHeight;
	else
		m_scrollY = playerPosition.y - m_screenHeight / 2.f;
}

void ScrollMgr::SetMapSize(float mapWidth, float mapHeight)
{
	m_mapWidth = mapWidth;
	m_mapHeight = mapHeight;
}

void ScrollMgr::SetScreenSize(float screenWidth, float screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
}


