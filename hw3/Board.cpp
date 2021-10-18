#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <array>
#include <iterator>

#include "Board.h"

using namespace std;

Board::Board(const string& _t1, const string& _t2, const string& _blank){
	t1 = _t1;
	t2 = _t2;
	blank = _blank;
	mRow = 5;
	mCol = 4;
	arr = new string*[mCol];
	size = new int[mCol];
	for(int x = 0; x < mCol; x++) //initalizing the sizes as 0s
		size[x] = 0;

	for(int i = 0; i < mCol; i++) //initializing column array pointers as NULLs
		arr[i] = NULL;
}

bool Board::checkConnectFour(int colNum, int rowNum, string t) const{
	bool connectFour = false;													//r and c == 0, min  --  mRow-1 and mCol-1, max
	if(rowNum >= 3){		//checks 3 below piece recently placed
		if(arr[colNum][rowNum-1] == t && arr[colNum][rowNum-2] == t && arr[colNum][rowNum-3] == t){
			connectFour = true;
		}
	}
	if(colNum <= mCol-4){	//checks 3 to right of piece recently placed
		if(size[colNum+3] > rowNum && size[colNum+2] > rowNum && size[colNum+1] > rowNum){ 		//makes sure that the column contains #rowNum tokens
			if(arr[colNum+1][rowNum] == t && arr[colNum+2][rowNum] == t && arr[colNum+3][rowNum] == t){		//checks
				connectFour = true;
			}
		}
	}
	if(colNum >= 3){		//checks 3 to left of piece recently placed
		if(size[colNum-3] > rowNum && size[colNum-2] > rowNum && size[colNum-1] > rowNum){		//same thing
			if(arr[colNum-1][rowNum] == t && arr[colNum-2][rowNum] == t && arr[colNum-3][rowNum] == t){		//checks
				connectFour = true;
			}
		}
	}
	return connectFour;
}

string Board::insert(int colNum, bool player1){
	
	string token; 						//token to be placed
	bool row0 = false; 					//if row where piece needs to be placed is 0

	if(player1){						//assigns [string token] to correct token:(t1 or t2)
		token = t1;
	}
	else{
		token = t2;
	}

	
	if(colNum > mCol-1){				//if column index inputted is larger than current column index
		addPiece(colNum, 0, token);		//adds token
		row0 = true;					//to row 0
	}
	else if(arr[colNum] == NULL){		//if column currently contains 0 tokens
		addPiece(colNum, 0, token);
		row0 = true;
	}
	else{
		addPiece(colNum, size[colNum], token);	//otherwise column already contains tokens, so add piece to the top
	}

	if(row0){							
		if(checkConnectFour(colNum, 0, token)){	//check for connect four around piece most recently inserted
			return token;						//returns token if connect four is found
		}
	}
	else{
		if(checkConnectFour(colNum, size[colNum]-1, token)){ // ^
			return token;
		}
	}

	return blank; //if connect four is not found return the blank
}

int Board::numTokensInRow(int rowNum) const{
	int counter = 0;

	if(rowNum > mRow-1){						//if row index inputted is larger than current largest row index
		return -1;
	}

	for(int x = 0; x < mCol; x++){				//for loop through columns
		if(arr[x] == NULL){						//if column contains no tokens
			continue;							//continue
		}
		if(size[x]-1 < rowNum){					//if size of array that column points to is less than the row index
			continue;							//continue
		}
		if(arr[x][rowNum] == t1 || arr[x][rowNum] == t2){	//add to counter if token is contained in specified location
			counter++;
		}
	}
	return counter;								//return the amount counted
}

int Board::numTokensInColumn(int colNum) const{
	int counter = 0;

	if(colNum > mCol-1){						//if col index inputted is larger than the current largest col index
		return -1;
	}


	for(int x = 0; x < size[colNum]; x++){						//for loop through sizes of columns
		if(arr[colNum] != NULL){								//if specified column is not empty
			if(arr[colNum][x] == t1 || arr[colNum][x] == t2){	//and specified column contains a token
				counter++;										//add to counter
			}
		}
		else
			break;	//if specified column is empty then break
	}
	return counter;	//return amount counted
}

