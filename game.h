#pragma once
#include "common.h"

class game
{
private:
	twoPlayers g2;

public:
	bool isContinue();
	void continueGame();

	void startTwoPlayers();
};