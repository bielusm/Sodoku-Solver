#pragma once

const int LEN = 9;
class Sudoku
{
public:
	Sudoku(int(&board)[LEN][LEN]);
	bool solve();

	~Sudoku();
private:
	int(&board)[LEN][LEN];
	int possibilityBoard[LEN][LEN][LEN];

	int solveCell(int i, int j);
	void solveBox(int i, int j, bool(&foundNum)[LEN]);
	void solveCol(int x, int y, bool(&foundNum)[LEN]);
	void solveRow(int x, int y, bool(&foundNum)[LEN]);
	void setFalse(bool(&foundNum)[LEN]);
	bool hiddenSingle(int x, int y);
	bool checkHiddenSingles();
};

