/* 
	Name(s): Bao Lam Le, Jessie Lu
	Assignment: Project 1
	Description:

	I acknowledge all content is our own original work
*/

#include <iostream>
using namespace std;

int main() {
	
	int choice, algorithm;

	cout << "Welcome to Bao Lam Le and Jessie Lu 8 puzzle solver.\n"; // replace names with student ID later
	cout << "Type \"1\" to use a default puzzle space, or \"2\" to enter your own puzzle. ";
	cin >> choice;

	cout << "Enter your puzzle, use a zero to represent the blank\n";
	cout << "Enter the first row, use space or tabs between numbers\n";
	cout << "Enter the second row, use space or tabs between numbers\n";
	cout << "Enter the third row, use space or tabs between numbers\n\n";

	cout << "Enter your choice of algorithm\n";
	cout << "Uniform Cost Search\n";
	cout << "A* with the Misplaced Tile heuristic\n";
	cout << "A* with the Eucledian distance heuristic\n";
	cin >> algorithm;

    

	return 0;
}