#include "Vehicle.h"
#include "BoxCollider.h"
#include "Player.h"
Vehicle::Vehicle(POS position) : GameObject(position)
{
	player = nullptr;
	wchar_t img[14] = { L' ',L' ',L' ',L'm',L'=',L'=',L'>',L'(',L'(',L'(',L'-',L')',L')',L')'};
	m_width = 7;
	m_height = 2;
	m_sprite = new wchar_t[m_width * m_height];

	memcpy(m_sprite, img, sizeof(wchar_t) * m_width * m_height);
	m_color = CYAN;
	m_name = L"Vehicle";
}

Vehicle::~Vehicle()
{
}

int Vehicle::Update()
{
	auto p = GetComponent<BoxCollider>()->OnTriggerEnter(L"Player");
	if (!m_isRide && p != nullptr)
	{
		if (!p->GetIsAttacked())
		{
			std::dynamic_pointer_cast<Player>(p)->SetIsRide(true);
			std::dynamic_pointer_cast<Player>(p)->SetPos(POS(m_pos.x, m_pos.y-1));
			m_isRide = true;
			return -1;
		}
	}
	return 1;
}

int Vehicle::LateUpdate()
{
	return 1;
}
