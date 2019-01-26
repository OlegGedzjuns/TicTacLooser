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
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			SetCellValue(mask, i, j);
			//cout << mask[i][j] << '\t';
		}
		//cout << endl;
	}
	//system("pause");
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

void Player_class::SetCellValue(int mask[10][10], int y, int x)
{
	if (mask[y][x] == -1 || mask[y][x] == -2)
		return;

	Dir direction[4] = 
	{
		{-1, -1, +1, +1},	// (\)
		{-1, 0, +1, 0},		// (|)
		{-1, +1, +1, -1},	// (/)
		{0, +1, 0, -1}		// (-)
	};
	
	for (int i = 0; i < 4; i++)
	{
		bool leftRowEnd = false, leftEnd = false;
		bool rightRowEnd = false, rightEnd = false;

		int posibleLen = 1;
		int rowLen = 0;
		int radius = 1;
		while (!leftEnd || !rightEnd)
		{
			if (!leftEnd)
			{
				int checkY = y + (radius * direction[i].lY);
				int checkX = x + (radius * direction[i].lX);
				if (checkY < 0 || checkY > 9 || checkX < 0 || checkX > 9)
				{
					leftEnd = true;
				}
				else
				{
					if (mask[checkY][checkX] == -1 && !leftRowEnd)
					{
						rowLen++;
						posibleLen++;
					}
					else if (mask[checkY][checkX] != -2 && posibleLen < 5)
					{
						leftRowEnd = true;
						posibleLen++;
					}
					else
					{
						leftEnd = true;
					}
				}
			}
			if (!rightEnd)
			{
				int checkY = y + (radius * direction[i].rY);
				int checkX = x + (radius * direction[i].rX);
				if (checkY < 0 || checkY > 9 || checkX < 0 || checkX > 9)
				{
					rightEnd = true;
				}
				else
				{
					if (mask[checkY][checkX] == -1 && !rightRowEnd)
					{
						rowLen++;
						posibleLen++;
					}
					else if (mask[checkY][checkX] != -2 && posibleLen < 5)
					{
						rightRowEnd = true;
						posibleLen++;
					}
					else
					{
						rightEnd = true;
					}
				}
			}
			radius++;
		}
		if (rowLen > mask[y][x] && posibleLen >= 5)
			mask[y][x] = rowLen;
	}
}
