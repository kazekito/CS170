
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
using namespace std;

vector<vector<int>> goal{
	{1,2,3},
	{4,5,6},
	{7,8,0}
};

struct Node{
	vector<int> vect; //current state
	vector<Node> child_list;
	int a;  //position of the row
	int b;  //position of the column
	int cost;
	
	
};

class Tree{
	private:
	Node root; //root node used to expand
	vector<Node> goal_vector; //used to store list of goal states with different costs.
	list<Node> frontier; //we access the front of the list and pops the front. we add elements to the end of the list (push_back)
	vector<Node> explored; //add elements but don't remove them.
	public:
	Tree();
	void set_root(Node root);
	void add_frontier(Node add); //add an element to frontier
	void add_explored(Node add); //add an element to explored
	void add_goal(Node add); //add an element to goal vector.
	void remove_frontier(); //remove the front element of the frontier
	bool compare_goal(Node); //compare a node with goal state, return true if it is the goal.
	bool isExplored(Node); //check to see if a Node is already in explored, if it is we ignore it. return true if it is in explored set.
	void expand_left(Node); //expand left of a node, then check with explored set, if it doesn't exist then we add it to the back of fontier and explored set. if it already exist in explored set, we don't add it.
	void expand_right(Node); //expand right of a node, then check with explored set, if it doesn't exist then we add it to the back of fontier and explored set.
	void expand_up(Node); //expand up of a node, then check with explored set, if it doesn't exist then we add it to the back of fontier and explored set.
	void expand_down(Node); //expand down of a node, then check with explored set, if it doesn't exist then we add it to the back of fontier and explored set.
	void expand(Node); //we call this before we call expand_<direction>. This is just a series of if statement to check the viable directions we can expand a node. then we call the expand_<directions> based 
					   //whichever if statement they falls into. We can use int a and int b of a Node to check this condition. if a == 2 and b == 2 --> we know that this is the bottom right of the vector.
					   //knowing this we can only expand upward and towards the left.
					   
	
};

int main() {
	
	int choice, algorithm, val;
    vector<vector<int>> puzzle;

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