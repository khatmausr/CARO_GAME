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
};