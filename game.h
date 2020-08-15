#pragma once
#include "common.h"

class game
{
private:
	// onePlayer g1;
	twoPlayers g2;

public:
	bool isContinue();
	void continueGame();

	void startOnePlayer();
	void startTwoPlayers();
};