#pragma once
class Player_class
{
private:
	char _myFigure;
	char _enemyFigure;


public:
	Player_class(char myFigure, char enemyFigure);

	void FillMask(char map[10][10], int mask[10][10]);

	void CreateMask(char map[10][10], int mask[10][10]);
	void CheckHorisontals(char map[10][10], int mask[10][10]);
	void CheckVerticals(char map[10][10], int mask[10][10]);
	void CheckDiagonals(char map[10][10], int mask[10][10]);
};

