#include <string>
#include <cassert>
#include "Board.h"

void SimpleTest(); //Some basic tests
void StudentTest(); //Write your own test cases here

int main(){
	SimpleTest();
	std::cout << "Completed all simple tests." << std::endl;

	StudentTest();
	std::cout << "Completed all student tests." << std::endl;

	return 0;
}

// Do not modify this function - a fresh copy will be used on Submitty
void SimpleTest(){
	Board b("R","Y",".");

	std::cout << "Initial board:" << std::endl << b << std::endl;
	std::cout << "Row 0 has " << b.numTokensInRow(0) << std::endl;
	std::cout << "Row 4 has " << b.numTokensInRow(4) << std::endl;
	std::cout << "Row 5 has " << b.numTokensInRow(5) << std::endl;
	std::cout << "Column 0 has " << b.numTokensInColumn(0) << std::endl;
	std::cout << "Column 3 has " << b.numTokensInColumn(3) << std::endl;
	std::cout << "Column 4 has " << b.numTokensInColumn(4) << std::endl;

	b.insert(0,true);
	std::cout << "Second handout figure" << std::endl << b << std::endl;

	b.insert(1,false);
	b.insert(2,true);
	b.insert(3,true);
	std::cout << "Third handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	b.insert(1,true);
	b.insert(1,false);
	b.insert(1,true);
	b.insert(1,false);
	b.insert(1,true);
	std::cout << "Fourth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	b.insert(4,true);
	std::cout << "Fifth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	//Looks ugly if we don't make all tokens the same length, but not required
	Board b2("Puppy","Kitty","-----"); 
	std::string result;
	std::cout << "Starting a new board!" << std::endl;
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
}

////////STUDENT CODE//////

//Write your own test cases here
void StudentTest(){
	std::cout << "Testing checkConnectFour function horizontally:" << std::endl; //horizontal connect4 test
	std::string result;
	Board b3("6.9", "420", "---");
	b3.insert(0, false);
	b3.insert(1, false);
	b3.insert(2, false);
	result = b3.insert(3, false);
	if(result == "_"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	std::cout << std::endl;


	std::cout << "Testing copy function:" << std::endl; //copy
	b3.insert(12, true);
	b3.insert(14, true);
	b3.insert(15, false);
	b3.insert(2, true);
	std::cout << "Printing b3:" << std::endl;
	std::cout << b3 << std::endl;
	std::cout << "Printing b4:" << std::endl;
	Board b4(b3);
	std::cout << b4 << std::endl;


	std::cout << "Testing clear and copy:" << std::endl; //clear & copy
	b4.insert(9,true);
	b3.clear();
	std::cout << "b3.clear()" << std::endl;
	std::cout << "Printing b3:" << std::endl;
	std::cout << b3 << std::endl;
	std::cout << "Printing b4: (copy of b3)" << std::endl;
	std::cout << b4 << std::endl;


	std::cout << "Testing assignment operator:" << std::endl; //= overload
	Board b5("x","o","-");
	b5.insert(0, false);
	b5.insert(5, true);
	std::cout << "Printing b5:" << std::endl;
	std::cout << b5 << std::endl;
	Board b6("n","u","[]");
	b6 = b5;
	std::cout << "Printing b6: (assigned to b5)" << endl;
	std::cout << b6 << std::endl;


	std::cout << "Changing b5 to check if assignment operator works correctly:" << endl;
	b5.insert(16,true);
	std::cout << "Printing b5:" << std::endl;
	std::cout << b5 << std::endl;
	std::cout << "Printing b6: (assigned to b5)" << endl;
	std::cout << b6 << std::endl;
}

