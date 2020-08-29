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
	std::string _s1, _s2; // 2P game: s1: player 1's name, s2: player 2's name
						// 1P game: s1: player's name, s2: score
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
};