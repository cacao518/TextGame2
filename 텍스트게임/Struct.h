#pragma once
typedef struct Position
{
	float x;
	float y;
	struct Position(float x, float y) :x(x), y(y) {}
	struct Position():x(0),y(0){}
}POS;