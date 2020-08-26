#pragma once
#include "Game.h"
class Game;
class twoPlayers
	: public Game
{
private:
	void askForName();
	void processKeyPressed(int keyCode);
public:
	twoPlayers(sf::Texture* bgTexture);
	virtual ~twoPlayers();
	bool displayWinners(int x_begin, int y_begin, int direction, int whoWin);
};