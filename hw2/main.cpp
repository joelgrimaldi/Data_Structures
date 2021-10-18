#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cassert>
#include <bits/stdc++.h> 

#include "statsOrganizer.h"

using namespace std;

/*
possible errors

-if someone has more than two names


*/

bool sortbysec(const Decathlete& a, const Decathlete& b){ //sorts by second variable, used later when sorting by country and by last name
	if(a.getCountry() == b.getCountry()){
		return (a.getName().substr(a.getName().find(" ")+1) < b.getName().substr(b.getName().find(" ")+1));
	}
	return (a.getCountry() < b.getCountry());
}

bool sortbyTotal(const Decathlete& a, const Decathlete& b){
	return (a.getTotal() > b.getTotal());
}




int main(int argc, char *argv[]){

	string infile = argv[1];
	string outfile = argv[2];
	string type = argv[3];

	//string infile = "2008_olympics.txt";
	//string outfile = "test_outfile.txt";
	//string type = "points";

	string line; //placeholder when running through file line by line
	ifstream file(infile); //file being read
	ofstream wFile(outfile); //write file

	vector<Decathlete> decs; //vector of Decathletes
	vector<string> names; //vector of Decathlete names to check if they are already in the vector

	string event;
	vector<string> events = {"100_METERS","LONG_JUMP","SHOT_PUT","HIGH_JUMP","400_METERS","110_METERS_HURDLES"
							,"DISCUS_THROW","POLE_VAULT","JAVELIN_THROW","1500_METERS"};
	if(file.is_open())
	{	
		while(getline(file,line)) //run through until event line
		{
			if(line.substr(0,1) == "") //if empty line
			{
				continue;
			}
			if(line.substr(0,5) == "event") //if event name line
			{
				event = line.substr(6);
				continue;
			}
			else
			{
				int nameSpot = line.find(" ",line.find(" ")+1); //index of second space
				string name = line.substr(0,nameSpot);

				int ctSpot = line.find(" ",nameSpot+1); //index of third space
				string country = line.substr(nameSpot+1,3); //gets country

				//int numSpot = line.find(" ",ctSpot+1); //not needed but keeping for now
				string num = line.substr(ctSpot+1); //gets number
				if(num.find(" ") != string::npos){
					num = num.substr(0,num.size()-1);
				}
				num += "|" + event; //creates a vector of string objects that are <score>|<event>	eg. 14.01|POLE_VAULT

				if(find(names.begin(),names.end(),name) == names.end())	//if name is not in vector names, create an object for them
				{
					names.push_back(name);
					decs.push_back(Decathlete(name,country,num));
				}
				else //if name is already in vector, just add the score to their data
				{
					for(unsigned int y = 0; y < decs.size(); y++){
						if(name == decs.at(y).getName()){
							decs.at(y).addScore(num);
							break;
						}
					}
				}
			}
		}

		wFile << left;
		wFile << setw(44);
		if(type == "scores"){
			wFile << "DECATHLETE SCORES";
		}
		else if(type == "points"){
			wFile << "DECATHLETE POINTS";
		}
		else{
			wFile << "DECATHLETE PLACEMENTS";
		}

		for(unsigned int x = 0; x < events.size(); x++){ //Top line formatting

			if(x != events.size()-1){ //prevents last spot from having extra space behind it
				wFile << setw(10);
			}

			if(events[x] == "POLE_VAULT"){
				wFile << "PV";
			}
			else if(events[x] == "JAVELIN_THROW"){
				wFile << "JT";
			}
			else if(events[x] == "1500_METERS"){
				wFile << "1500";
			}
			else if(events[x] == "SHOT_PUT"){
				wFile << "SP";
			}
			else if(events[x] == "HIGH_JUMP"){
				wFile << "HJ";
			}
			else if(events[x] == "400_METERS"){
				wFile << "400";
			}
			else if(events[x] == "110_METERS_HURDLES"){
				wFile << "110H";
			}
			else if(events[x] == "DISCUS_THROW"){
				wFile << "DT";
			}
			else if(events[x] == "100_METERS"){
				wFile << "100";
			}
			else if(events[x] == "LONG_JUMP"){
				wFile << "LJ";
			}
		}


		if(type == "points"){
			wFile << right;
			wFile << setw(11) << "TOTAL";
			wFile << left;
		}
		wFile << endl;



		sort(decs.begin(), decs.end(), sortbysec); //sort vector of objects by country and then by last name

		if(type == "scores"){
			for(unsigned int x = 0; x < decs.size(); x++){
				decs.at(x).printScoreLine(events, wFile);
				wFile << endl;
			}
		}



		

		if(type == "points"){
			for(unsigned int x = 0; x < decs.size(); x++){
				int summonedTotal = decs.at(x).summonTotal(events);
				decs.at(x).setTotal(summonedTotal);
			}

			sort(decs.begin(), decs.end(), sortbyTotal); //sort vector of objects by total points

			for(unsigned int x = 0; x < decs.size(); x++){
				decs.at(x).printPointLine(events, wFile);
				wFile << endl;
			}
		}



		if(type == "custom"){
			vector<float> scores100 = getPlaces("100_METERS",decs);					//gather score values from each event and put them
			vector<float> scoresLJ = getPlaces("LONG_JUMP",decs);					//into a vector for later sorting purposes
			vector<float> scoresSP = getPlaces("SHOT_PUT",decs);
			vector<float> scoresHJ = getPlaces("HIGH_JUMP",decs);
			vector<float> scores400 = getPlaces("400_METERS",decs);
			vector<float> scores110H = getPlaces("110_METERS_HURDLES",decs);
			vector<float> scoresDT = getPlaces("DISCUS_THROW",decs);
			vector<float> scoresPV = getPlaces("POLE_VAULT",decs);
			vector<float> scoresJT = getPlaces("JAVELIN_THROW",decs);
			vector<float> scores1500 = getPlaces("1500_METERS",decs);

			for(unsigned int x = 0; x < decs.size(); x++){
				decs.at(x).assignPlaces(scores100, "100_METERS");					//assign decathletes to their rightful places
				decs.at(x).assignPlaces(scoresLJ, "LONG_JUMP");						//based on scores earned in certain events
				decs.at(x).assignPlaces(scoresSP, "SHOT_PUT");
				decs.at(x).assignPlaces(scoresHJ, "HIGH_JUMP");
				decs.at(x).assignPlaces(scores400, "400_METERS");
				decs.at(x).assignPlaces(scores110H, "110_METERS_HURDLES");
				decs.at(x).assignPlaces(scoresDT, "DISCUS_THROW");
				decs.at(x).assignPlaces(scoresPV, "POLE_VAULT");
				decs.at(x).assignPlaces(scoresJT, "JAVELIN_THROW");
				decs.at(x).assignPlaces(scores1500, "1500_METERS");
				decs.at(x).summonTotal(events); //used to sort by total
			}

			sort(decs.begin(), decs.end(), sortbyTotal);							//sort by total to make it look pretty, otherwise
																					//DNFs will be scattered everywhere
			for(unsigned int x = 0; x < decs.size(); x++){
				decs[x].printCustomLine(wFile);	//simple print command
				wFile << endl;
			}
		}
	}
}