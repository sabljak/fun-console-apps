#include<iostream>
#include<vector>
#include<chrono>
#include<thread>
#include<fstream>
using namespace std;

vector<vector<int>> matrix;

void Print(vector<vector<int>> matrix) {
	cout << "\n";
	for (vector<int> item : matrix)
	{
		for (int var : item) {
			cout << var << " | ";
		}
		cout << "\n\n";
	}
}

bool checkValidMove(int row, int col, int val) {

#pragma region Check Row and Column
	for (size_t i = 0, j = 0; i < 9; i++, j++)
	{
		if (matrix[row][i] == val || matrix[j][col] == val) {
			return false;
		}
	}
#pragma endregion

#pragma region Check Mini Square
	int rowIndex = (row / 3) * 3;
	int colIndex = (col / 3) * 3;

	for (size_t i = rowIndex; i < rowIndex + 3; i++)
	{
		for (size_t j = colIndex; j < colIndex + 3; j++)
		{
			if (matrix[i][j] == val) {
				return false;
			}
		}
	}
#pragma endregion

	matrix[row][col] = val;
	return true;
}

bool solvePuzzle(int row, int col) {
	//return when row==9
	if (row == 9 || col == 9) return true;

	//if there's a number skip
	if (matrix[row][col] != 0) {

		if (col == 8) {
			return solvePuzzle(row + 1, 0);
		}
		else {
			return solvePuzzle(row, col + 1);
		}
	}

	//try numbers, reset to 0 if it's a dead end
	for (size_t val = 1; val < 10; val++)
	{
		if (checkValidMove(row, col, val)) {

			//uncomment for better visualisation
			//this_thread::sleep_for(100ms);
			system("CLS");
			Print(matrix);

			if (col == 8) {
				if (solvePuzzle(row + 1, 0)) return true;
			}
			else {
				if (solvePuzzle(row, col + 1)) return true;
			}
			matrix[row][col] = 0;
		}
	}
	return false;
}

int main() {

#pragma region Initialization

	vector<int> row0, row1, row2, row3, row4, row5, row6, row7, row8;
	matrix = { row0,row1,row2,row3,row4, row5, row6, row7, row8 };

	ifstream file;
	file.open("easy.txt");
	int num;
	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			file >> num;
			matrix[i].push_back(num);
		}
	}
	file.close();

#pragma endregion

#pragma region Solving

	Print(matrix);

	auto start = std::chrono::system_clock::now();
	solvePuzzle(0, 0);
	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;
	cout << "Elapsed time: " << elapsed_seconds.count() << "\n\n\n";

#pragma endregion

	return 0;
}