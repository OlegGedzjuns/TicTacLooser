#include "Game.h"

using namespace std;

bool Game_class::IsFirstStep(char map[11][11])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[i][j] == 'X' || map[i][j] == '0')
			{
				return false;
			}
		}
	}
	return true;
}

Game_class::Game_class(Communication_class *communicator)
{
	_communicator = communicator;
	_player = new Player_class(
		_communicator->GetFigure(),
		_communicator->GetFigure() == 'X' ? '0' : 'X');
	_enemy = new Player_class(
		_communicator->GetFigure() == 'X' ? '0' : 'X',
		_communicator->GetFigure());
}

void Game_class::TakeAStep()
{
	char map[11][11];
	_communicator->GetMap(map);
	if (IsFirstStep(map))
	{
		_communicator->PrintPos('E', 4);
		return;
	}
	int playerMask[10][10];
	int enemyMask[10][10];

	_player->FillMask(map, playerMask);
	_enemy->FillMask(map, enemyMask);

	Coords place = FindBest(playerMask, enemyMask);
	_communicator->PrintPos((char)place.x + 'A', place.y);
	return;
}

Coords Game_class::FindBest(int pMask[10][10], int eMask[10][10])
{
	int eMaxY = 0, eMaxX = 0;
	int pMaxY = 0, pMaxX = 0;
	for (int Y = 0; Y < 10; Y++)
	{
		for (int X = 0; X < 10; X++)
		{
			if (eMask[eMaxY][eMaxX] < eMask[Y][X])
			{
				eMaxY = Y;
				eMaxX = X;
			}
			if (pMask[pMaxY][pMaxX] < pMask[Y][X])
			{
				pMaxY = Y;
				pMaxX = X;
			}
		}
	}
	if (eMask[eMaxY][eMaxX] >= 4)
	{
		return { eMaxX, eMaxY };
	}
	if (pMask[pMaxY][pMaxX] >= 3)
	{
		return { pMaxX, pMaxY };
	}
	if (eMask[eMaxY][eMaxX] >= 2)
	{
		return { eMaxX, eMaxY };
	}
	return { pMaxX, pMaxY };
}
