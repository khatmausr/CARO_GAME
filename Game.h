#pragma once
#include "board.h"
using namespace sf;
// Save - Load Game Data Struct - Using for storing data by binary format file
struct saveGameData
{
	int _typeGame;
	int _board[BOARD_SIZE * BOARD_SIZE + 2];
	int _turn;
	Vector2u cursorP;
	int _scoreX, _scoreO;
	bool _isExit;
};

class Game
{
protected:
	int typeGame; // 0: 2P | 1,2,3: Easy, Med, Hard
	board b;
	int turn;
	Vector2u cursorP; // Cursor Position
	int scoreX, scoreO;
	bool isExit;
	std::string playerName[2];
	sf::Sprite background;

protected:
	virtual void askForName() = 0;
	virtual void processKeyPressed(int keyCode) = 0;
	
	void runGame();
	void resetData();
	void exitGame();
	void saveGame(std::string fileName);
	void loadGame(std::string fileName);

	void displayGame();

	void changeTurn();
	
public:
	Game(sf::Texture* bgTexture);
	virtual ~Game();
	bool isContinue();
	void continueGame();
	void newGame();
	void askForLoad();
	void askForSave();
	int getType();
};

