#pragma once
#include "common.h"

class twoPlayers
{
private:
	board b;
	int turn;
	int x, y;
	int scoreX, scoreO;
	bool isExit;
	std::string playerName[2];
	sf::Sprite background;

public:
	twoPlayers(sf::Texture* backgroundTexture);

	bool isContinue();

	void resetData();
	void newGame();
	void continueGame();
	void runGame();
	void exitGame();

	void askForName();
	void askForSave();
	void saveGame(std::string filename);	
	void askForLoad();
	void loadGame(std::string filename);

	void processKeyPressed(int keyCode);
	void changeTurn();
	void displayGameScreen();
	bool displayWinners(int x_begin, int y_begin, int direction, int whoWin);
};