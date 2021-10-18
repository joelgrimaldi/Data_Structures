#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Title
// Year of Release
// Runtime in Minutes
// GenreCount GenreList
// ActorCount ActorList
// RoleCount RoleList

class movieData{
public:
	movieData() : title("?"), year(0), runTime(0), genreCount(0), genreList(), actorCount(0),
	actorList(), roleCount(0), roleList() {}

	movieData(string t, int y, int rT, int gC, vector<string>gL, int aC, vector<string>aL, int rC, vector<string>rL) : 
	title(t), year(y), runTime(rT), genreCount(gC), genreList(gL), actorCount(aC), 
	actorList(aL), roleCount(rC), roleList(rL) {}

	void print();

	const string getTitle() { return title; }
	const int getYear() { return year; }
	const int getRT() { return runTime; }
	const int getGC() { return genreCount; }
	const vector<string> getGL() { return genreList; }
	const int getAC() { return actorCount; }
	const vector<string> getAL() { return actorList; }
	const int getRC() { return roleCount; }
	const vector<string> getRL() { return roleList; }

	void setTitle(string s) { title = s; }
	void setYear(int i) { year = i; }
	void setRT(int i) { runTime = i; }
	void setGC(int i) { genreCount = i; }
	void setGL(vector<string> v) { genreList = v; }
	void setAC(int i) { actorCount = i; }
	void setAL(vector<string> v) { actorList = v; }
	void setRC(int i) { roleCount = i; }
	void setRL(vector<string> v) { roleList = v; }
	// movieData& operator=(const movieData &b);

	friend bool operator==(const movieData &a, const movieData &b);
	friend bool operator!=(const movieData &a, const movieData &b);

private:
	string title;
	int year;
	int runTime;
	int genreCount;
	vector<string> genreList;
	int actorCount;
	vector<string> actorList;
	int roleCount;
	vector<string> roleList;
};

void movieData::print(){
	cout << title << endl;
	cout << year << endl;
	cout << runTime << endl;
	cout << genreCount << endl;
	cout << actorCount << endl;
	cout << roleCount << endl;
}

// movieData& movieData::operator=(const movieData &b){
// 	if(this != &b)
// 		return *this;
// 	title = b.title;
// 	year = b.year;
// 	runTime = b.runTime;
// 	genreCount = b.genreCount;
// 	genreList = b.genreList;
// 	actorCount = b.actorCount;
// 	actorList = b.actorList;
// 	roleCount = b.roleCount;
// 	roleList = b.roleList;
// 	return *this;
// }

bool operator==(const movieData &a, const movieData &b){
	if(a.title == b.title && a.year == b.year && a.runTime == b.runTime && a.genreList == b.genreList 
	  && a.actorList == b.actorList && a.roleList == b.roleList)
		return true;
	return false;
}

bool operator!=(const movieData &a, const movieData &b){
	return !(a == b);
}

class hashTable{
public:
	hashTable() : max_occupancy(.65){ setSize(650); }

	//void push_back(pair<movieData,list<movieData>> p){ ht.push_back(p); }
	void insert(int key, pair<movieData, list<movieData> > p);
	vector<pair<movieData, list<movieData>>> getTable() { return ht; }

	void setSize(int table_size);
	void setMaxOccupancy(float f) { max_occupancy = f; }

	void resize();
	int hashFunction(movieData p);
	list<movieData> validate(movieData p);

	void print();

private:
	vector<pair<movieData, list<movieData>>> ht;
	int size;
	float occupancy;
	float max_occupancy;
};

list<movieData> hashTable::validate(movieData p){
	int index = hashFunction(p);

	if(ht[index].first == p)
		return ht[index].second;

	else{
		while(ht[index].first != p){
			index++;
			if(index > size)
				return list<movieData>{};
		}
		return ht[index].second;
	}
}

void hashTable::resize(){
	uint old_size = size;
	size *= 2;
	for(uint i = 0; i < ht.size(); i++){
		if(ht[i].first.getTitle() == "NULL")
			continue;

		if(i >= old_size){
			movieData tmp;
			tmp.setTitle("NULL");
			list<movieData> empty;
			pair<movieData, list<movieData> > p(tmp, empty);
			ht[i] = p;
		}

		else{
			uint hash = hashFunction(ht[i].first);
			if(i != hash){
				insert(hash, ht[i]);

				movieData tmp;
				tmp.setTitle("NULL");
				list<movieData> empty;
				pair<movieData, list<movieData> > p(tmp, empty);
				ht[i] = p;
			}
		}
	}
}

void hashTable::setSize(int table_size){
	size = table_size;
	movieData dummy;
	dummy.setTitle("NULL");
	list<movieData> dummyList;

	for(int x = 0; x < table_size; x++)
		ht.push_back(pair<movieData, list<movieData>>(dummy, dummyList));

}

void hashTable::insert(int key, pair<movieData, list<movieData>> p){
	if(ht[key].first == p.first){
		list<movieData>::iterator it = p.second.begin();
		for(; it != p.second.end(); it++)
			ht[key].second.push_back(*it);
	}
	else{
		if(key < size){
			if(ht[key].first.getTitle() != "NULL")
				return insert(key+1, p);
			else{
				occupancy += 1/size;
				pair<movieData, list<movieData>> tmp(p.first, p.second);
				ht[key] = tmp;
				if(occupancy > max_occupancy){
					resize();
				}
			}
		}
	}
}

int hashTable::hashFunction(movieData p){
	int s = 0;
	for(char ch : p.getTitle())
		s += int(ch);
	//s += int(p.getTitle());
	s += p.getYear();
	s += p.getRT();
	s += p.getGL().size();
	for(uint i = 0; i < p.getGL().size(); i++){
		for(uint x = 0; x < p.getGL()[i].size(); x++)
			s += int(p.getGL()[i][x]);
	}

	s += p.getAL().size();
	for(uint i = 0; i < p.getAL().size(); i++){
		for(uint x = 0; x < p.getAL()[i].size(); x++)
			s += int(p.getAL()[i][x]);
	}

	s += p.getRL().size();
	for(uint i = 0; i < p.getRL().size(); i++){
		for(uint x = 0; x < p.getRL()[i].size(); x++)
			s += int(p.getRL()[i][x]);
	}

	return s%size;
}

void hashTable::print(){
	cout << "\n\n\nHASH TABLE:\n------------\n\n";
	for(int i = 0; i < size; i++){
		if(ht[i].first.getTitle() == "NULL")
			continue;

		cout << "\n" << i << "\n---" << endl;
		cout << ht[i].first.getTitle() << endl;
		cout << ht[i].first.getYear() << endl;
		cout << ht[i].first.getRT() << endl;
		cout << ht[i].first.getGL().size() << endl;
		cout << ht[i].first.getAL().size() << endl;
		cout << ht[i].first.getRL().size() << endl;
	}
}