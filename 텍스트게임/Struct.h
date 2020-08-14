#pragma once
typedef struct tagPosition
{
	float x;
	float y;
	struct tagPosition(float x, float y) :x(x), y(y) {}
	struct tagPosition() :x(0), y(0) {}
}POS;

typedef struct tagStatus
{
	float hp;//ü��
	float maxHp; //�ִ�ü��
	float moveSpeed; //�̼�
	float attackDamage; //���ݷ�
	//�ʿ��� �ɷ�ġ ��� ������ �߰�

	struct tagStatus(float hp, float moveSpeed, float attackDamage) :hp(hp),maxHp(hp),moveSpeed(moveSpeed),attackDamage(attackDamage) {}

}STATUS;
	