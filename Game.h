#pragma once
#include "common.h"
#include "board.h"

// Save - Load Game Data Struct - Using for storing data by binary format file
struct saveGameData
{
	int  _typeGame;
	int  _board[BOARD_SIZE * BOARD_SIZE + 2];
	int  _turn = 0;
	Vector2u cursorP;
	int  _scoreX, _scoreO;
	bool _isExit;
};

class Game
{
protected:
	board b;
	int   typeGame; // 0: 2P | 1,2,3: Easy, Med, Hard
	int   turn;	// -1 : O | 0 : exit | 1 : X
	int   scoreX, scoreO;
	bool  isExit;
	bool  vol; // 0 : off sound/music | ON

	Vector2u    cursorP; // Cursor Position
	std::string playerName[2];
	sf::Sprite  background;

	virtual void askForName() = 0;
	virtual void processKeyPressed(int keyCode) = 0;
	
	void runGame();
	void exitGame();
	void displayGame();

	void resetData();
	void changeTurn();
	void markWin(int x_begin, int y_begin, int direction);
	bool displayWin(bool isDraw = false);
	
public:
	Game(sf::Texture* bgTexture);
	virtual ~Game();

	bool isContinue();
	void continueGame();
	void newGame();

	void askForLoad();
	void askForSave();
	void saveGame(std::string fileName);
	void loadGame(std::string fileName);

	int  getType();
};

