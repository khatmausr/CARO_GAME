#include "common.h"

bool game::isContinue()
{
	return (g2.isContinue());
}

void game::continueGame()
{
	if (g2.isContinue()) g2.continueGame();
}

void game::startOnePlayer()
{
	//g1.resetData();
	//g2.resetData();
	//g1.newGame();
}

void game::startTwoPlayers()
{
	// g1.resetData();
	g2.resetData();
	g2.newGame();
}