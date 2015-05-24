#include<iostream>
#include"Sudoku.h"
main()
{
	Sudoku su;
	su.Read_In();
	su.solve();
	su.printMap();
}