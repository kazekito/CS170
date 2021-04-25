#include "misplaced.h"

Node::Node() {
	paren = vector<vector<vector<int>>>();
	vect = vector<vector<int>>();

}
Tree::Tree() {
	this->root = Node();
	this->goal_vector = vector<Node>();
	this->frontier = list<Node>();
	this->explored = vector<Node>();
}
void Tree::set_root(Node a) {
	this->root = a;
}

void Tree::add_frontier(Node add) {
	this->frontier.push_back(add);
}

void Tree::add_explored(Node add) {
	this->explored.push_back(add);
}

void Tree::add_goal(Node add) {
	this->goal_vector.push_back(add);
}

void Tree::remove_frontier() {
	this->frontier.pop_front();
}


bool Tree::compare_goal(Node add) {	//check if our Node add is the same as our goal state, if not 
	bool tru = true;
	vector<vector<int>> temp{
		{1,2,3},
		{4,5,6},
		{7,8,0}
	};

	misplace = 0;

	if (add.vect == temp) {
		add.tile.push_back(misplace);
		return true;
	}
	else {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (temp.at(i).at(j) != add.vect.at(i).at(j)) {
					misplace++;
				}
			}
		}
		add.tile.push_back(misplace);
		return false;
	}

	return tru;
}

bool Tree::isExplored(Node add) { //execute compare add through our explored set. the logic is that if it is true, then tru = true. if it doesn't match, tru = false for the rest of the comparison. 
	bool temp = true;
	if (this->explored.empty()) {
		temp = false;
	}
	else {
		for (int i = 0; i < this->explored.size(); ++i) {
			if (this->explored.at(i).vect == add.vect) {
				return true;
			}
		}
		temp = false;
	}

	return temp;
}

void Tree::expand_left(Node& add) {
	Node temp = add;
	int a; int b;
	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a).at(temp.b - 1); //get # for position left of blank
	temp.vect.at(temp.a).at(temp.b - 1) = a; //swap blank and # to the left of blank.
	temp.vect.at(temp.a).at(temp.b) = b;

	//++temp.cost; //increase cost of our state.
	//temp.cost = misplace + depth;
	temp.b = temp.b - 1; //change columns by 1 value to the left/
	temp.child_list = vector<Node>();  //initalize an empty child list for our newly expanded set.

	add.child_list.push_back(temp);
	temp.paren.push_back(add.vect);

	temp.dir.push_back("Move left");
	temp.tile.push_back(misplace);
	temp.dep.push_back(depth);

	if (compare_goal(temp)) {
		add_goal(temp);
	}

	if (!isExplored(temp)) {
		add_frontier(temp);
	}

}

void Tree::expand_up(Node& add) {
	Node temp = add;
	int a; int b;
	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a - 1).at(temp.b); //get # for position above blank
	temp.vect.at(temp.a - 1).at(temp.b) = a; //swap blank and # to the above blank.
	temp.vect.at(temp.a).at(temp.b) = b;

	++temp.cost; //increase cost of our state.
	temp.a = temp.a - 1; //change columns by 1 value to the left/
	temp.child_list = vector<Node>();  //initalize an empty child list for our newly expanded set.

	add.child_list.push_back(temp);
	temp.paren.push_back(add.vect);
	temp.tile.push_back(misplace);
	temp.dir.push_back("Move up");
	temp.dep.push_back(depth);

	if (compare_goal(temp)) {
		add_goal(temp);
	}

	if (!isExplored(temp)) {
		add_frontier(temp);
	}

}

void Tree::expand_down(Node& add) {
	Node temp = add;
	int a; int b;
	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a + 1).at(temp.b); //get # for position underneath  blank
	temp.vect.at(temp.a + 1).at(temp.b) = a; //swap blank and # to the underneath blank.
	temp.vect.at(temp.a).at(temp.b) = b;

	++temp.cost; //increase cost of our state.
	temp.a = temp.a + 1; //change columns by 1 value to the left/
	temp.child_list = vector<Node>();  //initalize an empty child list for our newly expanded set.

	add.child_list.push_back(temp);
	temp.paren.push_back(add.vect);
	temp.dir.push_back("Move down");
	temp.tile.push_back(misplace);
	temp.dep.push_back(depth);


	if (compare_goal(temp)) {
		add_goal(temp);
	}

	if (!isExplored(temp)) {
		add_frontier(temp);
	}

}

