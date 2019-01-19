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
	int finalMap[10][10];
	int maxY = 0, maxX = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (pMask[i][j] == -1 || pMask[i][j] == -2 || eMask[i][j] == -1 || eMask[i][j] == -2)
			{
				continue;
			}
			else
			{
				finalMap[i][j] = pMask[i][j] - eMask[i][j];
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (finalMap[i][j] > finalMap[maxY][maxX])
			{
				maxY = i;
				maxX = j;
			}
		}
	}
	return { maxX , maxY };
}
