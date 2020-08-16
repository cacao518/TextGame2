#pragma once
#include "GameObject.h"
class Part :
	public GameObject
{
public:
	Part(const char* fileName,int width,int height,int baseColor, GameObject* parentObj);
	virtual ~Part();
	// GameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual int LateUpdate() override;
	
	void SetIsDamagedPart(bool isDamagedPart) { m_IsDamagedPart = isDamagedPart; }
	void SetIsDamagingPart(bool isDamagingPart) { m_IsDamagingPart = isDamagingPart; }

private:
	void SetDamageEffect();
	void ShowDamageEffect();
private:
	GameObject* m_parentObj;
	bool m_IsDamagedPart;  //�÷��̾�� �������� �޴� ����
	bool m_IsDamagingPart; //�÷��̾�� �������� �ִ� ����
	int m_baseColor;
	float m_timer = 0.f;
	bool m_damaged = false;
};

