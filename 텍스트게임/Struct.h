#pragma once
typedef struct tagPosition
{
	float x;
	float y;
	struct tagPosition(float x, float y) :x(x), y(y) {}
}POS;

typedef struct tagStatus
{
	float hp;//ü��
	float maxHp; //�ִ�ü��
	float moveSpeed; //�̼�
	float attackDamage; //���ݷ�
	//�ʿ��� �ɷ�ġ ��� ������ �߰�

	struct tagStatus(float hp, float moveSpeed, float attackDamage) :hp(hp), moveSpeed(moveSpeed),attackDamage(attackDamage) {}

}STATUS;