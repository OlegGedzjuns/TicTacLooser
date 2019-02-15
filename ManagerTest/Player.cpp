#include "Player.h"

#include <cmath>
#if _DEBUG
	#include <iostream>
#endif

using namespace std;

Player_class::Player_class(char MyFigure, char EnemyFigure)
{
	myFigure = MyFigure;
	enemyFigure = EnemyFigure;
}

int Player_class::FillMask(char map[10][11])
{
	int fieldStrenght = 0;
	CreateMask(map);	//creates mask (0 free / -1 player / -2 - enemy)
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			SetCellValue(i, j);	//give all the cells on mask strengh
			if (mask[i][j].value >= 3 && mask[i][j].open)
			{
				mask[i][j].strenght *= 2;
			}
			fieldStrenght += mask[i][j].strenght;
#if _DEBUG
			cout << mask[i][j].value;
			if (mask[i][j].open)
				cout << "+";
			cout << "\t";
#endif
		}
#if _DEBUG
		cout << endl;
#endif
	}
#if _DEBUG
	//system("pause");
#endif
	return fieldStrenght;
}

void Player_class::CreateMask(char map[10][11])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[i][j] == '.')
			{
				mask[i][j].value = 0;
				mask[i][j].combinations = 0;
				mask[i][j].strenght = 0;
				mask[i][j].open = false;
			}
			else if (map[i][j] == myFigure)
			{
				mask[i][j].value = P;
				mask[i][j].combinations = 0;
				mask[i][j].strenght = 0;
				mask[i][j].open = false;
			}
			else if (map[i][j] == enemyFigure)
			{
				mask[i][j].value = E;
				mask[i][j].combinations = 0;
				mask[i][j].strenght = 0;
				mask[i][j].open = false;
			}
		}
	}
}

void Player_class::SetCellValue(int y, int x)
{
	if (mask[y][x].value == P || mask[y][x].value == E)
		return;
	
	for (int i = 0; i < 4; i++)
	{
		bool rowEnd[2] = { false, false };
		bool end[2] = { false, false };
		bool open[2] = { false, false };

		int posibleLen = 1;	//maximal cnt of figures posible in a row
		int rowLen = 0;		//cnt of figures in a row
		int radius = 1;		//distance to cell

		while (!end[0] || !end[1])
		{
			for (int j = 0; j <= 1; j++)
			{
				if (!end[j])
				{
					int checkY = y + (radius * _direction[i].Y[j]);
					int checkX = x + (radius * _direction[i].X[j]);
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
						else if (mask[checkY][checkX].value != E)
						{
							open[j] = true;
							if (posibleLen < 5)
							{
								rowEnd[j] = true;
								posibleLen++;
							}
							else
							{
								end[j] = true;
							}
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
			mask[y][x].strenght += 0.1 * pow(10, rowLen);
		}
		if (rowLen > mask[y][x].value && posibleLen >= 5)
		{
			if (open[0] && open[1])
			{
				mask[y][x].open = true;
			}
			mask[y][x].value = rowLen;
		}
	}
}
