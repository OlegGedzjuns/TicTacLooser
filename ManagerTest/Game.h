#pragma once

#include "Communication.h"
#include "Player.h"

struct Coords
{
	int x;
	int y;
};

class Game_class
{
private:
	Player_class *_player;
	Player_class *_enemy;
	Communication_class *_communicator;

	bool IsFirstStep(char map[11][11]);
public:
	Game_class(Communication_class *communicator);

	void TakeAStep();
	Coords FindBest(int pMask[10][10], int e[10][10]);
};

