#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <array>

using namespace std;

class Board{

public:
	Board(const string& _t1, const string& _t2, const string& _blank);

	int numRows() const { return mRow; }
	int numColumns() const { return mCol; }
	int numTokensInRow(int rowNum) const; 		//-1 if doesn't exist
	int numTokensInColumn(int colNum) const; 	//^

	void setArr();

	string insert(int colNum, bool player1); 	//inserts specified token
	bool checkConnectFour(int colNum, int rowNum, string t) const;

	void addPiece(int c, int r, string t);
	void clear();
	void copy(const Board& old);

	Board(const Board& old);
	void operator=(const Board& old);

	friend ostream& operator<<(ostream &os, const Board &b);

~Board(){clearMem();}
	void clearMem();

private:
	int mRow;
	int mCol;
	string** arr;	//contains board
	string t1;
	string t2;
	string blank;
	int* size; 		//keeps size of arrays

};


inline ostream& operator<<(ostream &os, const Board &b)
{
	for(int x = b.mRow-1; x >= 0; x--){
		for(int y = 0; y < b.mCol; y++){
			if(x > b.size[y]-1){			//if specified row index is greater than
				os << b.blank;				//column size then return a blank
			}
			else{
				os << b.arr[y][x];			//otherwise return token at specified board location
			}

			if(y != b.mCol-1){ 				//don't print the space if last one in loop
				os << " ";
			}
		}
		os << endl;
	}
	return os;
}