// ==================================================================================
// Implement all functions that you listed by prototype in deck.h
// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
//
// NOTE: These are standalone functions, not part of a class.
// ==================================================================================

#include <iostream>
#include <cassert>
#include "playing_card.h"
#include "node.h"
#include "deck.h"

using namespace std;

// ==================================================================================


int DeckSize(Node* deck)
{
	int counter = 0;
	Node* tmp = deck;
	while(tmp != NULL){
		counter++;
		tmp = tmp->after;
	}

	return counter;
}

void CutDeck(Node* deck, Node* &top, Node* &bottom, const string description)
{
	if(description == "perfect"){
		Node* tmp = deck;
		int end = DeckSize(deck);
		int middle = end/2;
		int counter = 1;

		top = tmp; 					//sets first node value to first card
		top->before = NULL;			//nothing before first one therefore NULL
		tmp = tmp->after;			//moves to next
		counter++;

		Node* tmpTop = top;

		while(counter <= middle){
			tmpTop->after = tmp;				//these three lines
			tmpTop->after->before = tmpTop;		//set node pointers around
			tmp = tmp->after;					//specified top node to make
												//printing possible
			tmpTop = tmpTop->after;	//on to next
			counter++;
		}
		tmpTop->after = NULL;		//make node after end = NULL


		bottom = tmp;				
		bottom->before = NULL;		//initializing
		tmp = tmp->after;
		counter++;

		Node* tmpBot = bottom;

		while(counter <= end){
			tmpBot->after = tmp;
			tmpBot->after->before = tmpBot;		//same as top
			tmp = tmp->after;

			tmpBot = tmpBot->after;
			counter++;
		}
		tmpBot->after = NULL;
	}
}

//cuts deck and shuffles by alternating top and bottom
//by changing before and after pointers but keeping sorted pointers
// --always take top first because order only matters when called
//   in parameters
Node* Shuffle(Node* top, Node* bottom, const string description)
{
	Node* deck = NULL;
	if(description == "perfect"){
		//going to take one from top and then one from bottom
		//and continue alternating that way

		int topSize = DeckSize(top);
		int botSize = DeckSize(bottom);
		int counter = 1;

		deck = top;
		deck->before = NULL;	//initialize with a top node
		top = top->after;
		counter++; // = 2

		while(counter <= topSize+botSize){		//counter <= total size
			if(counter % 2 == 0){				//if counter == even number
				deck->after = bottom;			//add one node from bottom to
				deck->after->before = deck;		//doubly linked list deck
				bottom = bottom->after;
			}
			else{								//otherwise add one node
				deck->after = top;				//from top
				deck->after->before = deck;
				top = top->after;				//this causes intertwining
			}									//of top and bottom in deck
			deck = deck->after;
			counter++;
		}

		while(deck->before != NULL){			//reset deck to the beginning
			deck = deck->before;				//for easy printing later
		}
	}
	return deck;
}




void Deal(Node* &deck, Node** hands, const int numHands, const string description, const int size)
{
	if(description == "one-at-a-time"){
		Node* tmp = deck;			//temporaries for deck and
		Node* tmpHands[numHands];  	//double pointer hands

		tmp->before = NULL;			

		for(int i = 0; i < numHands; i++){
			hands[i] = NULL;				//initializing hand node pointers
		}									//as NULL to satisfy certain test cases

		for(int x = 0; x < size; x++){
			for(int y = 0; y < numHands; y++){
				if(x == 0){						//if going through first x loop
					hands[y] = tmp;				//then initialize all the start
					hands[y]->before = NULL;	//of the hand node pointers
					tmpHands[y] = hands[y];		//to different variables as moving
					tmp = tmp->after;			//through tmp, aka deck
					continue;
				}

				tmpHands[y]->after = tmp;					//if it is not the first loop
				tmpHands[y]->after->before = tmpHands[y];	//then change all pointers around
				tmpHands[y] = tmpHands[y]->after;			//designated spot and set
				Node* temp = tmp->after;					//tmp to NULL while going along
				tmp = NULL;									//to show that they are getting
				tmp = temp;									//removed from the deck
				
				if(x == size-1)
					tmpHands[y]->after = NULL;				//if it is the end of a certain hand
			}												//then set its after to NULL
		}
		if(tmp != NULL){			//if deck was not all used
			tmp->before = NULL;		//then set the before of
		}							//current location to null
									//to satisfy sanity checks
		deck = tmp;
	}
}

