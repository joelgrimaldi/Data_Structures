#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <math.h>

#include "statsOrganizer.h"

using namespace std;

Decathlete::Decathlete(string aName, string aCountry, string aScore){
	name = aName;
	country = aCountry;
	scores.push_back(aScore);
}

string Decathlete::getName() const{					//GETTERS
	return name;
}

string Decathlete::getCountry() const{
	return country;
}

vector<string> Decathlete::getScores() const{
	return scores;
}

int Decathlete::getTotal() const{
	return total;
}

void Decathlete::setTotal(int totalTemp){			//SETTERS AND ADDERS(for vectors)
	total = totalTemp;
}

void Decathlete::addPlace(int newPlace){
	places.push_back(newPlace);
}

void Decathlete::addScore(string newScore){
	scores.push_back(newScore);
}

float Decathlete::scoreToPoint(string score, string event){			//CONVERT A SCORE TO A POINT
	int newPoint = 0;
	float scoreFloated = stof(score);

	if(event == "100_METERS"){										//seperate equations for each event
		newPoint = 25.4347 * pow((18 - scoreFloated),1.81);
	}
	else if(event == "LONG_JUMP"){
		newPoint = 0.14354 * pow((scoreFloated*100 - 220),1.4);
	}
	else if(event == "SHOT_PUT"){
		newPoint = 51.39 * pow((scoreFloated - 1.5),1.05);
	}
	else if(event == "HIGH_JUMP"){
		newPoint = 0.8465 * pow((scoreFloated*100 - 75),1.42);
	}
	else if(event == "400_METERS"){
		newPoint = 1.53775 * pow((82 - scoreFloated),1.81);
	}
	else if(event == "110_METERS_HURDLES"){
		newPoint = 5.74352 * pow((28.5 - scoreFloated),1.92);
	}
	else if(event == "DISCUS_THROW"){
		newPoint = 12.91 * pow((scoreFloated - 4),1.1);
	}
	else if(event == "POLE_VAULT"){
		newPoint = 0.2797 * pow((scoreFloated*100 - 100),1.35);
	}
	else if(event == "JAVELIN_THROW"){
		newPoint = 10.14 * pow((scoreFloated - 7),1.08);
	}
	else{
		string minutes = score.substr(0,1);							//convert the 1500_meters from minutes and seconds to only seconds
		string seconds = score.substr(2);

		float m = stof(minutes);
		float s = stof(seconds);

		scoreFloated = m*60 + s;

		newPoint = 0.03768 * pow((480-scoreFloated),1.85);
	}
	total += newPoint;
	return newPoint;
}

int Decathlete::summonTotal(vector<string> events){ //created to allow sorting before printing
	string last = name.substr(name.find(" "));
	string first = name.substr(0,name.size()-last.size());
	for(unsigned int x = 0; x < events.size(); x++){
		for(unsigned int y = 0; y < scores.size(); y++){
			string scoreEvent = scores.at(y).substr(scores.at(y).find("|")+1); //gets event name from the indexed score
			string onlyScore = scores.at(y).substr(0,scores.at(y).size() - scoreEvent.size() - 1); //gets score
			if(events.at(x) == scoreEvent){
				scoreToPoint(onlyScore, events.at(x));
			}
		}
	}
	return total;
}

vector<float> getPlaces(string event, vector<Decathlete> decs){
	vector<float> scoreSort;
	float newFloatedScore;
	for(unsigned int x = 0; x < decs.size(); x++){
		for(unsigned int y = 0; y < decs.at(x).getScores().size(); y++){
			string tempScore = decs.at(x).getScores().at(y); //score with event after
			string tempScoreEvent = tempScore.substr(tempScore.find("|")+1); //only event from score
			if(tempScoreEvent == event){
				if(event == "1500_METERS"){ //change minutes into seconds for the 1500 meter
					string minutes = decs.at(x).getScores().at(y).substr(0,1);
					string seconds = decs.at(x).getScores().at(y).substr(2);

					float m = stof(minutes);
					float s = stof(seconds);

					newFloatedScore = m*60 + s;
				}
				else{
					string tempScore2 = tempScore.substr(0,tempScore.size() - tempScoreEvent.size() - 1); //only score
					newFloatedScore = stof(tempScore2);
				}
				scoreSort.push_back(newFloatedScore);		//puts scores from certain event into a vector to later sort and find which place everyone came in
			}
		}
	}
	return scoreSort;
}

