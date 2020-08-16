#pragma once
#include "GameObject.h"
class Part :
	public GameObject
{
public:
	Part(const char* fileName,int width,int height,int baseColor, GameObject* parentObj);
	virtual ~Part();
	// GameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual int LateUpdate() override;
	
	void SetIsDamagedPart(bool isDamagedPart) { m_IsDamagedPart = isDamagedPart; }
	void SetIsDamagingPart(bool isDamagingPart) { m_IsDamagingPart = isDamagingPart; }

private:
	void SetDamageEffect();
	void ShowDamageEffect();
private:
	GameObject* m_parentObj;
	bool m_IsDamagedPart;  //플레이어에게 데미지를 받는 부위
	bool m_IsDamagingPart; //플레이어에게 데미지를 주는 부위
	int m_baseColor;
	float m_timer = 0.f;
	bool m_damaged = false;
};

