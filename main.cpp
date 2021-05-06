/*
	Name(s): Bao Lam Le, Jessie Lu
	Assignment: Project 1
	Description:
	I acknowledge all content is our own original work
*/

#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm> 
#include "ucs.h"
#include "Etree.h"
//#include "ucs.cpp"
//#include "Etree.cpp"
#include "misplace.h"

using namespace std;

int main() {

	int choice, algorithm, val;
	vector<vector<int>> puzzle{
		{1,2,3},
		{4,8,5},
		{7,0,6}
	};

	misplace* misplace_tree;
	misplace_tree = new misplace();

	E_tree* temp_etree;
	Node temp;
	Tree* temp_tree;
	temp_etree = new E_tree();
	temp_tree = new Tree();

	cout << "Welcome to Bao Lam Le and Jessie Lu 8 puzzle solver.\n"; // replace names with student ID later
	cout << "Type \"1\" to use a default puzzle space, or \"2\" to enter your own puzzle. ";
	cin >> choice;
	cout << endl;

	if (choice == 1) {
		temp.vect = puzzle;			//initializing root node. --> this is representative of the root node.
		temp.a = 2;
		temp.b = 1;
		temp.cost = 0.0;
		temp.Hcost = 0.0;
		temp.Tcost = 0.0;
		temp.paren = vector<vector<vector<int>>>();
	}

	else if (choice != 1) {
		cout << "Enter your puzzle, use a zero to represent the blank\n";
		cout << "Enter the first row, use space between numbers\n";
		cout << "Enter the second row, use space between numbers\n";
		cout << "Enter the third row, use space between numbers\n\n";
		for (int i = 0; i < 3; i++) { // row
			cout << "Row " << (i + 1) << ":\t";
			vector<int> tmpPuz = vector<int>();

			for (int j = 0; j < 3; j++) { // column
				cin >> val;
				puzzle.at(i).at(j) = val;
				if (val == 0) {
					temp.a = i;
					temp.b = j;
				}
			}
		}
		temp.vect = puzzle;
		temp.cost = 0;
		temp.paren = vector<vector<vector<int>>>();


	}

	cout << "\nEnter your choice of algorithm\n";
	cout << "1. Uniform Cost Search\n";
	cout << "2. A* with the Misplaced Tile heuristic\n";
	cout << "3. A* with the Eucledian distance heuristic\n";
	cin >> algorithm;

	if (algorithm == 1) {

		temp_tree->set_root(temp);				//set root node to the tree.
		temp_tree->add_frontier(temp);
		temp_tree->expand_frontier();
		temp_tree->GoalExist();
		temp_tree->print_solution();
		temp_tree->print_expanded_size();

	}
	else if (algorithm == 2) {
		// A* with Misplaced tile
		misplace_tree->set_mroot(temp);
		misplace_tree->calc_misplace(&temp);
		misplace_tree->add_mfrontier(temp);
		misplace_tree->expand_mfrontier();
		misplace_tree->print_mexpanded();
		misplace_tree->print_mfrontier();

	}
	else if (algorithm == 3) {
		temp_etree->set_root(temp);
		temp_etree->H_calc(&temp);
		temp_etree->add_frontier(temp);
		temp_etree->expand_frontier();
		temp_etree->print_expanded();
	}

	return 0;
}