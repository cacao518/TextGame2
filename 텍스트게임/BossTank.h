#pragma once
#include "Boss.h"
class Part;
class BossTank :
	public Boss
{
	enum PATTERN { IDLE,MOVE,SHOT,RUSH_READY,RUSH,PATTERN_END};
public:
	BossTank(POS pos);
	virtual ~BossTank();
	// Boss을(를) 통해 상속됨
	virtual int Update() override;
	virtual int LateUpdate() override;
	virtual void Render() override;

private:
	void ProgressPattern();
	void SetPattern(PATTERN pattern)
	{
		m_curPattern = pattern;
		m_patternTimer = 0.f;
	}

	void ProgressIdle();
	void ProgressMove();
	void ProgressShot();
	void ProgressRush();
	void ProgressRushReady();
private:
	std::shared_ptr<Part> m_upPart;
	std::shared_ptr<Part> m_downPart;

	float m_patternTimer = 0.f;
	PATTERN m_curPattern = PATTERN_END;
};

