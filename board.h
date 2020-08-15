#pragma once
#include "common.h"

class board
{
private:
	int** arr;

public:
	board();
	~board();

	void resetBoard();
	void displayBoard();
	bool markCell(int x, int y, int val);
	int  checkBoard(int x, int y);
};
