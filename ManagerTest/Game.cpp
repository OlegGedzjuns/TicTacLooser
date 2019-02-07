#include "Game.h"

#if _DEBUG
	#include<iostream>
#endif

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

	_player->FillMask(map);
	_enemy->FillMask(map);

	Coords place = FindBest();
#if _DEBUG
	cout << place.x << " " << place.y << endl;
	system("pause");
#endif
	_communicator->PrintPos((char)place.x + 'A', place.y);
	return;
}

Coords Game_class::FindBest()
{
	int eMaxY = 0, eMaxX = 0;
	int pMaxY = 0, pMaxX = 0;
	for (int Y = 0; Y < 10; Y++)
	{
		for (int X = 0; X < 10; X++)
		{
			if (_enemy->mask[eMaxY][eMaxX].value < _enemy->mask[Y][X].value)
			{
				eMaxY = Y;
				eMaxX = X;
			}
			else if (_enemy->mask[eMaxY][eMaxX].value == _enemy->mask[Y][X].value &&
				(_enemy->mask[eMaxY][eMaxX].combinations < _enemy->mask[Y][X].combinations /*|| _enemy->mask[Y][X].open*/))
			{
				eMaxY = Y;
				eMaxX = X;
			}
			if (_player->mask[pMaxY][pMaxX].value < _player->mask[Y][X].value)
			{
				pMaxY = Y;
				pMaxX = X;
			}
			else if (_player->mask[pMaxY][pMaxX].value == _player->mask[Y][X].value &&
				(_player->mask[pMaxY][pMaxX].combinations < _player->mask[Y][X].combinations /*|| _player->mask[Y][X].open*/))
			{
				pMaxY = Y;
				pMaxX = X;
			}
		}
	}
	/*if (_player->mask[pMaxY][pMaxX].value >= 4)
	{
		return { pMaxX, pMaxY };
	}
	if (_enemy->mask[eMaxY][eMaxX].value >= 4)
	{
		return { eMaxX, eMaxY };
	}
	if (_player->mask[pMaxY][pMaxX].value >= 3 && _player->mask[pMaxY][pMaxX].open)
	{
		return { pMaxX, pMaxY };
	}
	if (_enemy->mask[eMaxY][eMaxX].value >= 3 && _enemy->mask[eMaxY][eMaxX].open)
	{
		return { eMaxX, eMaxY };
	}
	if (_player->mask[pMaxY][pMaxX].value > _enemy->mask[eMaxY][eMaxX].value)
	{
		if(_enemy->mask[eMaxY][eMaxX].open && _player->mask[pMaxY][pMaxX].value - _enemy->mask[eMaxY][eMaxX].value > 1)
			return { pMaxX, pMaxY };
		if (!_enemy->mask[eMaxY][eMaxX].open)
			return { pMaxX, pMaxY };
	}
	return { eMaxX, eMaxY };*/

	if (_enemy->mask[eMaxY][eMaxX].value >= 4)
	{
		return { eMaxX, eMaxY };
	}
	if (_player->mask[pMaxY][pMaxX].value >= 3)
	{
		return { pMaxX, pMaxY };
	}
	if (_enemy->mask[eMaxY][eMaxX].value >= 2)
	{
		return { eMaxX, eMaxY };
	}
	if (_player->mask[pMaxY][pMaxX].value == 0)
	{
		return { eMaxX, eMaxY };
	}
	return { pMaxX, pMaxY };
}
