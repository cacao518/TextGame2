#include "Enemy.h"
#include "Timer.h"
#include "Bullet.h"
#include "GameMgr.h"
#include "RigidBody.h"

Enemy::Enemy(POS position)
	:GameObject(position), m_Status(STATUS(10.f, 10.f, 5.f))
{
	wchar_t monsterImg[4] = { '*', '*', 'M', 'M' };

	m_width = 2;
	m_height = 2;
	m_sprite = new wchar_t[m_width * m_height];
	memcpy(m_sprite, monsterImg, sizeof(wchar_t) * m_width * m_height);

	m_name = L"Enemy";
	m_color = 2;
	baseColor = m_color;
	
}

Enemy::~Enemy()
{

}

int Enemy::Update()
{
	if (m_dir) m_pos.x += Timer::DeltaTime() * 5;
	else  m_pos.x -= Timer::DeltaTime() * 5;

	m_MoveCount+= Timer::DeltaTime();
	if (m_MoveCount > 1 )
	{
		m_MoveCount =0;
		m_dir = !m_dir;
	}

	

		

	

	if (m_Life)
		return 1;
	else
		return -1;
}

int Enemy::LateUpdate()
{
	return 1;
}




void Enemy::Knockback(POS otherObjPos)
{
	if (ObjectMgr::GetInstance()->m_ObjectList[PLAYER].front()->GetPos().x <= m_pos.x)
		GetComponent<RigidBody>()->AddForce(Timer::DeltaTime() * 12, Timer::DeltaTime() * 8);
	else
		GetComponent<RigidBody>()->AddForce(Timer::DeltaTime() * -12, Timer::DeltaTime() * 8);
}

void Enemy::GetDamage(float damage, POS bulletPos)
{
    Knockback(bulletPos);
	printf("��ü�� %f ", m_Status.hp);
	m_Status.hp -= damage;
	if (m_Status.hp <= 0) m_Life = false;
		
}

//���忡�ʹ̿�
void Enemy::GetDamage(float damage, bool bulletDir)
{

	//if (bulletDir != m_dir) return;
	if (bulletDir) return;
	printf("��ü�� %f ", m_Status.hp);
	m_Status.hp -= damage;
	if (m_Status.hp <= 0) m_Life = false;

}

void Enemy::damagedColor()
{

	//�ǰ�
	if (m_isAttacked) {
		m_color = 13;
		m_timer += Timer::DeltaTime();
		//���� ���� , �� ����, Ÿ�̸� �ʱ�ȭ, �ݺ�������
		if (m_timer > 2) {
			m_color = baseColor;  m_timer = 0; m_isAttacked = false;
		}
	}
}

