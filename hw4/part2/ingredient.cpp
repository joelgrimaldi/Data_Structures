#include <iostream>
#include <list>

#include "ingredient.h"

using namespace std;


Ingredient::Ingredient(){
	name = "get me out";
	num = 0;
}

Ingredient::Ingredient(string _name, int _num){
	name = _name;
	num = _num;
}

bool sortByNumber(Ingredient &i1, Ingredient &i2){
	if(i1.getNum() < i2.getNum()){
		return true;
	}
	else if(i1.getNum() == i2.getNum()){ //if same quantity
		if(i1.getName() < i2.getName()){
			return true;
		}
	}
	return false;
}

bool sortByName(Ingredient &i1, Ingredient &i2){
	return i1.getName() < i2.getName();
}