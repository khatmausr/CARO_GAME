#pragma once
#include "Game.h"

class onePlayer : public Game
{
private:
	void askForName();
	void drawLine(int x_begin, int y_begin, int direction);
	bool displayResult(int whoWin);
	void processKeyPressed(int keyCode);

	double   distance(Vector2u pA, Vector2u pB);
	Vector2u botMove();
	Vector2u easyBotMove();
	Vector2u medBotMove();
	Vector2u hardBotMove();

public:
	onePlayer(Texture* bgTexture, int level);
	~onePlayer();
};