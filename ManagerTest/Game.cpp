#include "Game.h"

using namespace std;

bool Game_class::IsFirstStep(char map[10][10])
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
	char map[10][10];
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
}

Coords Game_class::FindBest(int playerMask[10][10], int enemyMask[10][10])
{
	return Coords();
}
