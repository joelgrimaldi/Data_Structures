#include "playing_card.h"
#include "node.h"

using namespace std;
// ==================================================================================
// prototypes for provided functions (implemented in main.cpp)
// ==================================================================================

bool SanityCheckPrimary(Node* top);
bool SanityCheckSorted(Node* first);
Node* CreateDeck(int numCards);
void DeckPushBackCard(Node* &deck, const string& suit, int num);
void PrintDeckPrimary(const string &description, Node* deck);


// ==================================================================================
//
// Write all the prototypes for the your functions here
// (they will be implemented in deck.cpp)
//
// NOTE: These are standalone functions, not part of a class.
//
// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
//
// ==================================================================================


int DeckSize(Node* deck);

//cuts deck and shuffles by alternating top and bottom
//by changing before and after pointers but keeping sorted pointers
Node* Shuffle(Node* top, Node* bottom, const string description);
void CutDeck(Node* deck, Node* &top, Node* &bottom, const string description);

void Deal(Node* &deck, Node** hands, const int numHands, const string description, const int size);
Node* SortHand(Node* &deck);

void PrintDeckSorted(const string description, Node* deck);

bool SamePrimaryOrder(Node* d1, Node* d2);
bool ReversePrimaryOrder(Node* d1, Node* d2);

Node* CopyDeck(Node* deck);
void DeleteAllCards(Node* &deck);