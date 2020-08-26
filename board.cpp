#include "board.h"

board::board()
{
	arr = new int* [BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		arr[i] = new int[BOARD_SIZE];
		for (int j = 0; j < BOARD_SIZE; j++) arr[i][j] = 0;
	}
	countX = countO = 0;
}

board::~board()
{
	for (int i = 0; i < BOARD_SIZE; i++) delete[] arr[i];
	delete[] arr;
	countX = countO = 0;
}

std::vector <int> board::exportBoard()
{
	std::vector <int> ans;

	ans.push_back(countX); ans.push_back(countO);
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			ans.push_back(arr[i][j]);

	return ans;
}

bool board::importBoard(std::vector <int> dataBoard)
{
	if (dataBoard.size() == BOARD_SIZE * BOARD_SIZE + 2)
	{
		countX = dataBoard[0]; countO = dataBoard[1];
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
				arr[i][j] = dataBoard[i * BOARD_SIZE + j + 2];
		return true;
	}
	return false;
}

void board::resetBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			arr[i][j] = 0;
	countX = countO = 0;
}

void board::displayBoard()
{
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
			if (arr[i][j] == 1)
			{
				button_X.setPosition(Vector2f(BOARD_LEFT + j * 30, BOARD_TOP + i * 30));
				window.draw(button_X);
			}
			else if (arr[i][j] == -1)
			{
				button_O.setPosition(Vector2f(BOARD_LEFT + j * 30, BOARD_TOP + i * 30));
				window.draw(button_O);
			}
}

bool board::markCell(int x, int y, int val)
{
	if (!arr[x][y])
	{
		arr[x][y] = val;
		if (val == 1) countX++;
		else if (val == -1) countO++;
		return true;
	}
	return false;
}

int board::checkBoard(int x, int y, int& x_begin, int& y_begin) 
// Return direction of winning cells: 0 - Nothing, 1 - Vertical, 2 - Horizon, 3 - Diagonal, 4 - Anti Diagonal
{
	x_begin = 0; y_begin = 0;
	if (arr[x][y] == 0) return 0;

	// Declairing
	int i_above, i_below, j_left, j_right;
	bool block_above, block_below, block_left, block_right;

	// Check vertical
	i_above = i_below = x;
	while ((i_above > 0) && (arr[i_above - 1][y] == arr[x][y])) i_above--;
	while ((i_below < BOARD_SIZE - 1) && (arr[i_below + 1][y] == arr[x][y])) i_below++;
	if (i_above == 0) block_above = 1; else block_above = arr[i_above - 1][y];
	if (i_below == BOARD_SIZE - 1) block_below = 1; else block_below = arr[i_below + 1][y];

	if ((i_below - i_above + 1 == 5) && (!block_above || !block_below))
	{
		x_begin = i_above; y_begin = y;
		return 1;
	}

	// Check horizon
	j_left = j_right = y;
	while ((j_left > 0) && (arr[x][j_left - 1] == arr[x][y])) j_left--;
	while ((j_right < BOARD_SIZE - 1) && (arr[x][j_right + 1] == arr[x][y])) j_right++;
	if (j_left == 0) block_left = 1; else block_left = arr[x][j_left - 1];
	if (j_right == BOARD_SIZE - 1) block_right = 1; else block_right = arr[x][j_right + 1];

	if ((j_right - j_left + 1 == 5) && (!block_left || !block_right))
	{
		x_begin = x; y_begin = j_left;
		return 2;
	}

	// Check diagonal
	i_above = i_below = x; j_left = j_right = y;
	while ((i_above > 0) && (j_left > 0) && (arr[i_above - 1][j_left - 1] == arr[x][y])) { i_above--; j_left--; }
	while ((i_below < BOARD_SIZE - 1) && (j_right < BOARD_SIZE - 1) && (arr[i_below + 1][j_right + 1] == arr[x][y])) { i_below++; j_right++; }
	if ((i_above == 0) || (j_left == 0)) block_above = 1; else block_above = arr[i_above - 1][j_left - 1];
	if ((i_below == BOARD_SIZE - 1) || (j_right == BOARD_SIZE - 1)) block_below = 1; else block_below = arr[i_below + 1][j_right + 1];

	if ((i_below - i_above + 1 == 5) && (!block_above || !block_below))
	{
		x_begin = i_above; y_begin = j_left;
		return 3;
	}

	// Check anti-diagonal
	i_above = i_below = x; j_left = j_right = y;
	while ((i_above > 0) && (j_right < BOARD_SIZE - 1) && (arr[i_above - 1][j_right + 1] == arr[x][y])) { i_above--; j_right++; }
	while ((i_below < BOARD_SIZE - 1) && (j_left > 0) && (arr[i_below + 1][j_left - 1] == arr[x][y])) { i_below++; j_left--; }
	if ((i_above == 0) || (j_right == BOARD_SIZE - 1)) block_above = 1; else block_above = arr[i_above - 1][j_right + 1];
	if ((i_below == BOARD_SIZE - 1) || (j_left == 0)) block_below = 1; else block_below = arr[i_below + 1][j_left - 1];

	if ((i_below - i_above + 1 == 5) && (!block_above || !block_below))
	{
		x_begin = i_above; y_begin = j_right;
		return 4;
	}
	// Not any case? => return 0
	return 0;
}

int board::getCountX()
{
	return countX;
}

int board::getCountO()
{
	return countO;
}