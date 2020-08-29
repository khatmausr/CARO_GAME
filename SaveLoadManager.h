#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define MAX_SAVEGAME 10

// Save Game Files Manager Struct
struct saveGameInfo
{
	std::string _filename;
	int _typeGame;
	std::string _s1, _s2;
	tm* _ltm;
};

class SaveLoadManager
{
private:
	std::vector <saveGameInfo> saveList;
	void updateSaveList();
	void updateFileManager();

public:
	bool checkFile(std::string filename, int typeGame);
	void pushSaveGame(saveGameInfo& temp);
	int  loadForGame(std::string& filename);
};