void Board::addPiece(int c, int r, string t){ 	//column, row, token
	if(c+1 > mCol){								//if column index inputted is larger than the max column index
		string** tempArr = new string*[mCol]; 	//copy of current board
		for(int i = 0; i < mCol; i++){			//for loop of old # columns
			tempArr[i] = new string[size[i]];	//initializing all column pointers to rows
			for(int j = 0; j < size[i]; j++){	//foor loop of old column sizes
				tempArr[i][j] = arr[i][j];		//copying
			}
			delete[] arr[i];					//deleting board at column after it has been copied
		}
		delete[] arr;							//deleting board

		arr = new string*[c+1];					//creating new board of specified size inputted
		for(int i = 0; i < mCol; i++){
			if(size[i] == 0)					//column pointer = NULL if specified column size is 0
				arr[i] = NULL;
			else
				arr[i] = new string[size[i]];	//initializing all column pointers to existing column sizes
			for(int j = 0; j < size[i]; j++){
				arr[i][j] = tempArr[i][j];		//copying back into real board
			}
			delete[] tempArr[i];				//deletes temp board at column after being coppied
		}
		delete[] tempArr;						//deleting temp board

		for(int i = mCol; i < c; i++){			//if the new index column is more than 1 bigger than
			arr[i] = NULL;						//previous max column, this loop will fill in the column pointers
		}										//in between old max and new max with NULL
		arr[c] = new string[r+1];		//specified column points to a new string of size 1
		arr[c][r] = t;					//and token is inserted

		int* tempSize;
		tempSize = new int[mCol];
		for(int x = 0; x < mCol; x++){
			tempSize[x] = size[x];				//copy of size array
		}

		delete[] size;
		size = new int[c+1];					//size array changed to new # of columns

		for(int x = 0; x < c; x++){				//for loop of size new column index
			if(x > mCol-1){						//if x > old max column
				size[x] = 0;					//fill in with 0 because column pointer at that index is NULL
				continue;						//and continue
			}
			size[x] = tempSize[x];				//otherwise re-copy into size
		}
		size[c] = 1;							//inputted column is now size 1

		delete[] tempSize;						//delete copy
		mCol = c+1;								//change max column to the new max
	}

	else if(r == 0){						//if inputted row is 0
		arr[c] = new string[r+1];			//column pointer points to new string size 1
		arr[c][r] = t;						//insert token
		size[c]++;							//column size increased by 1
	}
	else{									//if column already has tokens in it
		string* tempArr2;
		tempArr2 = new string[size[c]];
		for(int i = 0; i < size[c]; i++){
			tempArr2[i] = arr[c][i];		//copy of column contents
		}

		delete[] arr[c];					//delete the old column
		arr[c] = new string[r+1];			//new column of size inputted row+1

		for(int j = 0; j < size[c]; j++){
			arr[c][j] = tempArr2[j];		//copy back
		}

		delete[] tempArr2;					//delete copy

		if(r+1 > mRow){						//if row is greater than the max
			mRow = r+1;						//old max = new max
		}

		arr[c][r] = t;						//put token at board in new spot
		size[c]++;							//add to column size
	}
}

void Board::clear(){				//clears board back to beginning status
	for(int x = 0; x < mCol; x++){	//4x5 with empty board and column sizes = 0
		delete[] arr[x];			//and NULL pointers
	}
	delete[] arr;
	delete[] size;

	mRow = 5;
	mCol = 4;
	arr = new string*[mCol];
	size = new int[4];
	for(int x = 0; x < 4; x++)
		size[x] = 0;

	for(int i = 0; i < mCol; i++)
		arr[i] = NULL;
}

void Board::clearMem(){
	for(int x = 0; x < mCol; x++){
			delete[] arr[x];
	}
	delete[] arr;
	delete[] size;
}

void Board::copy(const Board& old){
	mRow = old.mRow;					//copy over aspects of old board
	mCol = old.mCol;
	t1 = old.t1;
	t2 = old.t2;
	blank = old.blank;

	size = new int[mCol];				//copy over old column sizes
	for(int x = 0; x < mCol; x++)
		size[x] = old.size[x];

	arr = new string*[mCol];			//copy over old column pointers
	for(int x = 0; x < mCol; x++){
		if(size[x] == 0)				//if column size is 0
			arr[x] = NULL;				//column points to NULL
		else
			arr[x] = new string[size[x]];	//otherwise = new string of size[column size]
	}

	for(int i = 0; i < mCol; i++){
		for(int j = 0; j < size[i]; j++){
			arr[i][j] = old.arr[i][j];		//copying over old board
		}
	}
}

Board::Board(const Board& old){
	copy(old);
}

void Board::operator=(const Board& old){
	clearMem();		//clear memory to make copy function work
	copy(old);
}