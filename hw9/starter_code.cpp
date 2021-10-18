/*
These two functions are not required for your program, but may be helpful!
The recursive function will generate every combination of 0/1 for 6 positions
in a vector. Whenever pos == 6, the vector is complete.

Hint: There are 6 different "fields" in a query, this may be useful in constructing
your hash table.
*/

// Title
// Year of Release
// Runtime in Minutes
// GenreCount GenreList
// ActorCount ActorList
// RoleCount RoleList

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <list>

#include "mdata.h"

using namespace std;

void permute_filters(int pos, vector<int> filter, movieData m, hashTable &ht){//, list<movieData>::iterator it){
	if(pos == 6){
		//Add other code here if you want to use the completed vectors

		movieData query;
		if(filter[0]){
			query.setTitle(m.getTitle());
		}
		if(filter[1]){
			query.setYear(m.getYear());
		}
		if(filter[2]){
			query.setRT(m.getRT());
		}
		if(filter[3]){
			query.setGC(m.getGC());
			query.setGL(m.getGL());
		}
		if(filter[4]){
			query.setAC(m.getGC());
			query.setAL(m.getAL());
		}
		if(filter[5]){
			query.setRC(m.getGC());
			query.setRL(m.getRL());
		}

		int i = ht.hashFunction(query);

		list<movieData> mList;
		mList.push_back(m);

		pair<movieData, list<movieData> > p(query, mList);

		ht.insert(i, p);

		return;
	}

	filter.push_back(0);
	vector<int> filter_new = filter;
	filter_new.back() = 1;
	permute_filters(pos+1, filter_new, m, ht);
	permute_filters(pos+1, filter, m, ht);
}

//Driver function, feel free to modify to pass more arguments
void permute_filters(hashTable &ht, vector<movieData> &movies){
	//list<movieData>::iterator it = movies.begin();
	for(uint x = 0; x < movies.size(); x++){
		movieData movie = movies[x];
		permute_filters(0, vector<int>(), movie, ht);
	}
}

movieData convert(ifstream &file){
	string word;

	file >> word;
	if(word == "")
		return movieData();
	string t = word;
	file >> word;
	int y = 0;
	if(word != "?")
		y = stoi(word);
	file >> word;
	int rT = 0;
	if(word != "?")
		rT = stoi(word);
	file >> word;

	int gC = stoi(word);
	vector<string> gL;
	for(int i = 0; i < gC; i++){
		file >> word;
		gL.push_back(word);
	}

	file >> word;
	int aC = stoi(word);
	vector<string> aL;
	for(int i = 0; i < aC; i++){
		file >> word;
		aL.push_back(word);
	}

	file >> word;
	int rC = stoi(word);
	vector<string> rL;
	for(int i = 0; i < aC; i++){
		file >> word;
		rL.push_back(word);
	}

	return movieData(t, y, rT, gC, gL, aC, aL, rC, rL);
}

map<string,string> actors(ifstream &aFile){
	string word;
	map<string, string> index;
	while(aFile >> word){
		string temp = word;
		aFile >> word;
		index[temp] = word;
	}

	return index;
}

vector<movieData> movies(ifstream &mFile){
	string word;
	vector<movieData> index;
	do{
		if(!mFile)
			break;
		index.push_back(convert(mFile));
	}while(true);

	return index;
}


int main(int argc, char** argv){
	// if(argc != 3){
	// 	std::cerr << "Proper usage is " << argv[0] << " [input file] [output file]" << std::endl;
	// 	return -1;
	// }

	// ifstream infile(argv[1]);
	// if(!infile){
	// 	std::cerr << "Failed to open input " << argv[1] << " for reading." << std::endl;
	// }

	// ofstream outfile(argv[2]);
	// if(!outfile){
	// 	std::cerr << "Failed to open output " << argv[2] << " for writing." << std::endl;
	// }

	string word;

	hashTable ht;
	map<string, string> aMap;
	vector<movieData> mVec;
	vector<movieData> queries;

	while(cin >> word){
		if(word == "quit")
			break;

		if(word == "table_size"){
			cin >> word;
			ht.setSize(stoi(word));
		}

		if(word == "occupancy"){
			cin >> word;
			ht.setMaxOccupancy(stof(word));
		}

		if(word == "query"){
			cin >> word;
			string t = word;
			cin >> word;
			int y = 0;
			if(word != "?")
				y = stoi(word);
			cin >> word;
			int rT = 0;
			if(word != "?")
				rT = stoi(word);
			cin >> word;

			int gC = stoi(word);
			vector<string> gL;
			for(int i = 0; i < gC; i++){
				cin >> word;
				gL.push_back(word);
			}

			cin >> word;
			int aC = stoi(word);
			vector<string> aL;
			for(int i = 0; i < aC; i++){
				cin >> word;
				aL.push_back(word);
			}

			cin >> word;
			int rC = stoi(word);
			vector<string> rL;
			for(int i = 0; i < aC; i++){
				cin >> word;
				rL.push_back(word);
			}

			queries.push_back(movieData(t, y, rT, gC, gL, aC, aL, rC, rL));
		}

		if(word == "movies"){
			cin >> word;
			ifstream movieFile(word);
			mVec = movies(movieFile);
		}

		if(word == "actors"){
			cin >> word;
			ifstream tmp(word);
			aMap = actors(tmp);
		}
	}
	permute_filters(ht, mVec);

	for(uint i = 0; i < queries.size(); i++){
		list<movieData> tmp = ht.validate(queries[i]);
		if(tmp.size() <= 0){
			cout << "No results for query.\n";
			continue;
		}

		int size = 0;
		for(movieData m : tmp){
			if(m.getTitle() != "?")
					size++;
		}

		cout << "Printing " << size << " result(s):\n";
		list<movieData>::iterator itr = tmp.begin();
		for(uint x = 0; x < tmp.size(); x++, itr++){
			if((*itr).getTitle() == "?")
				break;

			cout << (*itr).getTitle() << endl;
			cout << (*itr).getYear() << endl;
			cout << (*itr).getRT() << endl;
			cout << (*itr).getGL().size();
			for(uint y = 0; y < (*itr).getGL().size(); y++)
				cout << " " << (*itr).getGL()[y];
			cout << "\n" << (*itr).getAL().size();
			for(uint z = 0; z < (*itr).getAL().size(); z++){
				cout << " " << aMap[(*itr).getAL()[z]];
				cout << " (" << (*itr).getRL()[z] << ")";
			}
			cout << endl;
		}
	}

	//ht.print();
}