#include <string>

#include "Communication.h"
#include "Game.h"

using namespace std;

int main(int argc, char* argv[])
{
#if _DEBUG
	string player = "X";		//X or 0
	string inputPath = "field.txt";		//input path
	string outputPath = "result.txt";	//output path
#else
	string player = argv[1];		//X or 0
	string inputPath = argv[2];		//input path
	string outputPath = argv[3];	//output path
#endif

	Communication_class *communicator = new Communication_class(player[0], inputPath, outputPath);

	if (player == "INFO")
	{
		communicator->PrintInfo();
	}
	else
	{
		Game_class *game = new Game_class(communicator);
		game->TakeAStep();
	}

	delete communicator;
	return 0;
}