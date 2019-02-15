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
	bool IsFirstStep(char map[10][11]);
public:
	Game_class(Communication_class *communicator);
	void TakeAStep();
	Coords FindBest(char map[10][11]);
};

