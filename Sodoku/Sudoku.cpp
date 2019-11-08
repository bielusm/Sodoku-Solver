#include "Sudoku.h"
#include <iostream>

Sudoku::Sudoku(int(&board)[LEN][LEN])
	:board(board)
{
}
Sudoku::~Sudoku()
{
}

//This solve follows a two step process
//First every cell is checked to see if only one number possible
//it crosses off all numbers that are in the same row, colum and square
//if there is not only one solution for the cell it is skipped and all the possible solutions are recorded in possibilityBoard (if the cell is completed it is also skipped)
//upon skipping every number on the board without a cell filled we must try step 2
//step 2 uses a method known as hidden singes to solve further cells
//https://www.learn-sudoku.com/hidden-singles.html
//upon completion of hidden singles we go back to step 1 until the puzzle is solved or until hidden singles is nessicary again
//if hidden singles cannot find any cells, the method returns false
//more complex strategies could be implemented but currently only elimination and hidden singles is implemented
bool Sudoku::solve() {
	bool unsolved = true;
	bool cantSolve = false;
	int lastSolve = 0;
	for (int i = 0; i < LEN; i++)
		for (int j = 0; j < LEN; j++)
		{
			if (board[i][j] == 0) {
				possibilityBoard[i][j][0] = 0;
			}
			else
				possibilityBoard[i][j][0] = -1;
		}

	while (unsolved && !cantSolve) {
		bool skipped = false;
		for (int i = 0; i < LEN; i++) {
			{
				for (int j = 0; j < LEN; j++)
				{
					if (possibilityBoard[i][j][0] != -1) {
						int ret = solveCell(i, j);
						if (ret == -1)
							skipped = true;
						else
							lastSolve = 0;
					}
				}
				lastSolve++;
			}
		}
		if (lastSolve > LEN*LEN)
		{
			if (!checkHiddenSingles())
				unsolved = false;
			else
				cantSolve = true;
		}
		if (!skipped) {
			unsolved = false;
		}
	}
	return (!cantSolve);

}

//takes a Sudoku cell that has not been solved and uses elimentation 
int Sudoku::solveCell(int x, int y)
{
	bool foundNum[LEN];
	int amtEmpty = 0;
	int emptyIndex;
	setFalse(foundNum);
	solveBox(x, y, foundNum);
	solveCol(x, y, foundNum);
	solveRow(x, y, foundNum);

	for (int i = 0; i < LEN; i++) {
		if (foundNum[i] == false)
		{
			amtEmpty++;
			emptyIndex = i + 1;
		}
	}
	if (amtEmpty == 1)
	{
		board[x][y] = emptyIndex;
		possibilityBoard[x][y][0] = -1;
		return 0;
	}
	else
	{
		for (int i = 0; i < LEN; i++)
		{
			possibilityBoard[x][y][i] = foundNum[i];
		}
		return -1;
	}
}

//elimination on a collum 
void Sudoku::solveCol(int x, int y, bool(&foundNum)[LEN]) {
	int currNum = 0;
	for (int i = 0; i < LEN; i++) {
		currNum = board[x][i];
		if (currNum != 0)
			foundNum[currNum - 1] = true;
	}
}

//elimination on a row
void Sudoku::solveRow(int x, int y, bool(&foundNum)[LEN]) {
	int currNum = 0;
	for (int i = 0; i < LEN; i++) {
		currNum = board[i][y];
		if (currNum != 0)
			foundNum[currNum - 1] = true;
	}
}

//elimination on a box
void Sudoku::solveBox(int x, int y, bool(&foundNum)[LEN])
{
	int currNum = 0;

	int xOffset = x / 3;
	int yOffset = y / 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			currNum = board[xOffset * 3 + i][yOffset * 3 + j];
			if (currNum != 0)
				foundNum[currNum - 1] = true;

		}
	}
}

//checks the hidden single method
//https://www.learn-sudoku.com/hidden-singles.html
bool Sudoku::checkHiddenSingles()
{
	bool foundOne = false;
	for (int i = 0; i < LEN; i++)
	{
		for (int j = 0; j < LEN; j++)
		{
			if (possibilityBoard[i][j][0] != -1) {
				if (hiddenSingle(i, j))
					foundOne = true;
			}
		}
	}
	return foundOne;
}

//checks hidden single for specific cell
bool Sudoku::hiddenSingle(int x, int y)
{
	int notFound[LEN];
	for (int i = 0; i < LEN; i++)
		notFound[i] = possibilityBoard[x][y][i];

	int currPos;
	for (int i = 0; i < LEN; i++) {
		if (possibilityBoard[x][i][0] == -1)
			continue;
		for (int j = 0; j < LEN; j++)
		{

			currPos = possibilityBoard[x][i][j];
			if (currPos > 0)
				notFound[j] = -1;
		}
	}
	for (int i = 0; i < LEN; i++) {
		if (possibilityBoard[i][y][0] == -1)
			continue;

		for (int j = 0; j < LEN; j++)
		{
			currPos = possibilityBoard[i][y][j];
			if (currPos > 0)
				notFound[j] = -1;
		}
	}

	int xOffset = x / 3;
	int yOffset = y / 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			if (possibilityBoard[xOffset * 3 + i][yOffset * 3 + j][0] == -1)
				continue;
			for (int k = 0; k < LEN; k++)
			{
				currPos = possibilityBoard[xOffset * 3 + i][yOffset * 3 + j][k];
				if (currPos > 0)
					notFound[j] = -1;
			}

		}
	}
	for (int i = 0; i < LEN; i++)
	{
		if (notFound[i] == 0)
		{
			board[x][y] = i + 1;
			return true;
		}
	}
	return false;

}

void Sudoku::setFalse(bool(&foundNum)[LEN])
{
	for (int i = 0; i < LEN; i++)
	{
		foundNum[i] = false;
	}
}