Node* SortHand(Node* &deck)
{

	Node* tmp = deck;
	bool checkMore = false;

	while(tmp->after != NULL){
		checkMore = false;
		if(tmp->after->getCard() > tmp->getCard()){				//if card after current belongs in front
			if(tmp->sorted_next != NULL){						//of current card when sorted and
				tmp->sorted_next->sorted_prev = tmp->after;		//sorted_next != NULL then move pointers around
				tmp->after->sorted_next = tmp->sorted_next;		//to satisfy for conditions and if sorted_next
				checkMore = true;								//isnt NULL then check more after the current
			}													//move, and if sorted_next is null then just
			tmp->sorted_next = tmp->after;						//add the card we're looking at to the back
			tmp->after->sorted_prev = tmp;
			if(checkMore)
				tmp = tmp->sorted_next;

			while(tmp->sorted_next != NULL && tmp->getCard() > tmp->sorted_next->getCard()){
				if(tmp->sorted_next->sorted_next == NULL){
					tmp->sorted_next->sorted_prev = tmp->sorted_prev;	//check over and over if card
					tmp->sorted_next->sorted_next = tmp;				//belongs behind the next card
																		//in the list and if it does
					tmp->sorted_prev->sorted_next = tmp->sorted_next;	//continue moving it backwards
					tmp->sorted_prev = tmp->sorted_next;				//until it gets to one that it 
					tmp->sorted_next = NULL;							//no longer belongs behind or it
					break;												//reaches the end of the sorted_next
				}														//pointers where it equals NULL
				tmp->sorted_prev->sorted_next = tmp->sorted_next;
				tmp->sorted_next->sorted_prev = tmp->sorted_prev;		//use different methods when
																		//tmp->sorted_next->sorted_next
				tmp->sorted_next->sorted_next->sorted_prev = tmp;		//is NULL too create the end
				tmp->sorted_prev = tmp->sorted_next;					//of the sorted pointers

				tmp->sorted_next = tmp->sorted_next->sorted_next;
				tmp->sorted_prev->sorted_next = tmp;

			}
		}
		else{
			if(tmp->sorted_prev != NULL){						//same thing as above but
				tmp->sorted_prev->sorted_next = tmp->after;		//if the card belongs
				tmp->after->sorted_prev = tmp->sorted_prev;		//further forward in the list
				checkMore = true;								//when sorted
			}
			tmp->sorted_prev = tmp->after;
			tmp->after->sorted_next = tmp;
			if(checkMore)
				tmp = tmp->sorted_prev;

			while(tmp->sorted_prev != NULL && tmp->getCard() < tmp->sorted_prev->getCard()){
				if(tmp->sorted_prev->sorted_prev == NULL){
					tmp->sorted_prev->sorted_next = tmp->sorted_next;
					tmp->sorted_prev->sorted_prev = tmp;

					tmp->sorted_next->sorted_prev = tmp->sorted_prev;
					tmp->sorted_next = tmp->sorted_prev;
					tmp->sorted_prev = NULL;
					break;
				}
				tmp->sorted_next->sorted_prev = tmp->sorted_prev;
				tmp->sorted_prev->sorted_next = tmp->sorted_next;

				tmp->sorted_prev->sorted_prev->sorted_next = tmp;
				tmp->sorted_next = tmp->sorted_prev;

				tmp->sorted_prev = tmp->sorted_prev->sorted_prev;
				tmp->sorted_next->sorted_prev = tmp;
				
			}

		}
		if(!checkMore)			//if pointer has not already moved
			tmp = tmp->after;	//from checkMore then move it to after
	}
	while(tmp->sorted_prev != NULL)
		tmp = tmp->sorted_prev;			//bring back tmp to the start of
										//the sorted list
	return tmp;
}



void PrintDeckSorted(const string description, Node* deck)
{
	//same as PrintDeckPrimary except
	//moves by sorted_next instead
	//of after when iterating through
	cout << description << " ";
	Node* tmp = deck;
	while(tmp != NULL){
		cout << tmp->getCard().getString();
		if(tmp->sorted_next != NULL)
			cout << " ";
		tmp = tmp->sorted_next;		//<- here
	}
	cout << endl;
}



bool SamePrimaryOrder(Node* d1, Node* d2)
{
	if(DeckSize(d1) != DeckSize(d2))
		return false;					//if they are different sizes this
										//is automatically false
	int size = DeckSize(d1);
	int counter = 1;
	while(counter <= size){
		if(d1->getCard() != d2->getCard())
			return false;
		d1 = d1->after;					//check each card and move
		d2 = d2->after;					//to next if they are the same
		counter++;
	}
	return true;
}

bool ReversePrimaryOrder(Node* d1, Node* d2)
{
	if(DeckSize(d1) != DeckSize(d2))
		return false;

	Node* tmpD2 = d2;

	while(tmpD2->after != NULL){
		tmpD2 = tmpD2->after;		//puts tmpD2 to the last
	}								//!NULL Node of d2
	
	
	int size = DeckSize(d1);
	int counter = 1;
	while(counter <= size){
		if(d1->getCard() != tmpD2->getCard())
			return false;
		d1 = d1->after;
		tmpD2 = tmpD2->before;		//same thing but d2
		counter++;					//is reversed
	}
	return true;
}



Node* CopyDeck(Node* deck)
{
	Node* copy = NULL;	//copy = NULL to prevent errors
	
	int size = DeckSize(deck);
	int counter = 0;

	while(counter < size){
		DeckPushBackCard(copy,deck->getCard().getSuit(),deck->getCard().getCard());
		deck = deck->after;
		counter++;					//same as creating a new deck, but
	}								//just putting them into a copy
									//with new nodes so they aren't linked
	return copy;
}

void DeleteAllCards(Node* &deck)
{
	Node* next;

	while(deck != NULL){
		next = deck->after;
		delete deck;			//in the end every instance
		deck = next;			//of deck will be deleted and
	}							//next will = NULL
}