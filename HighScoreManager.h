#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define MAX_RECORD 10

// High Score Manager Struct
struct HighScoreInfo
{
	std::string _playerName;
	int _typeGame;
	int _score;
	int _scoreX;
	int _scoreO;
	tm* _ltm;
};

std::string typeGameConverter(unsigned int typeGame);

class HighScoreManager
{
private:
	std::vector <HighScoreInfo> highScoreList;
	void updateHighScoreList();
	void sortHighScoreList();
	void updateFileManager();
	void resetHighScore();

public:
	void pushHighScore(HighScoreInfo& temp);
	void showHighScore();
};