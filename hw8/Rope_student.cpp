/*
Write your Rope implementation in this file. 
You do not have to keep any of the code that is already in this file.
Functions that e an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <vector>
#include <algorithm>
#include <cassert>
#include "Rope.h"

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves
rope_iterator& rope_iterator::operator++(){

	//iterates through by starting from the bottom left
	//leaf and moving across to the parent and right
	//until it ends by going past the root in which
	//case ptr_ will be returned as null

	if(ptr_->right){
		ptr_ = ptr_->right;
		while(ptr_->left != NULL)
			ptr_ = ptr_->left;
	}
	else if(ptr_->parent){
		while(ptr_->parent && ptr_->parent->right == ptr_)
			ptr_ = ptr_->parent;
		ptr_ = ptr_->parent;
	}
	else
		ptr_ = NULL;
	return *this;
}

//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const{

	//sets rope iterator to bottom
	//left Node* in the rope

	if(!root)
		return rope_iterator(NULL);
	Node* tmp = root;
	while(tmp->left)
		tmp = tmp->left;
	return rope_iterator(tmp);
}

Rope::Rope(){
	root = NULL;
	size_ = 0;
}

//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p){
	root = p;
	size_ = update_size();
}

int Rope::update_size(){

	//goes through entire rope and gets size

	int value = 0;
	for(rope_iterator it = begin(); it != end(); it++){
		if(is_leaf(it.ptr_))
			value += it.weight();
	}
	return value;
}

int rope_iterator::udw(Node* p, int ret, bool firstTime){

	//updates weights recursively

	if(!p)
		return 0;
	
	if(is_leaf(p)){
		return p->weight;
	}
	else{
		if(firstTime)
			ret = udw(p->left,ret, false);
		else
			ret = udw(p->left, ret, false) + udw(p->right, ret, false);
	}
	return ret;
}

void Rope::update_weights(){
	for(rope_iterator it = begin(); it != end(); it++){
		Node* p = it.ptr_;
		it.ptr_->weight = it.udw(p, 0, true);
	}
}


Rope::~Rope(){
	destructor(root, "");
}

void Rope::destructor(Node* p, std::string direction){
	if(!p)
		return;

	//destructs every direction

	destructor(p->left, "l");
	destructor(p->right, "r");

	delete p;
}

Rope::Rope(const Rope& r){
	size_ = r.size();
	root = new Node();

	Node* old = r.expose_root();
	if(old->left)
		root->left = old->left;			//setting values of new root
	if(old->right)
		root->right = old->right;		//equal to values of old root
	root->parent = NULL;
	root->weight = old->weight;
	root->value = old->value;

	root->left = copy(root->left,root);
	root->right = copy(root->right,root);
}

Node* Rope::copy(Node* q, Node* p){
	//q node being copied


	//copy used to copy every node in every
	//direction from the root until the
	//entire rope is copied

	if(!q)
		return NULL;

	Node* tmp = new Node();
	tmp->left = q->left;
	tmp->right = q->right;
	tmp->parent = p;
	tmp->weight = q->weight;
	tmp->value = q->value;

	tmp->left = copy(tmp->left, tmp);
	tmp->right = copy(tmp->right, tmp);

	return tmp;
}

Rope& Rope::operator= (const Rope& r){

	//essentially the same as copy

	size_ = r.size();
	root = new Node();
	Node* old = r.expose_root();
	if(old){
		if(old->left)
			root->left = old->left;			//setting values of new root
		if(old->right)
			root->right = old->right;		//equal to values of old root
		root->parent = NULL;
		root->weight = old->weight;
		root->value = old->value;
	}

	root->left = copy(root->left,root);
	root->right = copy(root->right,root);

	return *this;
}

Node* Rope::assign(Node* q, Node* p){
	if(!q)
		return NULL;

	Node* tmp = q;
	tmp->left = q->left;
	tmp->right = q->right;
	tmp->parent = p;
	tmp->weight = q->weight;
	tmp->value = q->value;

	if(tmp->left)
		tmp->left = assign(tmp->left, tmp);
	if(tmp->right)
		tmp->right = assign(tmp->right, tmp);

	return tmp;
}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char& c) const{

	//moves left while int i is less than
	//the weight of the node that it is on

	if(i >= size_ || i < 0)
		return false;
	Node* p = root;
	while(p->left || p->right){
		if(i < p->weight)
			p = p->left;
		else{
			i -= p->weight;
			p = p->right;
		}
	}
	c = p->value[i];
	return true;
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope& r){

	//makes a copy of the right rope and
	//adds this copy on to the left size
	//with a new root connecting them

	Node* new_root = new Node();
	int weight = 0;

	//getting all weights from left side leaves
	for(rope_iterator tmp = begin(); tmp != end(); tmp++){
		if(is_leaf(tmp.ptr_))
			weight += tmp.weight();
	}
	new_root->weight = weight;

	new_root->left = root;
	new_root->right = r.expose_root();
	new_root->parent = NULL;				// setting all of the values of
	new_root->left->parent = new_root;		// new_root
	new_root->right->parent = new_root;
	root = new_root;

	new_root->right = copy(new_root->right,new_root);

	size_ = update_size();

	//Rope rRope(r); //right rope
}

void Rope::node_concat(Node* p){

	//same as concat but without copying the
	//right side and just assigning it

	Node* new_root = new Node();
	int weight = 0;

	//getting all weights from left side leaves
	for(rope_iterator tmp = begin(); tmp != end(); tmp++){
		if(is_leaf(tmp.ptr_))
			weight += tmp.weight();
	}
	new_root->weight = weight;

	new_root->left = root;
	new_root->right = p;
	new_root->parent = NULL;				// setting all of the values of
	new_root->left->parent = new_root;		// new_root
	new_root->right->parent = new_root;
	root = new_root;
	
	int size = 0;
	for(rope_iterator tmp = begin(); tmp != end(); tmp++){
		if(is_leaf(tmp.ptr_))
			size += tmp.weight();
	}
	size_ = size;
}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const{

	//gets the starting index and then goes
	//until index reaches int j

	char l;
	s = "";
	for(int x = i; x <= j; x++){
		if(index(x,l))
			s += l;
	}
	if(!l)
		return false;
	return true;
}

//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope& Rope::split(int i, Rope& rhs){
	if(i >= size_ || i < 0){
		//if int i is a bad value 
		//return split(0) as default

		return split(0, rhs);
	}

	Node* p = root;

	std::vector<Node*> rightspots;

	bool movedRight = false;
	bool isZero = true;
	while(i > 0){
		isZero = false;
		if(is_leaf(p)){

			//split node into two new nodes
			//with a new parent

			//only should make it here when
			//i is not 0 and still on a leaf

			Node* l = new Node();
			p->left = l;
			p->left->value = p->value.substr(0,i);
			p->left->weight = i;
			p->left->parent = p;

			Node* r = new Node();
			p->right = r;
			p->right->value = p->value.substr(i);
			p->right->weight = p->value.size()-i;
			p->right->parent = p;

			p->value = "";
			p->weight = p->left->weight;
			p = p->right;
			i=0;
			break;
		}

		if(i < p->weight){

			//same moving left and right
			//as index, but if it has moved
			//right previously and attempts
			//to move to the left, the node
			//to the right is saved for later
			//copying and that section
			//is cut off from the *this
			//rope that we are working on

			if(movedRight){
				p->right->parent = NULL;
				rightspots.push_back(p->right);
				p->right = NULL;
			}
			p = p->left;
		}
		else{
			i -= p->weight;
			p = p->right;
			movedRight = true;
		}
	}

	if(!isZero){		//should not be called if int i == 0 from start

		//saves the final Node* that it was on,
		//which will be a leaf and need to be
		//separated from the *this rope

		//cuts it off from rope and
		//saves it to add it to rhs

		if(movedRight)
			p->parent->right = NULL;
		rightspots.push_back(p);
	}
	

	for(uint x = rightspots.size(); x > 0; x--){
		if(x == rightspots.size())
			rhs = Rope(rightspots[x-1]);
		else
			rhs.node_concat(rightspots[x-1]);
	}
	rhs.print(std::cout);

	//update size and weights of both ropes

	size_ = update_size();
	rhs.update_weights();
	update_weights();

	return *this;
}
