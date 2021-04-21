#include "ucs.h"


Tree::Tree(){
	this->root = new Node();
	this->goal_vector = new vector<Node>();
	this->frontier = new list<Node>();
	this->explored = new vector<Node>();
}
void Tree::set_root(Node *a){
	this->root = a;
}