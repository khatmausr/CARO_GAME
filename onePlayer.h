#pragma once
#include "Game.h"

class onePlayer : public Game
{
private:
	void askForName();
	bool displayResult(int x_begin, int y_begin, int direction, int whoWin);
	void processKeyPressed(int keyCode);

	double   distance(Vector2u pA, Vector2u pB);
	Vector2u botMove();
	Vector2u easyBotMove();
	Vector2u medBotMove();
	Vector2u hardBotMove();
	Vector3i alphaBetaPrunning(bool isMaximize, int depth, int maxDepth);

public:
	onePlayer(Texture* bgTexture, int level);
	~onePlayer();
};