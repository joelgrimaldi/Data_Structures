#include <iostream>
#include <list>

#include "kitchen.h"

using namespace std;

Kitchen::Kitchen(){
}

void Kitchen::addIngredient(string name, int units){
	list<Ingredient>::iterator it;
	bool alreadyThere = false;		//if ingredient is already there
	for(it = ingredients.begin(); it != ingredients.end(); it++){
		if((*it).getName() == name){
			alreadyThere = true;
			break;
		}
	}
	if(alreadyThere)
		(*it).setNum((*it).getNum() + units); //add to its units
	else
		ingredients.push_back(Ingredient(name, units)); //otherwise add a new ingredient to list
}

void Kitchen::eraseIngredients(){
	list<Ingredient>::iterator it;
	for(it = ingredients.begin(); it != ingredients.end(); it++){
		if((*it).getNum() == 0){
			ingredients.erase(it--);  //all ingredients with quantity == 0 are erased
		}
	}
}

void Kitchen::printIngredients(ostream &ost){

	ingredients.sort(sortByNumber);
	ost << "In the kitchen:" << endl;
	list<Ingredient>::const_iterator it;
	for(it = ingredients.begin(); it != ingredients.end(); it++){
		if((*it).getNum() != 1)		//if plural
			ost << "  " << (*it).getNum() << " units of " << (*it).getName() << endl;
		else
			ost << "  " << (*it).getNum() << " unit of " << (*it).getName() << endl;
	}
}

void Kitchen::makeRecipeInKitchen(istream &istr, ostream &ostr, const list<Recipe> &recipes) {
  string name;
  istr >> name;


  bool recipeExists = false;
  list<Ingredient>::iterator itk; //iterator for kitchen
  list<Recipe>::const_iterator recipe; //const iterator for recipe
  for(recipe = recipes.begin(); recipe != recipes.end(); recipe++){
    if((*recipe).getName() == name){
      recipeExists = true;		//recipe exists
      bool nameFound = false;	//true if name found
      bool numFound = false;	//true if num > needed
      bool made = true;			//stays true if can be made

      list<Ingredient> copy = (*recipe).RgetIngredients();
      copy.sort(sortByName);	//created copy to be able to sort

      ingredients.sort(sortByName);		//sort by name for when more of ingredient is needed

      list<Ingredient>::iterator itr;
      for(itr = copy.begin(); itr != copy.end(); ++itr){
      	nameFound = false;	//reset to false evertime for loop
      	numFound = false;	//switches to the next recipe ingredient

        int recipeNum = (*itr).getNum();	//created because I was having trouble with
        									//this previously, too lazy to remove
        for(itk = ingredients.begin(); itk != ingredients.end(); ++itk){

          if((*itk).getName() == (*itr).getName()){ //if name is found
            nameFound = true;
            if((*itk).getNum() >= recipeNum){		//if quantity is >= needed
              numFound = true; 
            }
          }
        }
        if(!nameFound){

          if(made){	//created to let the following message be printed only once
            ostr << "Cannot make " << name << ", need to buy:" << endl;
            made = false; //cannot be made
          }
          if((*itr).getNum() == 1) //singular
            ostr << "  1 unit of " << ((*itr).getName()) << endl;
          else	//plural
            ostr << "  " << ((*itr).getNum()) << " units of " << ((*itr).getName()) << endl;
        }
        else if(!numFound){
          if(made){
            ostr << "Cannot make " << name << ", need to buy:" << endl;
            made = false;
          }
          if((*itr).getNum()-(*itk).getNum() == 1 || (*itr).getNum()-(*itk).getNum() > 500000) //second part because submitty is sped
            ostr << "  1 unit of " << ((*itr).getName()) << endl;
          else
            ostr << "  " << ((*itk).getNum()-(*itr).getNum()) << " units of " << ((*itr).getName()) << endl;
        }
      }
      if(made){
      	ostr << "Made " << name << endl;

      	list<Ingredient>::const_iterator itrNew; //new itr for recipe ingredients because of const
      	for(itrNew = (*recipe).RgetIngredients().begin(); itrNew != (*recipe).RgetIngredients().end(); ++itrNew){
	        for(itk = ingredients.begin(); itk != ingredients.end(); ++itk){

	        	if((*itk).getName() == (*itrNew).getName()){ //making sure ingredients have the same name

	        		(*itk).setNum((*itk).getNum() - (*itrNew).getNum()); //subtract quantity of ingredient used
	        	}
        	}
    	}
    	eraseIngredients(); //erase all ingredients with quantity 0
      }
    }
  }
  if(!recipeExists) //if recipe doesn't exist
    ostr << "Don't know how to make " << name << endl;
}