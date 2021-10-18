#include <iostream>
#include <list>

#include "recipe.h"

using namespace std;

Recipe::Recipe(string _name){
	name = _name;
}

void Recipe::addIngredient(string name, int units){
	list<Ingredient>::iterator it;
	bool alreadyThere = false;
	for(it = rIngredients.begin(); it != rIngredients.end(); it++){
		if((*it).getName() == name){
			alreadyThere = true;
			break;
		}
	}
	if(!alreadyThere) //only add if it's not already there
		rIngredients.push_back(Ingredient(name, units));
}