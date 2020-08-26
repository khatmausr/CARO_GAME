#pragma once
#include "common.h"
#define BOARD_SIZE 20
class board
{
private:
	int** arr;
	int countX, countO;

public:
	board();
	~board();

	std::vector <int> exportBoard();
	bool importBoard(std::vector <int> dataBoard);

	void resetBoard();
	void displayBoard();
	bool markCell(int x, int y, int val);
	int  checkBoard(int x, int y, int& x_begin, int& y_begin);

	int getCountX();
	int getCountO();
};
