#ifndef UCS_H
#define UCS_H
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <cstddef>
#include <stack>

using namespace std;

struct Node{
	Node(){}
	vector<vector<int>> vect; //current state
	Node *paren;
	vector<Node> *child_list;
	int a;  //position of the row
	int b;  //position of the column
	int cost;
	
	
};


class Tree{
	private:
	Node *root; //root node used to expand
	vector<Node> *goal_vector; //used to store list of goal states with different costs.
	list<Node> *frontier; //we access the front of the list and pops the front. we add elements to the end of the list (push_back)
	vector<Node> *explored; //add elements but don't remove them.
	stack<Node> answer;
	public:
	Tree();
	void set_root(Node *root);
	void add_frontier(Node add); //add an element to frontier
	void add_explored(Node add); //add an element to explored
	void add_goal(Node add); //add an element to goal vector.
	void remove_frontier(); //remove the front element of the frontier
	bool compare_goal(Node); //compare a node with goal state, return true if it is the goal.
	bool isExplored(Node); //check to see if a Node is already in explored, if it is we ignore it. return true if it is in explored set.
	void expand_left(Node &); //expand left of a node, then check with explored set, if it doesn't exist then we add it to the back of fontier and explored set. if it already exist in explored set, we don't add it.
	void expand_right(Node &); //expand right of a node, then check with explored set, if it doesn't exist then we add it to the back of fontier and explored set.
	void expand_up(Node &); //expand up of a node, then check with explored set, if it doesn't exist then we add it to the back of fontier and explored set.
	void expand_down(Node &); //expand down of a node, then check with explored set, if it doesn't exist then we add it to the back of fontier and explored set.
	void expand(Node); //we call this before we call expand_<direction>. This is just a series of if statement to check the viable directions we can expand a node. then we call the expand_<directions> based 
					   //whichever if statement they falls into. We can use int a and int b of a Node to check this condition. if a == 2 and b == 2 --> we know that this is the bottom right of the vector.
					   //knowing this we can only expand upward and towards the left.
	Node compare_goal();
	void trace_goal(Node *);
	void print_sol();
					   
					   
	
};




#endif
