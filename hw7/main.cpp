#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <functional>

#include "fighter.h"

//You may add additional typedefs, includes, etc. up here

//This is the only array you are allowed to have in your program.
const std::string move_names[7] = {"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash", "down-smash"};

//Feel free to put forward declarations here




std::string q(std::string name, std::string move, std::set<Fighter> fighters){
	std::string ret;

	std::set<Fighter>::const_iterator x;
	for(x = fighters.begin(); x != fighters.end(); x++){	//for loop finds which fighter is the
		if((*x).getName() == name){							//target and prints out respective moves
			if(move != "all"){
				ret += name + " " + move + ": ";
				ret += std::to_string((*x).getMoveTimes()[move]) + "\n";
			}
			else{
				ret += name + " " + move_names[6] + ": " + std::to_string((*x).getMoveTimes()[move_names[6]]) + "\n";
				ret += name + " " + move_names[3] + ": " + std::to_string((*x).getMoveTimes()[move_names[3]]) + "\n";
				ret += name + " " + move_names[4] + ": " + std::to_string((*x).getMoveTimes()[move_names[4]]) + "\n";
				ret += name + " " + move_names[1] + ": " + std::to_string((*x).getMoveTimes()[move_names[1]]) + "\n";
				ret += name + " " + move_names[0] + ": " + std::to_string((*x).getMoveTimes()[move_names[0]]) + "\n";
				ret += name + " " + move_names[5] + ": " + std::to_string((*x).getMoveTimes()[move_names[5]]) + "\n";
				ret += name + " " + move_names[2] + ": " + std::to_string((*x).getMoveTimes()[move_names[2]]) + "\n";
			}	//^to print in alphabetical order
		}
	}

	ret += "\n";
	return ret;
}

std::string f(std::string move, int limit, std::set<Fighter> fighters){

	std::string ret;
	ret += "-f " + move + " " + std::to_string(limit) + "\n";
	std::map<std::string, int> moveTime;

	std::set<Fighter>::const_iterator x;
	for(x = fighters.begin(); x != fighters.end(); x++){
		moveTime[(*x).getName()] = (*x).getMoveTimes()[move];
	}


	//I googled how to sort a map by the second value, hence
	//the Comparator typedef


	typedef std::function<bool(std::pair<std::string, int>, std::pair<std::string, int>)> Comparator;
 
	//lambda function to compare two pairs by the second value
	Comparator compFunctor =
		[](std::pair<std::string, int> a ,std::pair<std::string, int> b)
		{
			if(a.second == b.second)
				return a.first < b.first;
			return a.second < b.second;
		};
 
	//set will store the pairs in the sorted order
	std::set<std::pair<std::string, int>, Comparator> sortedTimes(
			moveTime.begin(), moveTime.end(), compFunctor);
 
 	//also used google for the following for loop
	int i = 0;
	for (std::pair<std::string, int> element : sortedTimes){
		//adds each element in order to the return string
		if(i >= limit)
			break;
		ret += element.first  + " " + std::to_string(element.second) + "\n";
		i++;
	}

	ret += "\n";
	return ret;
}

std::string s(std::string move, int limit, std::set<Fighter> fighters){

	std::string ret;
	ret += "-s " + move + " " + std::to_string(limit) + "\n"; 
	std::map<std::string, int> moveTime;

	std::set<Fighter>::const_iterator x;
	for(x = fighters.begin(); x != fighters.end(); x++){
		moveTime[(*x).getName()] = (*x).getMoveTimes()[move];
	}

	//Same thing as function f but with the sort 
	//function changed to sort by greatest number

	typedef std::function<bool(std::pair<std::string, int>, std::pair<std::string, int>)> Comparator;
 
	Comparator compFunctor =
		[](std::pair<std::string, int> a ,std::pair<std::string, int> b)
		{
			if(a.second == b.second)
				return a.first < b.first;
			return a.second > b.second;
		};
 
	std::set<std::pair<std::string, int>, Comparator> sortedTimes(
			moveTime.begin(), moveTime.end(), compFunctor);
 
	int i = 0;
	for (std::pair<std::string, int> element : sortedTimes){
		if(i >= limit)
			break;
		ret += element.first  + " " + std::to_string(element.second) + "\n";
		i++;
	}

	ret += "\n";
	return ret;
}

