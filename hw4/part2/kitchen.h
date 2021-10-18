#include <iostream>
#include <list>

#include "ingredient.h"
#include "recipe.h"

using namespace std;

class Kitchen{

public:
	Kitchen();

	const list<Ingredient>& getIngredients() const { return ingredients; }

	void addIngredient(string name, int units);
	void printIngredients(ostream &ost);

	void eraseIngredients();

	void makeRecipeInKitchen(istream &istr, ostream &ostr, const list<Recipe> &recipes);

private:
	list<Ingredient> ingredients;
};