#include<iostream>
#include<vector>
class Sudoku{
public:
	Sudoku();
	void findAnswer();
	void setMap(vector<const int> set_map);
	int getElement[int index];
	bool correct();
	static const int sudokuSize=144;
private:
	bool checkUnity(vector<int> arr);
	vector<int> map(sudokuSize);
};

