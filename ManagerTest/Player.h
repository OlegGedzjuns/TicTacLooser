#pragma once

#define P -1
#define E -2

struct Cell
{
	int value = 0;
	int combinations = 0;
	int strenght = 0;
	bool open = false;
};

struct Dir
{
	int Y[2];
	int X[2];
};

class Player_class
{
private:
	Dir _direction[4] =
	{
		{-1, +1, -1, +1},	// (\)
		{-1, +1, 0, 0},		// (|)
		{-1, +1, +1, -1},	// (/)
		{0, 0, +1, -1}		// (-)
	};
	char _myFigure;
	char _enemyFigure;
public:
	Cell mask[10][10];
	Player_class(char myFigure, char enemyFigure);
	int FillMask(char map[11][11]);
	void CreateMask(char map[11][11]);
	void SetCellValue(int y, int x);
};

