#pragma once
typedef struct Position
{
	float x;
	float y;
	struct Position(float x, float y) :x(x), y(y) {}
}POS;