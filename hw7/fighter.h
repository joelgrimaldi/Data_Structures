#include <map>

#ifndef FIGHTER_H
#define FIGHTER_H

using namespace std;

class Fighter{
public:
	Fighter(string n) : name(n) {}

	string getName() const { return name; }
	map<string, int> getMoveTimes() const { return moveTimes; }
	void addMoveTime(string move, int time) { moveTimes[move] = time; }

	friend bool operator<(const Fighter &a, const Fighter &b);

private:
	string name;
	map<string, int> moveTimes;
};

bool operator<(const Fighter &a, const Fighter &b){
	return(a.name < b.name);
}


#endif