#include <iostream>
#include <vector>

using namespace std;

struct Node{
	vector<int> vect; //current state
	vector<Node> child_list;
	int a;  //position of the row
	int b;  //position of the column
	int cost;
	
	
};

class Tree{
	private:
	Node root;
	vector<Node> goal_list; //used to store list of goal states with different costs.
	public:
	
};


int main(){
	
	return 0;
}