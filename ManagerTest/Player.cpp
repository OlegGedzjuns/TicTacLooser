#include "Player.h"

#include <iostream>

using namespace std;


Player_class::Player_class(char myFigure, char enemyFigure)
{
	_myFigure = myFigure;
	_enemyFigure = enemyFigure;
}

void Player_class::FillMask(char map[11][11], int mask[10][10])
{
	CreateMask(map, mask);
	CheckHorisontals(mask);
	CheckVerticals(mask);
	//CheckDiagonals(mask);
}

void Player_class::CreateMask(char map[11][11], int mask[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[i][j] == '.') mask[i][j] = 0;
			else if (map[i][j] == _myFigure) mask[i][j] = -1;
			else if (map[i][j] == _enemyFigure) mask[i][j] = -2;
		}
	}
}

void Player_class::CheckHorisontals(int mask[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		int posToCnt = -1;
		for (int j = 0; j < 10; j++)
		{
			if (posToCnt == -1 && mask[i][j + 1] == -1)
			{
				posToCnt = j;
				continue;
			}
			if (posToCnt != -1 && mask[i][j] == -1)
			{
				mask[i][posToCnt]++;
			}
			else
			{
				if (mask[i][j + 1] == -1)
				{
					posToCnt = j;
					continue;
				}
				posToCnt = -1;
			}
		}
		posToCnt = -1;
		for (int j = 9; j >= 0; j--)
		{
			if (posToCnt == -1 && mask[i][j - 1] == -1)
			{
				posToCnt = j;
				continue;
			}
			if (posToCnt != -1 && mask[i][j] == -1)
			{
				mask[i][posToCnt]++;
			}
			else
			{
				if (mask[i][j - 1] == -1)
				{
					posToCnt = j;
					continue;
				}
				posToCnt = -1;
			}
		}
	}
}

void Player_class::CheckVerticals(int mask[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		int posToCnt = -1;
		for (int j = 0; j < 10; j++)
		{
			if (posToCnt == -1 && mask[j + 1][i] == -1 && mask[j][i] != -1 && mask[j][i] != -2)
			{
				posToCnt = j;
				continue;
			}
			if (posToCnt != -1 && mask[j][i] == -1)
			{
				mask[posToCnt][i]++;
			}
			else
			{
				if (mask[j + 1][i] == -1 && mask[j][i] != -1 && mask[j][i] != -2)
				{
					posToCnt = j;
					continue;
				}
				posToCnt = -1;
			}
		}
		posToCnt = -1;
		for (int j = 9; j >= 0; j--)
		{
			if (posToCnt == -1 && mask[j - 1][i] == -1)
			{
				posToCnt = j;
				continue;
			}
			if (posToCnt != -1 && mask[j][i] == -1)
			{
				mask[posToCnt][i]++;
			}
			else
			{
				if (mask[j - 1][i] == -1)
				{
					posToCnt = j;
					continue;
				}
				posToCnt = -1;
			}
		}
	}
}

void Player_class::CheckDiagonals(int mask[10][10])
{
}
