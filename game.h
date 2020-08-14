#pragma once
#include "common.h"

class game
{
private:
	bool continueGame;
	int turn;
	int  x, y;
	std::string name1, name2;

public:
	board b;
	
	game();	
	void setContinue(bool isContinue);
	void loadGame();
	bool isContinue();
	void changeTurn();
	void startTwoPlayers();
	void displayWinner(int whoWin);
};