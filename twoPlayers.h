#pragma once
#include "common.h"

class twoPlayers
{
private:
	board b;
	int turn;
	int x, y;
	int scoreX, scoreO;

public:
	twoPlayers();

	bool isContinue();

	void resetData();
	void newGame();
	void continueGame();
	void runGame();

	void processKeyPressed(int keyCode, bool& isExit);
	void changeTurn();
	bool displayWinners(int x_begin, int y_begin, int direction, int whoWin);
};