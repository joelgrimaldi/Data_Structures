#ifndef ingredient_h
#define ingredient_h

#include <iostream>
#include <list>

using namespace std;

class Ingredient{

public:
	Ingredient();
	Ingredient(string _name, int _num);

	string getName() const { return name; }
	int getNum() const { return num; }

	void setNum(int newNum) { num = newNum; }

private:
	string name;
	int num;
};

bool sortByNumber(Ingredient &i1, Ingredient &i2);
bool sortByName(Ingredient &i1, Ingredient &i2);

#endif