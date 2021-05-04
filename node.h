#ifndef NODE_H
#define NODE_H

//#include "node.h"
//#include "node.cpp"
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <cstddef>
#include <stack>
//#include "math.h"
//#include "stdlib.h"
#include <set>

using namespace std;

struct Node;

struct Node {
	Node() {
		paren = vector<vector<vector<int>>>();
		vect = vector<vector<int>>();
		cost = 0;
		Hcost = 0;
		Tcost = 0;
		dir = vector<string>();
		GN = vector<double>();
		HN = vector<double>();
		TN = vector<double>();
	}

	vector<Node> child_list;
	vector<Node> parent_vector;
	vector<int> depth;
	vector<vector<int>> vect; //current state
	int a;  //position of the row
	int b;  //position of the column
	double cost;			//g(n)
	double Hcost;			//h(n)
	double Tcost;			//total cost f(n) = g(n) + h(n);

	//Answer storage
	vector<string> dir;		//list of directions to finish the puzzle.
	vector<vector<vector<int>>> paren;
	vector<double> GN;
	vector<double> HN;
	vector<double> TN;
};


#endif