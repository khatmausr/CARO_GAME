#include "common.h"

board::board()
{
	arr = new int* [BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		arr[i] = new int[BOARD_SIZE];
		for (int j = 0; j < BOARD_SIZE; j++) arr[i][j] = 0;
	}
}

board::~board()
{
	for (int i = 0; i < BOARD_SIZE; i++) delete[] arr[i];
	delete[] arr;
}

void board::resetBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			arr[i][j] = 0;
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
		return true;
	}
	return false;
}

int board::checkBoard(int x, int y) 
// Return direction of winning cells: 0 - Nothing, 1 - Vertical, 2 - Horizon, 3 - Diagonal, 4 - Anti Diagonal
{
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

	if ((i_below - i_above + 1 == 5) && (!block_above || !block_below)) return 1;

	// Check horizon
	j_left = j_right = y;
	while ((j_left > 0) && (arr[x][j_left - 1] == arr[x][y])) j_left--;
	while ((j_right < BOARD_SIZE - 1) && (arr[x][j_right + 1] == arr[x][y])) j_right++;
	if (j_left == 0) block_left = 1; else block_left = arr[x][j_left - 1];
	if (j_right == BOARD_SIZE - 1) block_right = 1; else block_right = arr[x][j_right + 1];

	if ((j_right - j_left + 1 == 5) && (!block_left || !block_right)) return 2;

	// Check diagonal
	i_above = i_below = x; j_left = j_right = y;
	while ((i_above > 0) && (j_left > 0) && (arr[i_above - 1][j_left - 1] == arr[x][y])) { i_above--; j_left--; }
	while ((i_below < BOARD_SIZE - 1) && (j_right < BOARD_SIZE - 1) && (arr[i_below + 1][j_right + 1] == arr[x][y])) { i_below++; j_right++; }
	if ((i_above == 0) || (j_left == 0)) block_above = 1; else block_above = arr[i_above - 1][j_left - 1];
	if ((i_below == BOARD_SIZE - 1) || (j_right == BOARD_SIZE - 1)) block_below = 1; else block_below = arr[i_below + 1][j_right + 1];

	if ((i_below - i_above + 1 == 5) && (!block_above || !block_below)) return 3;

	// Check anti-diagonal
	i_above = i_below = x; j_left = j_right = y;
	while ((i_above > 0) && (j_right < BOARD_SIZE - 1) && (arr[i_above - 1][j_right + 1] == arr[x][y])) { i_above--; j_right++; }
	while ((i_below < BOARD_SIZE - 1) && (j_left > 0) && (arr[i_below + 1][j_left - 1] == arr[x][y])) { i_below++; j_left--; }
	if ((i_above == 0) || (j_right == BOARD_SIZE - 1)) block_above = 1; else block_above = arr[i_above - 1][j_right + 1];
	if ((i_below == BOARD_SIZE - 1) || (j_left == 0)) block_below = 1; else block_below = arr[i_below + 1][j_left - 1];

	if ((i_below - i_above + 1 == 5) && (!block_above || !block_below)) return 4;

	// Not any case? => return 0
	return 0;
}
