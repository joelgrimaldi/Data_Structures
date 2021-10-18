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

using namespace std;

int main(){
	double * p = new double;
	*p = 35.1;
	double *q = p;
	cout << *p << " " << *q << endl;
	p = new double;
	*p = 27.1;
	cout << *p << " " << *q << endl;
	*q = 12.5;
	cout << *p << " " << *q << endl;
	delete p;
	delete q;
}