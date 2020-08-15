#pragma once
#include "common.h"

class twoPlayers
{
private:
	board b;
	int turn;
	int x, y;

public:
	twoPlayers();

	bool isContinue();

	void resetData();
	void newGame();
	void continueGame();
	void runGame();

	void processKeyPressed(int keyCode);
	void changeTurn();
	void displayWinners(int whoWin);
};