#include"Sudoku.h"
using namespace std;
Sudoku::Sudoku(){
	map = new int[sudokuSize];
	giveMap = new int[sudokuSize];
	countcol = new vector<int>(9,0);
	countrow = new vector<int>(9);
	countcel = new vector<int>(9);
	randNum = new vector<int>(9);
	saverow = new vector<vector<int> >(12);
	savecol = new vector<vector<int> >(12);
	savecel = new vector<vector<int> >(16);
	
}
void Sudoku::solve()
{
	give();
}	
bool Sudoku::give(){
	scanPossibility();
	bool can = false;
	for(int i = 1;i < 10;i++)//judge if there is any possibility exist.
		if(possible[i].size() > 0)
			can = true;
	if(!can)
	{
		if(isCorrect())//answer is right.
		{
			cout<<"there is at least one answer."<<endl;
			return true;
		}
		else
		{
			cout<<"no answer."<<endl;//no awnser.
			return false;
		}
	}
	for(int i=1;i<=9;i++){
		if(i == 1 && possible[1].size() != 0)//if there is only one possibility.
		{
			for(int j = 0;j < possible[1].size();j++)
			{
				map[possible[1][j]->position] = possible[1][j]->possibility[0];//store the possibility into the position.
			}
			give();//recursive
			return true;
		}
		else if(possible[i].size()!=0){//over one possibility
			for(int j=0;j<possible[i].size();j++){
				for(int k = 0;k < possible[i][j]->possibility.size();k++)
				{
					int a = map[possible[i][j]->position];
					map[possible[i][j]->position] = possible[i][j]->possibility[k];	//try the possibilities of the position.
					if(give())
					{
						return true;
					}
					map[a] = 0;
					scanPossibility();
				}
			}
		}
	}
}	

void Sudoku::printMap(){//cout a map.
	for(int i=0;i<sudokuSize;i++){
		cout<<" "<<map[i]<<" ";
		if(i%12==11)
			cout<<endl;
	}
}
void Sudoku::scanPossibility()//Find how many possibility does the position have ,and store the possibilities and position.
{
	for(int i=0;i<12;i++) {
		for(int j=0;j<12;j++)//column has which numbers
		{
			if(map[i+12*j]!=-1&&map[i+12*j]!=0)
				(*countcol)[map[i+12*j]-1]+=1;
		}
		(*savecol)[i]=(*countcol);
		(*countcol).clear();
		for(int i = 0;i < 9;i++)
			(*countcol).push_back(0);//reset the countcol
	}
	for(int i=0;i<144;i+=12) {
		for(int j=0;j<12;j++)//row has which numbers.
		{
			if(map[i+j]!=-1&&map[i+j]!=0)
				(*countrow)[map[i+j]-1]+=1;
		}
		(*saverow)[i/12]=(*countrow);
		(*countrow).clear();
		for(int i = 0;i < 9;i++)
			(*countrow).push_back(0);//reset the countrow
	}
	for(int i=0;i<16;i++){ 
		for(int j=0;j<9;j++)//cell has which numbers.
		{	
			location=12*(j/3)+(j%3)+36*(i/4)+3*(i%4);
			if(map[location!=-1]&&map[location!=0])
				++(*countcel)[map[location]-1];	
		}
		(*savecel)[i]=(*countcel);
		(*countcel).clear();
		for(int i = 0;i < 9;i++)
			(*countcel).push_back(0);//reset the countcel
	}
	for(int i = 0;i <= 9;i++)
		possible[i].clear();
	for(int i=0;i<144;i+=12){//scan possibility and store possibilities and positions.
		for(int j=0;j<12;j++){
			if(map[i+j]==0){
				(*countrow)=(*saverow)[i/12];
				(*countcel)=(*savecel)[(((i+j)%12)/3+4*(i/36))];		
				(*countcol)=(*savecol)[j];
				int x=0;
				doublepos* doublep = new doublepos;
				doublep->position = i+j;
				for(int k=0;k<9;k++){
					if((*countrow)[k]+(*countcel)[k]+(*countcol)[k]==0){
						doublep->possibility.push_back(k+1);
						x++;
					}			
				}
				if(x > 0)
					possible[x].push_back(doublep);				//How many possibility does the position has.
			}
		}
	}
	(*countcol).clear();
	(*countcel).clear();
	(*countrow).clear();
}

