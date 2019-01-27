#pragma once

#define P -1
#define E -2

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
	Player_class(char myFigure, char enemyFigure);

	void FillMask(char map[11][11], int mask[10][10]);

	void CreateMask(char map[11][11], int mask[10][10]);

	void SetCellValue(int mask[10][10], int y, int x);
};

