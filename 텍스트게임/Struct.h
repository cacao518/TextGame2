#pragma once
typedef struct tagPosition
{
	float x;
	float y;
	struct tagPosition(float x, float y) :x(x), y(y) {}
}POS;

typedef struct tagStatus
{
	float hp;//체력
	float maxHp; //최대체력
	float moveSpeed; //이속
	float attackDamage; //공격력
	//필요한 능력치 요소 있으면 추가

	struct tagStatus(float hp, float moveSpeed, float attackDamage) :hp(hp), moveSpeed(moveSpeed),attackDamage(attackDamage) {}

}STATUS;