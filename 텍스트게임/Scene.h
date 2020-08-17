#pragma once
#include "Header.h"
#include "SceneMgr.h"
#include "ObjectMgr.h"
#include "GameMgr.h"
class Scene
{
protected:
	explicit Scene();

public:
	virtual ~Scene();

public:
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;


protected:
	SceneMgr* m_sceneMgr;
	ObjectMgr* m_objectMgr;
	GameMgr* m_gameMgr;

	void ParsingMap(char* mapName);
};