void Decathlete::assignPlaces(vector<float> eventScores, string event){			//assign places based on values grouped and scores earned by olympians
	vector<float>::iterator it = eventScores.begin();
	int counter = 0;
	for(unsigned int x = 0; x < scores.size(); x++)
	{
		if(scores[x].substr(scores[x].find("|")+1) == event)
		{
			counter++;
			string tempScoreEvent = scores[x].substr(scores[x].find("|")+1); //only event from score
			string tempScore2 = scores[x].substr(0,scores[x].size() - tempScoreEvent.size() - 1); //only score
			float myScore = stof(tempScore2); //score as a float
			if(event == "1500_METERS"){ //change minutes into seconds for the 1500 meter
				string minutes = scores[x].substr(0,1);
				string seconds = scores[x].substr(2);

				float m = stof(minutes);
				float s = stof(seconds);
				myScore = m*60 + s;
			}
			

			sort(eventScores.begin(),eventScores.end()); //sort event scores to search for object score to find place scored
			
			if(event == "LONG_JUMP" || event == "SHOT_PUT" || event == "HIGH_JUMP" || event == "DISCUS_THROW" 
				|| event == "POLE_VAULT" || event == "JAVELIN_THROW"){
				sort(eventScores.begin(),eventScores.end(),greater<float>()); //sorted from highest to lowest score, used for field events
				it = find(eventScores.begin(),eventScores.end(),myScore);
			}
			else{
				sort(eventScores.begin(),eventScores.end()); //sorted from lowest time to highest time, used for track events
				it = find(eventScores.begin(),eventScores.end(),myScore);
			}
			
			
			if(it != eventScores.end()) //if score is found in the vector of event scores
			{
				int index = distance(eventScores.begin(), it)+1; //find index
				places.push_back(index); //index saved as Nth place for that event
			}
		}
	}
	if(counter == 0){ //if decathlete didnt qualify for this event
		places.push_back(0);
	}
}









string Decathlete::printScores() const{
	string output;
	for(unsigned int x = 0; x < scores.size(); x++){
		output.append(scores.at(x));
		output.append(" ");
	}
	return output;
}

void Decathlete::printScoreLine(vector<string> events, ofstream &wFile) const{ //take in vector of events to get correct order
	string last = name.substr(name.find(" "));
	string first = name.substr(0,name.size()-last.size());
	wFile << setw(18) << first << setw(18) << last << setw(8) << country; //name and country
	for(unsigned int x = 0; x < events.size(); x++){
		bool space = true;
		for(unsigned int y = 0; y < scores.size(); y++){
			string scoreEvent = scores.at(y).substr(scores.at(y).find("|")+1); //gets event name from the indexed score
			string onlyScore = scores.at(y).substr(0,scores.at(y).size() - scoreEvent.size() - 1); //gets score
			if(events.at(x) == scoreEvent){
				wFile << setw(10) << onlyScore;
				space = false;
			}
		}
		if(space){
			wFile << setw(10) << " ";
		}
	}
}

void Decathlete::printPointLine(vector<string> events, ofstream &wFile){
	string last = name.substr(name.find(" "));
	string first = name.substr(0,name.size()-last.size());
	wFile << setw(18) << first << setw(18) << last << setw(8) << country; //name and country
	for(unsigned int x = 0; x < events.size(); x++){
		bool zero = true;
		for(unsigned int y = 0; y < scores.size(); y++){
			string scoreEvent = scores.at(y).substr(scores.at(y).find("|")+1); //gets event name from the indexed score
			string onlyScore = scores.at(y).substr(0,scores.at(y).size() - scoreEvent.size() - 1); //gets score
			if(events.at(x) == scoreEvent){
				wFile << setw(10) << scoreToPoint(onlyScore, events.at(x));
				zero = false;
			}
		}
		if(zero){
			wFile << setw(10) << 0;
		}
	}
	total /= 2;
	wFile << total; //divided by two because I ran scoreToPoint twice and this messed up the total values by doubling them and this was an easy fix
}


void Decathlete::printCustomLine(ofstream &wFile){
	string last = name.substr(name.find(" "));
	string first = name.substr(0,name.size()-last.size());
	wFile << setw(18) << first << setw(18) << last << setw(8) << country; //name and country
	for(unsigned int x = 0; x < places.size(); x++){
		if(places[x] == 0){
			wFile << setw(10) << "DNF"; 		//print DNF if a certain decathlete did not qualify
		}										//aka DNF == DID NOT FINISH
		else{
			wFile << setw(10) << places[x];		//otherwise continue to print place values normally
		}
	}
}
