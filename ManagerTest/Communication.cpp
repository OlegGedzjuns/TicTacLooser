#include "Communication.h"

Communication_class::Communication_class(char myFigure, string &inputPath, string &outputPath)
{
	_figure = myFigure;
	_inputF.open(inputPath);
	_outputF.open(outputPath);
}

Communication_class::~Communication_class()
{
	_inputF.close();
	_outputF.close();
}

void Communication_class::PrintInfo()
{
	_outputF << "Oleg Gedzjuns\nrelease v1\n";
}

void Communication_class::PrintPos(char c, int i)
{
	_outputF << c << i << endl;
}

char Communication_class::GetFigure()
{
	return _figure;
}

void Communication_class::GetMap(char map[11][11])
{
	for (int i = 0; i < 10; i++)
	{
		_inputF.getline(map[i], 11, '\n');
	}
}
