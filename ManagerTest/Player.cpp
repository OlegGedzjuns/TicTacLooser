#include "Player.h"

#include <iostream>

using namespace std;

Player_class::Player_class(char myFigure, char enemyFigure)
{
	_myFigure = myFigure;
	_enemyFigure = enemyFigure;
}

void Player_class::FillMask(char map[11][11])
{
	CreateMask(map);	//creates mask (0 free / -1 player / -2 - enemy)
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			SetCellValue(i, j);	//give all the cells on mask strengh
#if _DEBUG
			cout << mask[i][j].value << "/" << mask[i][j].combinations << '\t';
#endif
		}
#if _DEBUG
		cout << endl;
#endif
	}
#if _DEBUG
	system("pause");
#endif
}

void Player_class::CreateMask(char map[11][11])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[i][j] == '.') mask[i][j].value = 0;
			else if (map[i][j] == _myFigure) mask[i][j].value = P;
			else if (map[i][j] == _enemyFigure) mask[i][j].value = E;
		}
	}
}

void Player_class::SetCellValue(int y, int x)
{
	if (mask[y][x].value == P || mask[y][x].value == E)
		return;

	Dir direction[4] =
	{
		{-1, +1, -1, +1},	// (\)
		{-1, +1, 0, 0},		// (|)
		{-1, +1, +1, -1},	// (/)
		{0, 0, +1, -1}		// (-)
	};
	
	for (int i = 0; i < 4; i++)
	{
		bool rowEnd[2] = { false, false };
		bool end[2] = { false, false };

		int posibleLen = 1;	//maximal cnt of figures posible in a row
		int rowLen = 0;		//cnt of figures in a row
		int radius = 1;		//distance to cell

		while (!end[0] || !end[1])
		{
			for (int j = 0; j <= 1; j++)
			{
				if (!end[j])
				{
					int checkY = y + (radius * direction[i].Y[j]);
					int checkX = x + (radius * direction[i].X[j]);
					if (checkY < 0 || checkY > 9 || checkX < 0 || checkX > 9)
					{
						end[j] = true;
					}
					else
					{
						if (mask[checkY][checkX].value == P && !rowEnd[j])
						{
							rowLen++;
							posibleLen++;
						}
						else if (mask[checkY][checkX].value != E && posibleLen < 5)
						{
							rowEnd[j] = true;
							posibleLen++;
						}
						else
						{
							end[j] = true;
						}
					}
				}
			}
			radius++;
		}
		if (rowLen >= 1 && posibleLen >= 5)
		{
			mask[y][x].combinations++;
		}
		if (rowLen > mask[y][x].value && posibleLen >= 5)
		{
			mask[y][x].value = rowLen;
		}
	}
}
