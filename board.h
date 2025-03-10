#pragma once
#include <vector>

#define BOARD_SIZE 20

class board
{
private:
	int** arr;
	int   countX, countO;

public:
	board();
	~board();

	std::vector <int> exportBoard();
	bool importBoard(std::vector <int> dataBoard);

	void resetBoard();
	void displayBoard();
	bool markCell(int x, int y, int val);
	void redoMarkCell(int x, int y);
	int  checkBoard(int x, int y, int& x_begin, int& y_begin, int k = 5);

	int  getCell(int x, int y);
	int  getCountX();
	int  getCountO();
};
