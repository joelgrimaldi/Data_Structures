#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;


class Decathlete{
public:
	Decathlete(string aName, string aCountry, string aScore);

	//accesors
	string getName() const;
	string getCountry() const;
	vector<string> getScores() const;
	int getTotal() const;

	void setTotal(int totalTemp);

	void addScore(string newScore);
	void addPlace(int newPlace);
	void assignPlaces(vector<float> eventScores, string event);

	string printScores() const;
	void printScoreLine(vector<string> events, ofstream &wFile) const;
	void printPointLine(vector<string> events, ofstream &wFile);
	void printCustomLine(ofstream &wFile);

	float scoreToPoint(string score, string event);
	int summonTotal(vector<string> events);



private:
	string name;
	string country;
	vector<string> scores;
	int total = 0;
	vector<int> places;
};

vector<float> getPlaces(string event, vector<Decathlete> decs); //for custom