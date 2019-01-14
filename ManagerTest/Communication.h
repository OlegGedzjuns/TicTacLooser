#pragma once

#include <string>
#include <fstream>

using namespace std;

class Communication_class
{
private:
	char _figure;
	ifstream _inputF;
	ofstream _outputF;
public:
	Communication_class(char myFigure, string &inputPath, string &outputPath);
	~Communication_class();

	void PrintInfo();
	void PrintPos(char c, int i);
	char GetFigure();
	void GetMap(char map[10][10]);
};

