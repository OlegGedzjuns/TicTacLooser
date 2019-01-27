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
	CreateMask(map, mask);	//creates mask (0 free / -1 player / -2 - enemy)
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			SetCellValue(mask, i, j);	//give all the cells on mask strengh
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
			else if (map[i][j] == _myFigure) mask[i][j] = P;
			else if (map[i][j] == _enemyFigure) mask[i][j] = E;
		}
	}
}

void Player_class::SetCellValue(int mask[10][10], int y, int x)
{
	if (mask[y][x] == P || mask[y][x] == E)
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

		int posibleLen = 1;	//maximal cnt of figures posible in a row
		int rowLen = 0;		//cnt of figures in a row
		int radius = 1;		//distance to cell
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
					if (mask[checkY][checkX] == P && !leftRowEnd)
					{
						rowLen++;
						posibleLen++;
					}
					else if (mask[checkY][checkX] != E && posibleLen < 5)
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
					if (mask[checkY][checkX] == P && !rightRowEnd)
					{
						rowLen++;
						posibleLen++;
					}
					else if (mask[checkY][checkX] != E && posibleLen < 5)
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
