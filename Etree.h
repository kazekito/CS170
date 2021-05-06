#ifndef ETREE_H
#define ETREE_H
#include "node.h"

struct Node;

class E_tree {
private:
	Node root;
	vector<Node> goal_vector;
	list<Node> frontier;
	vector<Node> explored;
	vector<vector<vector<int>>> answer;
	int frontier_size;
public:
	E_tree();
	void H_calc(Node*);					//success
	void set_root(Node root);				//success
	void add_frontier(Node);				//success
	void add_explored(Node);				//success
	void add_goal(Node);					//success
	bool isExplored(Node);					//success
	bool compare_goal(Node);				//success	--> check if Node is equivalent to goal state
	bool isFrontier(Node);					//success
	void expand(Node);
	void expand_left(Node);
	void expand_right(Node);
	void expand_up(Node);
	void expand_down(Node);
	Node get_lowestcost();					//success
	void remove_frontier(Node);				//success   --> remove lowest cost from frontier.
	void expand_frontier();
	bool position_checker(double, double, double);	//success
	double position_diff(double, double, double);	//success

	//Testing functions//
	void print_node(Node);
	void goal_exist();	//print solution
	void print_vector(vector<vector<int>>);
	void print_expanded();
	void frontier_update();
};



#endif