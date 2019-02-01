#pragma once

#define P -1
#define E -2

struct Cell
{
	int value = 0;
	int combinations = 0;
};

struct Dir
{
	int lY, lX;
	int rY, rX;
};

class Player_class
{
private:
	char _myFigure;
	char _enemyFigure;

public:

	Cell mask[10][10];

	Player_class(char myFigure, char enemyFigure);

	void FillMask(char map[11][11]);

	void CreateMask(char map[11][11]);

	void SetCellValue(int y, int x);
};

