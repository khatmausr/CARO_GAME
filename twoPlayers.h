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

	void processKeyPressed(int keyCode, bool& isExit);
	void changeTurn();
	bool displayWinners(int whoWin);
};