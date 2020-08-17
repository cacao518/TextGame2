#pragma once
typedef struct tagPosition
{
	float x;
	float y;
	struct tagPosition(float x, float y) :x(x), y(y) {}
	struct tagPosition() :x(0), y(0) {}

	struct tagPosition operator+(struct tagPosition pos)
	{
		struct tagPosition returnPos;
		returnPos.x = x + pos.x;
		returnPos.y = y + pos.y;
		return returnPos;

	}
}POS;

typedef struct tagStatus
{
	float hp;//체력
	float maxHp; //최대체력
	float moveSpeed; //이속
	float attackDamage; //공격력
	//필요한 능력치 요소 있으면 추가

	struct tagStatus(float hp, float moveSpeed, float attackDamage) :hp(hp),maxHp(hp),moveSpeed(moveSpeed),attackDamage(attackDamage) {}

}STATUS;
	