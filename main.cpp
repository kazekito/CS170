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

vector<vector<int>> goal{
	{1,2,3},
	{4,5,6},
	{7,8,0}
};

int main() {
	
	int choice, algorithm, val;
    vector<vector<int>> puzzle;
	Node *temp;
	Tree* temp_tree;
	temp_tree = new Tree();

	cout << "Welcome to Bao Lam Le and Jessie Lu 8 puzzle solver.\n"; // replace names with student ID later
	cout << "Type \"1\" to use a default puzzle space, or \"2\" to enter your own puzzle. ";
	cin >> choice;

	cout << "Enter your puzzle, use a zero to represent the blank\n";
	cout << "Enter the first row, use space or tabs between numbers\n";
	cout << "Enter the second row, use space or tabs between numbers\n";
	cout << "Enter the third row, use space or tabs between numbers\n\n";

    if (choice == 1) {
        // use default puzzle
        vector<int> r1 = {1,2,3};
        vector<int> r2 = {4,8,0};
        vector<int> r3 = {7,6,5};
        puzzle.push_back(r1);
        puzzle.push_back(r2);
        puzzle.push_back(r3);
		
		temp->vect = puzzle;						//initializing root node. --> this is representative of the root node.
		temp->child_list = new vector<Node>();
		temp->a = 1;
		temp->b = 2;
		temp->cost = 0;
		temp->paren = 0;
		
		temp_tree->set_root(temp);				//set root node to the tree.
		temp_tree->add_frontier(*temp);
		temp_tree->expand(*temp);
		Node temp_node = temp_tree->compare_goal();
		temp_tree->trace_goal(&temp_node);
		temp_tree->print_sol();
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
        // Uniform cost search
    }
    else if (algorithm == 2) {
        // A* with Misplaced tile
    }
    else {
        // A* with Eucledian distance
    }

	return 0;
}
