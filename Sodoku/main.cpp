#include <chrono>
#include <iostream>
#include "Sudoku.h"

void printTable(int(&board)[LEN][LEN]);

//This function gets an input sudoku board from the user
//and sends it to the sudoku method to be solved
//it also measures the completion time
int main() {
	char line[10];
	int board[LEN][LEN];
	std::cout << "Input sudoku board:\n";
	for (int i = 0; i < LEN; i++) {
		{
			std::cin.getline(line, 10);
			for (int j = 0; j < LEN; j++)
			{
				//char to int conversion is taken from foo bahs answer on https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
				board[i][j] = line[j] - '0';
			}
		}
	}
	auto start = std::chrono::steady_clock::now();
	Sudoku s = Sudoku(board);
	bool ret = s.solve();
	if (!ret)
		std::cout << "Puzzle cannot be solved, here is the solution for the possibe part of the puzzle\n";
	else
		std::cout << "\nPuzzle solved:\n";
	printTable(board);

	auto end = std::chrono::steady_clock::now();
	auto dt = end - start;
	std::cout << "Time elapsed: " << dt.count() << " nano seconds or: " << dt.count() / (1000000.0) << " milli seconds\n";

	system("pause");
	return 0;
}

//takes a board state and prints it to the console
void printTable(int(&board)[LEN][LEN])
{
	for (int i = 0; i < LEN; i++) {
		for (int j = 0; j < LEN; j++)
		{
			std::cout << board[i][j];
		}
		std::cout << "\n";
	}
}

