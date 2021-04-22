/* 
	Name(s): Bao Lam Le, Jessie Lu
	Assignment: Project 1
	Description:
	I acknowledge all content is our own original work
*/
#include "ucs.h"
#include "ucs.cpp"
#include <iostream>
#include <list>
#include <iterator>
#include <vector>
using namespace std;


int main() {
	
	int choice, algorithm, val;
    vector<vector<int>> puzzle{
		{2,0,3},
		{1,8,5},
		{4,7,6}
	};
	
	/*
	vector<vector<int>> goal{
		{1,2,3},
		{4,0,6},
		{7,8,0}
	};
	Node goal_temp;
	*/
	
	Node temp;
	Tree* temp_tree;
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
        // use default puzzle
		/*
        vector<int> r1 = {1,2,3};
        vector<int> r2 = {4,8,0};
        vector<int> r3 = {7,6,5};
        puzzle.push_back(r1);
        puzzle.push_back(r2);
        puzzle.push_back(r3);
		*/
		
		temp.set_vect(puzzle);						//initializing root node. --> this is representative of the root node.
		temp.child_list = new vector<Node>();
		temp.a = 0;
		temp.b = 1;
		temp.cost = 0;
		temp.paren = 0;
		
		//goal_temp.vect = goal;
    }
	
    else {
        // enter own 8 puzzle
        for (int i = 0; i < 3; i++) { // row
            vector<int> tmpPuz; 

            for (int j = 0; j < 3; j++) { // column
            cin >> val;
                tmpPuz.push_back(val); // 1D puzzle
            }
            puzzle.push_back(tmpPuz); // creates 2D puzzle
        }
    }

	cout << "Enter your choice of algorithm\n";
	cout << "1. Uniform Cost Search\n";
	cout << "2. A* with the Misplaced Tile heuristic\n";
	cout << "3. A* with the Eucledian distance heuristic\n";
	cin >> algorithm;

    if (algorithm == 1){
		
        temp_tree->set_root(temp);				//set root node to the tree.
		temp_tree->add_frontier(temp);
		temp_tree->print_frontier_front();
		temp_tree->expand_frontier();
		temp_tree->GoalExist();
		
    }
    else if (algorithm == 2) {
        // A* with Misplaced tile
    }
    else {
        // A* with Eucledian distance
    }

	return 0;
}
