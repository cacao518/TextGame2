#pragma once
#include "Boss.h"
class Part;
class BossTank :
	public Boss
{
	enum PATTERN { NOT_RECOGNIZE,IDLE,MOVE,SHOT_READY,SHOT,RUSH_READY,RUSH,PATTERN_END};
public:
	BossTank(POS pos);
	virtual ~BossTank();
	// Boss��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual int LateUpdate() override;
	virtual void Render() override;

private:
	void UpdateCenterPos();

	void ProgressPattern();
	void SetPattern(PATTERN pattern)
	{
		m_curPattern = pattern;
		m_patternTimer = 0.f;
	}

	void ProgressIdle();
	void ProgressMove();
	void ProgressShot();
	void ProgressShotReady();
	void ProgressRush();
	void ProgressRushReady();
	void ProgressNotRecognize();
private:
	std::shared_ptr<Part> m_upPart;
	std::shared_ptr<Part> m_downPart;

	float m_patternTimer = 0.f;
	PATTERN m_curPattern = PATTERN_END;
	POS m_centerPos;
};

