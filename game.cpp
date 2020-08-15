#include "common.h"

bool game::isContinue()
{
	return (g2.isContinue());
}

void game::continueGame()
{
	if (g2.isContinue()) g2.continueGame();
}

void game::startTwoPlayers()
{
	g2.resetData();
	g2.newGame();
}