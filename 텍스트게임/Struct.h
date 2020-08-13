#pragma once
typedef struct Position
{
	int x;
	int y;
	struct Position(int x, int y) :x(x), y(y) {}
}POS;