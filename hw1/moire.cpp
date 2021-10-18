#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

int main(int argc, char *argv[]){


	if(argc != 5){ //if more or less than 4 args
		cerr << "Not correct number of parameters, try again loser." << endl;
		return -1;
	}

	string pattern = argv[1]; //declaring args as vars
	string h = argv[2];
	string shape = argv[3];
	string fileTxt = argv[4];
	ofstream file(fileTxt);

	int heightT = atoi(h.c_str()); //height to int


	//check for correct inputs
	if(shape != "square" && shape != "right_triangle" && shape != "isosceles_triangle" && shape != "diamond"){
		cerr << "Shape not typed incorrectly or not supported by program, try again loser." << endl;
		return -1;
	}
	if(heightT <= 0){
		cerr << "Height input not supported by program, try again loser" << endl;
		return -1;
	}
	if(fileTxt.substr(fileTxt.size() - 4) != ".txt"){
		cerr << "Target output file is not a .txt, try again loser." << endl;
		return -1;
	}


	unsigned int height = heightT; //changed to unsigned to prevent warnings


	if(file.fail()){
		cerr << "Failed to open file" << endl;
		return -1;
	}


	if(shape == "square"){
		unsigned int start = 0;		//create starting point for pattern
		for(unsigned int x = 0; x < height; x++){
			if(x == 0 || x == height-1){	//if first or last row, line of stars
				string temp(height,'*');
				file << temp << endl;
			}
			else{
				file << "*";
				string sub = pattern.substr(start);		//creates string from specified start point
				unsigned int size = sub.size();
				unsigned int leftOver = (height-2) - sub.size();	//leftover space in row
				unsigned int more = leftOver;	//needed as placeholder
				file << sub;
				do{
					more = (height-2) - size;	//space left
					sub = pattern.substr(0,more);	//creates new substring from start
					file << sub;
					size += sub.size();		//new size because of added substring
				} while(more > pattern.size());		//if space between stars not completely filled
				file << "*" << endl;
				start = more;	//next startpoint is where last substring ended
			}
		}
	}
	
	if(shape == "right_triangle"){
		unsigned int start = 0;
		unsigned int counter; //counter made to keep place in string while start changes
		for(unsigned int x = 0; x < height; x++){
			if(x == 0){		//first line is one star
				file << "*" << endl;
			}
			else if(x == 1){	//second line is two stars
				file << "**" << endl;
			}
			else if(x == height-1){		//last line is row of stars
				string temp(height,'*');
				file << temp << endl;
			}
			else{
				file << "*";
				string sub = pattern.substr(start,x-1);		
				unsigned int size = sub.size();
				unsigned int leftOver = (x-1) - sub.size();
				unsigned int more = leftOver;
				file << sub;
				while(size <= x-2){
					more = (x-1) - size;
					sub = pattern.substr(0,more);
					file << sub;
					size += sub.size();
					start = more;
				}
				file << "*" << endl;
				counter += size;	
				start = counter;
				while(start >= pattern.size()){ //reset start to end point of pattern by subracting pattern size, fixes errors
					start -= pattern.size();
				}
			}
		}
	}

	if(shape == "isosceles_triangle"){
		int start = 0;
		int counter = 0;
		for(unsigned int x = 0; x < height*2; x+=2){ //*2 for base size, +=2 for both sides of triangle
			if(x == 0){
				string space(height-1,' '); //creates space based on height
				file << space << "*" << endl;
			}
			else if(x == height*2-2){ //final row of stars
				string temp(height*2-1,'*');
				file << temp << endl;
			}
			else{
				string newSpace(height-(x+2)/2,' '); //creates spaces before line
				file << newSpace << "*";
				string sub = pattern.substr(start,x-1); //substring from starting point x-1
				int size = sub.size(); 
				int leftOver = (x-1) - sub.size(); //reference right traingle comments for the rest
				int more = leftOver;
				file << sub;
				while(size <= x-2){
					more = (x-1) - size;
					sub = pattern.substr(0,more);
					file << sub;
					size += sub.size();
					start = more;
				}
				file << "*" << endl;
				counter += size;	
				start = counter;
				while(start >= pattern.size()){
					start -= pattern.size();
				}
			}
		}
	}

	if(shape == "diamond"){ //isosceles triangle on top of flipped isosceles triangle forms a diamond
		int start = 0;
		int counter = 0;
		for(unsigned int x = 0; x < height*2; x+=2){
			if(x == 0){
				string space(height-1,' ');
				file << space << "*" << endl;
			}
			else{
				string newSpace(height-(x+2)/2,' ');
				file << newSpace << "*";
				string sub = pattern.substr(start,x-1);
				int size = sub.size(); 
				int leftOver = (x-1) - sub.size();
				int more = leftOver;
				file << sub;
				while(size <= x-2){
					more = (x-1) - size;
					sub = pattern.substr(0,more);
					file << sub;
					size += sub.size();
					start = more;
				}
				file << "*" << endl;
				counter += size;	
				start = counter;
				while(start >= pattern.size()){
					start -= pattern.size();
				}
			}
		}
		for(unsigned int x = height*2-2; x >= 0; x-=2){
			if(x == 0){
				string space(height-1,' ');
				file << space << "*" << endl;
				return 0;
			}
			else{
				string newSpace(height-(x+2)/2,' ');
				file << newSpace << "*";
				string sub = pattern.substr(start,x-1);
				int size = sub.size(); 
				int leftOver = (x-1) - sub.size();
				int more = leftOver;
				file << sub;
				while(size <= x-2){
					more = (x-1) - size;
					sub = pattern.substr(0,more);
					file << sub;
					size += sub.size();
					start = more;
				}
				file << "*" << endl;
				counter += size;	
				start = counter;
				while(start >= pattern.size()){
					start -= pattern.size();
				}
			}
		}
	}
	return 0;
}