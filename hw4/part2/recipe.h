#ifndef recipe_h
#define recipe_h

#include <iostream>
#include <list>

#include "ingredient.h"

using namespace std;

class Recipe{
	
public:
	Recipe(string _name);

	string getName() const { return name; }
	const list<Ingredient>& RgetIngredients() const { return rIngredients; }

	void addIngredient(string name, int units);

private:
	string name;
	list<Ingredient> rIngredients;
};

#endif