#include "Player.h"



Player_class::Player_class(char myFigure, char enemyFigure)
{
	_myFigure = myFigure;
	_enemyFigure = enemyFigure;
}

void Player_class::FillMask(char map[10][10], int mask[10][10])
{
	CreateMask(map, mask);
	CheckHorisontals(map, mask);
	CheckVerticals(map, mask);
	CheckDiagonals(map, mask);
}

void Player_class::CreateMask(char map[10][10], int mask[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			char cur = map[i][j];

			if (cur == '.') mask[i][j] = 0;
			else if (cur == _myFigure) mask[i][j] = -1;
			else if (cur == _enemyFigure) mask[i][j] = -2;
		}
	}
}

void Player_class::CheckHorisontals(char map[10][10], int mask[10][10])
{
}

void Player_class::CheckVerticals(char map[10][10], int mask[10][10])
{
}

void Player_class::CheckDiagonals(char map[10][10], int mask[10][10])
{
}
