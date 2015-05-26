#include<iostream>
#include<vector>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<algorithm>
#include<ctime>
using namespace std;
struct doublepos{
	int position;
	vector<int> possibility;
};
class Sudoku{
public:
	Sudoku();
	void solve();
	void setMap(vector<int> set_map);
	void scanPossibility();
	void printMap();
	void giveQuestion();
	void Read_In();
	bool isCorrect();
	bool give();
	static const int sudokuSize=144;
	int* map;
	int* giveMap;
private:
	bool checkUnity(vector<int> arr);
	
	vector<int>* countrow;
	vector<int>* countcol;
	vector<int>* countcel;
	vector<vector<int> >* saverow;
	vector<vector<int> >* savecol;
	vector<vector<int> >* savecel;
	vector<doublepos*> possible[10];
	vector<int>* randNum;
	int location;
};