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
	void set_mroot(Node root);
	void add_mfrontier(Node add);
	void add_mexplored(Node add);
	void add_mgoal(Node add);
	bool ismExplored(Node);
	bool mcompare_goal(Node);
	bool ismFrontier(Node);
	void mexpand(Node);
	void mexpand_left(Node);
	void mexpand_right(Node);
	void mexpand_up(Node);
	void mexpand_down(Node);
	Node get_mlowestcost();
	void remove_mfrontier(Node);
	void calc_misplace(Node*);
	void expand_mfrontier();
	bool mposition_checker(double, double, double);

	//Testing functions//
	void print_node(Node);
	void goal_exist();
	void print_vector(vector<vector<int>>);
	void print_mexpanded();
	void print_mfrontier();
};

#endif