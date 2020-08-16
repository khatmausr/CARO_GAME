#pragma once
#include "common.h"

class board
{
private:
	int** arr;
	int countX, countO;

public:
	board();
	~board();

	void resetBoard();
	void displayBoard();
	bool markCell(int x, int y, int val);
	int  checkBoard(int x, int y, int& x_begin, int& y_begin);

	int getCountX();
	int getCountO();
};
