/* 
	Name(s): Bao Lam Le, Jessie Lu
	Assignment: Project 1
	Description:
	I acknowledge all content is our own original work
*/
#include "ucs.h"
#include "ucs.cpp"
#include "Etree.cpp"
#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm> 
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


int main() {
	
	string line1,line2,line3;
	char *char1,*char2,*char3,*char4,*char5,*char6,*char7,*char8,*char9;
	int choice, algorithm, val;
    vector<vector<int>> puzzle{
	//	{1,2,3},
	//	{4,5,6},
	//	{7,8,0}
		
		{1,2,5},
		{8,0,6},
		{7,3,4}
	};
	
	vector<vector<int>> puzzle1{
		{1,2,5},
		{8,4,6},
		{7,3,0}
	};
	

	E_tree* temp_etree;
	Node temp;
	Tree* temp_tree;
	temp_etree = new E_tree();
	temp_tree = new Tree();

	cout << "Welcome to Bao Lam Le and Jessie Lu 8 puzzle solver.\n"; // replace names with student ID later
	cout << "Type \"1\" to use a default puzzle space, or \"2\" to enter your own puzzle. ";
	cin >> choice;
	/*
	cout << "Enter your puzzle, use a zero to represent the blank\n";
	cout << "Enter the first row, use space or tabs between numbers\n";
	cout << "Enter the second row, use space or tabs between numbers\n";
	cout << "Enter the third row, use space or tabs between numbers\n\n";
	*/

    if (choice == 1) {
		temp.vect = puzzle;			//initializing root node. --> this is representative of the root node.
		temp.child_list = vector<Node>();
		temp.a = 2;
		temp.b = 0;
		temp.cost = 0.0;
		temp.Hcost = 0.0;
		temp.Tcost = 0.0;
		temp.paren = vector<vector<vector<int>>>();
    }
	
    else if (choice != 1){
		for (int i = 0; i < 3; i++) { // row
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
		temp.child_list = vector<Node>();
		temp.cost = 0;
		temp.paren = vector<vector<vector<int>>>();
	
		
    }

	cout << "Enter your choice of algorithm\n";
	cout << "1. Uniform Cost Search\n";
	cout << "2. A* with the Misplaced Tile heuristic\n";
	cout << "3. A* with the Eucledian distance heuristic\n";
	cin >> algorithm;

    if (algorithm == 1){
		
        temp_tree->set_root(temp);				//set root node to the tree.
		temp_tree->add_frontier(temp);
		temp_tree->expand_frontier();
		temp_tree->GoalExist();
		temp_tree->print_goal_cost();
		temp_tree->print_solution();
		
    }
    else if (algorithm == 2) {
        // A* with Misplaced tile
    }
    else if (algorithm == 3){
       temp_etree->set_root(temp);
	   temp_etree->H_calc(&temp);
	   temp_etree->add_frontier(temp);
	   temp_etree->expand_frontier();
	   //temp_etree->print_T(temp);
	   //temp_etree->print();
	   Node temp1 = temp;
	   temp1.vect = puzzle1;
	   temp1.Tcost = 7;
	   Node temp2 = temp;
	   temp2.Tcost = 9;
	   temp_etree->add_frontier(temp1);
	   temp_etree->add_frontier(temp2);
	   temp_etree->isFrontier(temp1);
	   printf("Node cost returned : %f\n",temp_etree->get_lowestcost().Tcost);
	   temp_etree->remove_frontier(temp_etree->get_lowestcost());
	   printf("Node cost returned : %f\n",temp_etree->get_lowestcost().Tcost);
    }

	return 0;
}