std::string d(std::string move, int start, std::set<Fighter> fighters){
	std::string ret;
	ret += "-d " + move + " " + std::to_string(start) + "\n";
	std::set<string> names;

	//for loop iterates through the fighters and adds
	//their name to a set if they have the specified
	//start time for specified move
	std::set<Fighter>::const_iterator x;
	for(x = fighters.begin(); x != fighters.end(); x++)
		if((*x).getMoveTimes()[move] == start)
			names.insert(names.end(), (*x).getName());
		
	std::set<string>::iterator y;
	for(y = names.begin(); y != names.end(); y++){
		ret += *y + "\n";
	}
	ret += "\n";
	return ret;
}




int main(int argc, char** argv){
	// Argument parsing
	if(argc != 4){
		std::cerr << "Proper usage is " << argv[0] << " [database file] [input file] [output file]" << std::endl;
		return -1;
	}

	std::ifstream dbfile(argv[1]);
	if(!dbfile){
		std::cerr << "Failed to open database " << argv[1] << " for reading." << std::endl;
	}

	std::ifstream infile(argv[2]);
	if(!infile){
		std::cerr << "Failed to open input " << argv[2] << " for reading." << std::endl;
	}

	std::ofstream outfile(argv[3]);
	if(!outfile){
		std::cerr << "Failed to open output " << argv[3] << " for writing." << std::endl;
	}

	///////Fill in the rest of main below:

	std::string word;
	std::set<Fighter> fighters;
	int col = 1;


	//data parsing
	while(dbfile >> word){
		//if at the start, skip to first fighter name
		if(word == "character-name")
			for(int i = 0; i < 8; i++)
				dbfile >> word;

		Fighter f(word); //adds fighter
		if(col == 1)
			dbfile >> word;

		while(col <= 8){
			col++;
			f.addMoveTime(move_names[col-2], std::stoi(word));
			//Adds move and time to a map to fighter
			if(col < 8)
				dbfile >> word;
		}
		col = 1;
		fighters.insert(fighters.end(), f);
		//insert the fighter into set of fighters for
		//later use
	}


	//goes through the input file
	while(infile >> word){
		std::string name;
		std::string move;

		if(word == "-q"){
			infile >> word;
			name = word;
			//checks if fighter name is valid
			if(fighters.find(word) != fighters.end()){
				infile >> word;
				move = word;
				//checks if move name is valid
				if(std::find(move_names, move_names + 7, move) != move_names + 7 || move == "all"){
					outfile << q(name, move, fighters);
					//puts returned string from function
					//q into the output file
				}
				else
					outfile << "Invalid move name: " << move << "\n\n";
			}
			else
				outfile << "Invalid character name: " << name << "\n\n";
		}
		if(word == "-f"){
			infile >> word;
			move = word;
			if(std::find(move_names, move_names + 7, move) != move_names + 7 || move == "all"){
				infile >> word;
				int limit = std::stoi(word);
				outfile << f(move, limit, fighters);
			}
			else
				outfile << "Invalid move name: " << move << "\n\n";
		}
		if(word == "-s"){
			infile >> word;
			move = word;
			if(std::find(move_names, move_names + 7, move) != move_names + 7 || move == "all"){
				infile >> word;
				int limit = std::stoi(word);
				outfile << s(move, limit, fighters);
			}
			else
				outfile << "Invalid move name: " << move << "\n\n";
		}
		if(word == "-d"){
			infile >> word;
			move = word;
			if(std::find(move_names, move_names + 7, move) != move_names + 7 || move == "all"){
				infile >> word;
				int startupFrame = std::stoi(word);
				outfile << d(move, startupFrame, fighters);
			}
			else
				outfile << "Invalid move name: " << move << "\n\n";
		}
	}

	return 0;
}
