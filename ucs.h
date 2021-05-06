#ifndef UCS_H
#define UCS_H

#include "node.h"

struct Node;

class Tree {
private:
	Node root; //root node used to expand
	vector<Node> goal_vector; //used to store list of goal states with different costs.
	list<Node> frontier; //we access the front of the list and pops the front. we add elements to the end of the list (push_back)
	vector<Node> explored; //add elements but don't remove them.
	vector<Node> answer;
	Node* goal;
	int frontier_size;
public:
	Tree();
	void set_root(Node root);//		(functional)
	void add_frontier(Node add); //add an element to frontier		(functional)
	void add_explored(Node add); //add an element to explored		(functional)
	void add_goal(Node add); //add an element to goal vector.		(functional)
	void remove_frontier(); //remove the front element of the frontier		(functional)
	bool compare_goal(Node); //compare a node with goal state, return true if it is the goal.		(functional)
	bool isExplored(Node); //check to see if a Node is already in explored, if it is we ignore it. return true if it is in explored set.		(functional)
	void expand_left(Node); //expand left of a node, then check with explored set, if it doesn't exist then we add it to the back of fontier and explored set. if it already exist in explored set, we don't add it.		(functional)
	void expand_right(Node); //expand right of a node, then check with explored set, if it doesn't exist then we add it to the back of fontier and explored set.		(functional)
	void expand_up(Node); //expand up of a node, then check with explored set, if it doesn't exist then we add it to the back of fontier and explored set.		(functional)
	void expand_down(Node); //expand down of a node, then check with explored set, if it doesn't exist then we add it to the back of fontier and explored set.		(functional)
	void expand(Node); //we call this before we call expand_<direction>. This is just a series of if statement to check the viable directions we can expand a node. then we call the expand_<directions> based 
					   //whichever if statement they falls into. We can use int a and int b of a Node to check this condition. if a == 2 and b == 2 --> we know that this is the bottom right of the vector.
					   //knowing this we can only expand upward and towards the left.		(functional)

	void print_GH(Node); //		(functional)
	void expand_frontier();//		(functional)
	bool isFrontier(Node);



	//********Testing functions********
	void print_frontier_front();
	void GoalExist();
	void print_solution();
	void print_vector(vector<vector<int>>);
	void print_expanded_size();
	void print_node(Node);  	//print entire state along with g(n), h(n) and total expanded.
	void frontier_update();
};


#endif