void Sudoku::setMap(vector<int>set_map)//put the file into map.
{
	for(int i=0; i<sudokuSize; ++i)
	map[i] = set_map[i];
}
bool Sudoku:: isCorrect()// if the final answer is correct.
{
	bool* num = new bool[10];
	for(int i = 0;i < 12;i++)
	{
		for(int j = 0;j < 10;j++)
		num[j] = false;
		for(int j = 0;j < 12;j++)
		{
			if(map[i*12+j] != -1){
				if(map[i*12+j] == 0)
					return false;
				else if(map[i*12+j] > 0&& num[map[i*12+j]]==false)
				{
					num[map[i*12+j]] = true;
				}
				else if(num[map[i*12+j]] == true)
					return false;
			}
			
		}
	}
	for(int i = 0;i < 12;i++)
	{
		for(int j = 0;j < 10;j++)
		num[j] = false;
		for(int j = 0;j < 12;j++)
		{	
			if(map[i+j*12] != -1){
				if(map[i+j*12] == 0)
					return false;
				else if(map[i+j*12] > 0&& num[map[i+j*12]]==false)
				{
					num[map[i+j*12]] = true;
				}
				else if(num[map[i+j*12]] == true)
					return false;
			}
		}
	}
	for(int i=0;i<16;i++){ 
		for(int j = 0;j < 10;j++)
		num[j] = false;
		for(int j=0;j<9;j++)//cell has which numbers.
		{	
			int location;
			location=12*(j/3)+(j%3)+36*(i/4)+3*(i%4);
			if(map[location] != -1){
				if(map[location] == 0)
					return false;
				else if(map[location] > 0&& num[map[location]]==false)
				{
					num[map[location]] = true;
				}
				else if(num[map[location]] == true)
					return false;
			}
		}
	return true;
	}
}
void Sudoku:: giveQuestion()
{
	int a,b,c,e,f,g,h,i,j;
	int d=0;
	
	srand ( time(0)  );
	for(int i=0;i<9;i++)
	{
		(*randNum)[i]=d+1;
		d++;
	}
	
	random_shuffle((*randNum).begin(),(*randNum).end());
	for(int i=0;i<9;i++){
		cout<<(*randNum)[i]<<endl;
		}
	a=(*randNum)[0];
	b=(*randNum)[1];
	c=(*randNum)[2];
	e=(*randNum)[3];
	f=(*randNum)[4];
	g=(*randNum)[5];
	h=(*randNum)[6];
	i=(*randNum)[7];
	j=(*randNum)[8];
	int giveMap[]={b,c,a,-1,-1,-1,i,j,h,g,e,f,
			f,g,e,-1,-1,-1,b,c,a,i,j,h,
			j,i,h,-1,-1,-1,f,g,e,b,c,a,
			e,f,g,a,b,c,-1,-1,-1,h,i,j,
			h,j,i,e,f,g,-1,-1,-1,a,b,c,
			a,b,c,h,i,j,-1,-1,-1,e,f,g,
			-1,-1,-1,b,c,a,g,e,f,j,h,i,
			-1,-1,-1,f,g,e,j,h,i,c,a,b,
			-1,-1,-1,i,j,h,c,a,b,f,g,e,
			i,h,j,c,a,b,e,f,g,-1,-1,-1,
			c,a,b,g,e,f,h,i,j,-1,-1,-1,
			g,e,f,j,h,i,a,b,c,-1,-1,-1};
	for(int i=0;i<27;i++)
	{
	int k;
	k=rand()%144;
	if(giveMap[k]!=-1)
	giveMap[k]=0;
	}
	
	ofstream giveQuestion("map.txt",ios::out);
	if(!giveQuestion)
	{
		cerr<<"Failed opening.";
		exit(1);
	}
	for(int i=0;i<sudokuSize;i++)
	{
		giveQuestion<<" "<<giveMap[i];
	}
}
void Sudoku:: Read_In(){
	vector<int>sudoku_in(Sudoku::sudokuSize);
	ifstream in("map.txt",ios::in);
	if(!in)
	{
		cerr<<"Failed opening";
		exit(1);
	}
	else{
		for(int i = 0;i < Sudoku::sudokuSize;i++)
		{
			int a;
			in >> a;
			sudoku_in[i] = a;
		}
		setMap(sudoku_in);
		cout << endl;
	}
}
