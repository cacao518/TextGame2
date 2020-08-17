#pragma once
#include "Boss.h"
class Part;
class BossWizard :
	public Boss
{
	enum PATTERN { NOT_RECOGNIZE, IDLE, MOVE, METEOR_READY, METEOR, EARTHQUAKE_READY, EARTHQUAKE, PATTERN_END };
public:
	BossWizard(POS pos);
	virtual ~BossWizard();
	// Boss을(를) 통해 상속됨
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
	void EnableAttackPosition();
	void DisableAttackPosition();

	void ProgressIdle();
	void ProgressMove();
	void ProgressMeteor();
	void ProgressMeteorReady();
	void ProgressEarthquake();
	void ProgressEarthquakeReady();
	void ProgressNotRecognize();
private:
	std::shared_ptr<Part> m_leftPart;
	std::shared_ptr<Part> m_rightPart;
	std::shared_ptr<Part> m_centerPart;

	float m_patternTimer = 0.f;
	PATTERN m_curPattern = PATTERN_END;
	POS m_centerPos;

	bool m_setAttackPosition;
	int m_attackPosCount;
	std::vector<POS> m_attackPosition;
};

