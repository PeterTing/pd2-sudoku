#include"Sudoku.h"
#include<fstream>
#include<iomanip>
#include<cstdlib>
using namespace std;

void Sudoku::findAnswer()
{
	vector<int>countrow(9);
	vector<int>countcol(9);
	vector<int>countcel(9);
	vector<countrow>saverow(12);
	vector<countcol>savecol(12);
	vector<countcel>savecel(16);
	vector<int>numbers;
	vector<int>possible[9];

	int location;
	ifstream infile("sudoku")
	if(!infile){
		cerr<<"Failed opening."<<endl;
		exit(1);
	}
	for(int i=0;i<sudokuSize;i++)
	{
		sudoku>>map.at(i);
	}
	for(int i=0;i<sudokuSize;i++){//test
		cout<<map.at(i)<<setw(8);
		if(i%12==11)
		cout<<endl;
	}
	for(int i=0;i<12;i++) {
		for(int j=0;j<12;j++)//column has which numbers
		{
			if(map[i+12*j]!=-1&&map[i+12*j]!=0)
				++countcol[map[i+12*j]-1];
		}
		savecol[i]=countcol;
		countcol.clear();//not sure
	}
	for(int i=0;i<144;i+=12) {
		for(int j=0;j<12;j++)//row has which numbers.
		{
			if(map[i+j]!=-1&&map[i+j]!=0)
				++countrow[map[i+j]-1];
		}
		saverow[i]=countrow;
		countrow.clear();//not sure
	}
	for(int i=0;i<16;i++){ 
		for(int j=i;j<9;j++)//cell has which numbers.
		{	
			location=12*(j/3)+(j%3)+36*(i/4)+3*(i%4);
			if(map[location!=-1]&&map[location!=0])
				++countcel[map[location]-1];	
		}	 
		savecel[i]=countcel;
		countcel.clear();//not sure
	}
	for(int i=0;i<144;i+=12){//scan possibility
		for(int j=0;j<12;j++){
			if(map[i+j]==0){
				countrow=saverow[i/12];
				countcel=savecel[(((i+j)%12)/3+4*(i/36))];		
				countcol=savecol[j];
				for(int k=0;k<9;k++0){
					int x=0;
					if(countrow(k)+countcel(k)+countcol(k)==0)
						x++;
					possible[x].push_back(i+j);					
				}							
			}
		}
	}
	for(int i=0;i<9;i++){
		if(possible[i].size()!=0){
			for(int j=0;j<possible[i].size();i++){
				int x,y;
				x=possible[i][j]-possible[i][j]%12;
				y=possible[i][j]%12;
					
			}
		}		
		
	}
	
}	
	
bool checkUnity(vector<int> arr(12))
{
	vector<int> arr_check(12);
	int location;
	for(int i=0;i<12;i++){
		if(arr(i)!=-1)
			++arr_check(arr(i)-1);
		if(arr(i)==-1)
			arr_check(10)=arr_check(11)=arr_check(12)=1;
	}
	for(int i=0;i<12;i++)
	{
		if(arr_check(arr(i)-1)!=1)
			return false;
		else
			return true;
	}
}
