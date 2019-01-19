#pragma once
class Player_class
{
private:
	char _myFigure;
	char _enemyFigure;


public:
	Player_class(char myFigure, char enemyFigure);

	void FillMask(char map[11][11], int mask[10][10]);

	void CreateMask(char map[11][11], int mask[10][10]);
	void CheckHorisontals(int mask[10][10]);
	void CheckVerticals(int mask[10][10]);
	void CheckDiagonals(int mask[10][10]);
};