void Tree::expand_right(Node& add) {
	Node temp = add;
	int a; int b;
	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a).at(temp.b + 1); //get # for position right of blank
	temp.vect.at(temp.a).at(temp.b + 1) = a; //swap blank and # to the right of blank.
	temp.vect.at(temp.a).at(temp.b) = b;

	++temp.cost; //increase cost of our state.
	temp.b = temp.b + 1; //change columns by 1 value to the right/
	temp.child_list = vector<Node>();  //initalize an empty child list for our newly expanded set.

	add.child_list.push_back(temp);
	temp.paren.push_back(add.vect);
	temp.dir.push_back("Move right");
	temp.tile.push_back(misplace);
	temp.dep.push_back(depth);

	if (compare_goal(temp)) {
		add_goal(temp);
	}

	if (!isExplored(temp)) {
		add_frontier(temp);
	}

}

void Tree::expand(Node add) {
	int a = add.a;
	int b = add.b;
	if (compare_goal(add)) {
		add_goal(add);
		if (this->frontier.size() == 1) {
			this->frontier.front() = Node();
		}
		else {
			this->frontier.pop_front();
		}
	}
	else if (!isExplored(add) && !compare_goal(add)) {
		if (a == 0 && b == 0) { //blank is at top left corner.
			add_explored(add);
			expand_right(add);
			expand_down(add);
		}
		else if (a == 0 && b == 1) { //blank is at the top corner
			add_explored(add);
			expand_right(add);
			expand_down(add);
			expand_left(add);
		}
		else if (a == 0 && b == 2) { //blank is at top right corner
			add_explored(add);
			expand_left(add);
			expand_down(add);
		}
		else if (b == 0 && a == 1) { //blank is at the left corner.
			add_explored(add);
			expand_right(add);
			expand_up(add);
			expand_down(add);
		}
		else if (b == 0 && a == 2) {  //blank is at the bottom left
			add_explored(add);
			expand_up(add);
			expand_right(add);
		}
		else if (a == 2 && b == 1) { //blank is at the bottom corner
			add_explored(add);
			expand_up(add);
			expand_left(add);
			expand_right(add);
		}
		else if (a == 2 & b == 2) { //bottom right corner.
			add_explored(add);
			expand_up(add);
			expand_left(add);
		}
		else if (b == 2 && a == 1) { //right corner.
			add_explored(add);
			expand_left(add);
			expand_up(add);
			expand_down(add);
		}
		else if (b == 1 && a == 1) {
			add_explored(add);
			expand_left(add);
			expand_right(add);
			expand_up(add);
			expand_down(add);
		}
	}
	depth++;
	this->frontier.pop_front();
}

void Tree::expand_frontier() {
	while (this->goal_vector.empty()) {
		print_frontier_front();
		print_frontier_size();
		print_expanded_size();
		expand(this->frontier.front());
	}
}


//*******************************************************testing purposes ***********************************************************************************************************************

void Tree::print_frontier_front() {
	if (!this->frontier.empty()) {
		for (int i = 0; i < 3; ++i) {
			cout << "{ ";
			for (int j = 0; j < 3; ++j) {
				cout << this->frontier.front().vect.at(i).at(j) << ", ";
			}
			cout << "}\n";
		}
	}

	cout << endl;
}

void Tree::GoalExist() {
	if (this->goal_vector.empty()) {
		cout << "NO" << endl;
	}
	else {
		cout << "YES" << endl;
	}
}

void Tree::print_goal_cost() {
	if (!this->goal_vector.empty()) {
		printf("Goal cost %d\n", this->goal_vector.at(0).cost);
	}
}


void Tree::print_solution() {
	cout << "Solution: " << endl;
	Node temp;
	if (!this->goal_vector.empty()) {
		temp = goal_vector.at(0);
		for (int i = 0; i < temp.paren.size(); ++i) {
			// keep track of depth and misplace			depth doesn't exactly work
			cout << "The best state to expand with g(n) = " << temp.dep.at(i) << " and h(n) = " << temp.tile.at(i) << endl; 
			print_vector(temp.paren.at(i));
		}
		print_vector(temp.vect);
		cout << "Directions\n";
		print_vector(this->root.vect);
		for (int j = 0; j < temp.dir.size(); ++j) {
			cout << temp.dir.at(j) << endl;
		}
	}


}


void Tree::print_vector(vector<vector<int>> add) {
	for (int i = 0; i < 3; ++i) {
		cout << "{ ";
		for (int j = 0; j < 3; ++j) {
			cout << add.at(i).at(j) << ", ";
		}
		cout << "}\n";
	}
	cout << "\n";
}

void Tree::print_frontier_size() {
	if (!this->frontier.empty()) {
		cout << "Frontier: " << this->frontier.size() << " ";
	}
}

void Tree::print_expanded_size() {
	if (!this->explored.empty()) {
		cout << "Expanded: " << this->explored.size() << " \n";
	}
}
