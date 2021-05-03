#ifndef MISPLACE_H
#define MISPLACE_H
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include "node.h"

using namespace std;

class misplace {
private:
	Node root;
	vector<Node> goal_vector;
	list<Node> frontier;
	vector<Node> explored;
	vector<vector<vector<int>>> answer;

public:
	misplace();
	void set_root(Node root);
	void add_frontier(Node add);
	void add_explored(Node add);
	void add_goal(Node add);
	bool isExplored(Node);
	bool compare_goal(Node);
	bool isFrontier(Node);
	void expand(Node);
	void expand_left(Node*);
	void expand_right(Node*);
	void expand_up(Node*);
	void expand_down(Node*);
	Node get_lowestcost();
	void remove_frontier(Node);
	void calc_misplace(Node*);
	void expand_frontier();
	bool position_checker(double, double, double);

	//Testing functions//
	void print_T(Node);
	void print();
	void print_node(Node);
	void goal_exist();
	void print_directions();
	void print_vector(vector<vector<int>>);
};

#endif