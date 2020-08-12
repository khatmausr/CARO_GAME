#pragma once
#include "common.h"

class game
{
private:
	int turn;
	int  x, y;
	std::string name1, name2;

public:
	board b;
	
	game();	
	void continueGame();
	void loadGame();
	bool isContinue();
	void changeTurn();
	void startTwoPlayers();
	void displayWinner(int whoWin);
};