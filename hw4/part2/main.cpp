//
// PROVIDED CODE FOR HOMEWORK 4: GROCERY LISTS
// 
// You may use none, a little, or all of this, as you choose, but we
// strongly urge you to examine it carefully.  You may modify this
// code as you wish to complete the assignment.
//

// The program will handle several different operations: 
// adding a recipe, buying ingredients for the kitchen, printing out a
// recipe, making a recipe (which removes ingredients from the kitchen), 
// and printing out the current contents
// of the kitchen

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>

#include "recipe.h"
#include "kitchen.h"
#include "ingredient.h"

using namespace std;

// Helper functions
void readRecipe(istream &istr, ostream &ostr, list<Recipe> &recipes);
void addIngredients(istream &istr, ostream &ostr, Kitchen &kitchen);
void printRecipe(istream &istr, ostream &ostr, const list<Recipe> &recipes);

// The main loop parses opens the files for I/O & parses the input
int main(int argc, char* argv[]) {

  // Check the number of arguments.
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " in-file out-file\n";
    return 1;
  }
  // Open and test the input file.
  ifstream istr(argv[1]);
  if (!istr) {
    cerr << "Could not open " << argv[1] << " to read\n";
    return 1;
  }
  // Open and test the output file.
  ofstream ostr(argv[2]);
  if (!ostr) {
    cerr << "Could not open " << argv[2] << " to write\n";
    return 1;
  }

  // the kitchen & recipe list
  Kitchen kitchen;
  list<Recipe> recipes;

  // some variables to help with parsing
  char c;
  while (istr >> c) {
    if (c == 'r') {
      // READ A NEW RECIPE
      readRecipe(istr,ostr,recipes);

    } else if (c == 'a') {
      // ADD INGREDIENTS TO THE KITCHEN
      addIngredients(istr,ostr,kitchen);

    } else if (c == 'p') {
      // PRINT A PARTICULAR RECIPE
      printRecipe(istr,ostr,recipes);

    } else if (c == 'm') {
      // MAKE SOME FOOD
      kitchen.makeRecipeInKitchen(istr,ostr,recipes);

    } else if (c == 'k') {
      // PRINT THE CONTENTS OF THE KITCHEN
      kitchen.printIngredients(ostr);

    } else {
      cerr << "unknown character: " << c << endl;
      exit(0);
    }
  }  
}


void readRecipe(istream &istr, ostream &ostr, list<Recipe> &recipes) {
  int units;
  string name, name2;  
  istr >> name;
  // build the new recipe
  Recipe r(name);
  while (1) {
    istr >> units;
    if (units == 0) break;
    assert (units > 0);
    istr >> name2;
    r.addIngredient(name2,units);
  }


  // add it to the list
  list<Recipe>::const_iterator check;
  bool alreadyThere = false;
  for(check = recipes.begin(); check != recipes.end(); check++){
    if((*check).getName() == name)
      alreadyThere = true;
  }

  if(!alreadyThere){
    recipes.push_back(r);
    ostr << "Recipe for " << name << " added" << endl;
  }
  else
    ostr << "Recipe for " << name << " already exists" << endl;
}


void addIngredients(istream &istr, ostream &ostr, Kitchen &kitchen) {
  int units;
  string name;
  int count = 0;
  while (1) {
    istr >> units;
    if (units == 0) break;
    assert (units > 0);
    istr >> name;
    // add the ingredients to the kitchen
    kitchen.addIngredient(name,units);
    count++;
  }


  if(count != 1) //if plural
    ostr << count << " ingredients added to kitchen" << endl;
  else
    ostr << count << " ingredient added to kitchen" << endl;
}


void printRecipe(istream &istr, ostream &ostr, const list<Recipe> &recipes) {
  string name;
  istr >> name;

  list<Recipe>::const_iterator it;
  bool exists = false;   //if recipe exists
  for(it = recipes.begin(); it != recipes.end(); it++){
    if((*it).getName() == name){
      exists = true;
      ostr << "To make " << name << ", mix together:" << endl;;

      list<Ingredient> copy = (*it).RgetIngredients();
      copy.sort(sortByName);

      list<Ingredient>::iterator ingIt;
      for(ingIt = copy.begin(); ingIt != copy.end(); ingIt++){
        
        if((*ingIt).getNum() == 1)
          ostr << "  1 unit of " << (*ingIt).getName() << endl; //singular
        else
          ostr << "  " << (*ingIt).getNum() << " units of " << (*ingIt).getName() << endl;
      }
      break;
    }
  }
  if(!exists){
    ostr << "No recipe for " << name << endl;
  }
}


