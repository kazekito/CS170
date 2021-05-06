#include "ucs.h"


Tree::Tree() {
	this->root = Node();
	this->goal_vector = vector<Node>();
	this->frontier = list<Node>();
	this->explored = vector<Node>();
	this->answer = vector<Node>();
	this->goal = 0;
	this->frontier_size = 0;
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


//Add a node to the goal vector, we use the goal vector to check if we found a goal or not.
void Tree::add_goal(Node add) {
	this->goal_vector.push_back(add);
	this->goal = (Node*)& add;
}


void Tree::remove_frontier() {
	this->frontier.pop_front();
}


//check to see if a Node is equivalent to the goal state		(functional)
bool Tree::compare_goal(Node add) {	//check if our Node add is the same as our goal state, if not 
	bool tru = true;
	vector<vector<int>> temp{
		{1,2,3},
		{4,5,6},
		{7,8,0}
	};

	if (add.vect == temp) {
		return true;
	}
	else {
		return false;
	}


	return tru;
}


//Check whether a node is in the frontier set or not		(functional)
bool Tree::isFrontier(Node add) {
	list<Node>::iterator it;
	for (it = this->frontier.begin(); it != this->frontier.end(); ++it) {
		if (it->vect == add.vect) {
			return true;
		}
	}

	return false;
}


//Check whether a node is explored or not		(functional)
bool Tree::isExplored(Node add) {
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


//Expand left and update all neccessary information 		(functional)
void Tree::expand_left(Node add) {
	Node temp = add;
	int a; int b;


	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a).at(temp.b - 1); //get # for position left of blank
	temp.vect.at(temp.a).at(temp.b - 1) = a; //swap blank and # to the left of blank.
	temp.vect.at(temp.a).at(temp.b) = b;

	++temp.cost; //increase cost of our state.
	temp.b = temp.b - 1; //change columns by 1 value to the left/

	//add parent vector
	temp.paren.push_back(add.vect);
	//add direction
	temp.dir.push_back("Move left");
	//add g(n)
	temp.GN.push_back(add.cost);

	if (!isExplored(temp) && !isFrontier(temp)) {
		add_frontier(temp);
	}

}


//Expand up and update all neccessary information 		(functional)
void Tree::expand_up(Node add) {
	Node temp = add;
	int a; int b;
	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a - 1).at(temp.b); //get # for position above blank
	temp.vect.at(temp.a - 1).at(temp.b) = a; //swap blank and # to the above blank.
	temp.vect.at(temp.a).at(temp.b) = b;

	++temp.cost; //increase cost of our state.
	temp.a = temp.a - 1; //change columns by 1 value to the left/

	//add parent vector
	temp.paren.push_back(add.vect);
	//add direction
	temp.dir.push_back("Move up");
	//add g(n)
	temp.GN.push_back(add.cost);

	if (!isExplored(temp) && !isFrontier(temp)) {
		add_frontier(temp);
	}

}


//Expand down and update all neccessary information 		(functional)
void Tree::expand_down(Node add) {
	Node temp = add;
	int a; int b;


	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a + 1).at(temp.b); //get # for position underneath  blank
	temp.vect.at(temp.a + 1).at(temp.b) = a; //swap blank and # to the underneath blank.
	temp.vect.at(temp.a).at(temp.b) = b;

	++temp.cost; //increase cost of our state.
	temp.a = temp.a + 1; //change columns by 1 value to the left/


	//add parent vector
	temp.paren.push_back(add.vect);
	//add direction
	temp.dir.push_back("Move down");
	//add g(n)
	temp.GN.push_back(add.cost);


	if (!isExplored(temp) && !isFrontier(temp)) {
		add_frontier(temp);
	}

}


//Expand right and update all neccessary information 		(functional)
void Tree::expand_right(Node add) {
	Node temp = add;
	int a; int b;


	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a).at(temp.b + 1); //get # for position right of blank
	temp.vect.at(temp.a).at(temp.b + 1) = a; //swap blank and # to the right of blank.
	temp.vect.at(temp.a).at(temp.b) = b;

	temp.cost = temp.cost + 1; //increase cost of our state.
	temp.b = temp.b + 1; //change columns by 1 value to the right/

	//add parent vector
	temp.paren.push_back(add.vect);
	//add direction
	temp.dir.push_back("Move right");
	//add g(n)
	temp.GN.push_back(add.cost);

	if (!isExplored(temp) && !isFrontier(temp)) {
		add_frontier(temp);
	}

}


//Expand node, subset of expand_frontier(), helps determine which path a state should expand based on the position of the white tile.		(functional)
void Tree::expand(Node add) {
	int a = add.a;
	int b = add.b;

	if (compare_goal(add)) {
		add_goal(add);
		if (this->frontier.size() == 1) {
			//this->frontier.front() = Node();
		}
		else {
			//this->frontier.pop_front();
		}
		return;
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
}


//Caller to expand nodes, while solution is not found, expand.		(functional)
void Tree::expand_frontier() {
	while (this->goal_vector.empty()) {
		frontier_update();
		print_frontier_front();
		print_GH(this->frontier.front());
		print_expanded_size();
		expand(this->frontier.front());
		this->frontier.pop_front();
	}
}


//*******************************************************testing purposes ***********************************************************************************************************************


//Print the node in front of the frontier		(functional)
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

//Check whether the goal exist or not		(functional)
void Tree::GoalExist() {
	if (this->goal_vector.empty()) {
		cout << "Goal state does not exist" << endl;
	}
	else {
		cout << "Goal state found\n" << endl;
	}
}


//Print the state movements
//Print the directions to solve the puzzle		(functional)
void Tree::print_solution() {
	Node temp;
	if (!this->goal_vector.empty()) {
		printf("***Solution***\n");
		temp = goal_vector.at(0);
		for (int i = 0; i < temp.paren.size(); ++i) {
			for (int j = 0; j < 3; ++j) {
				printf("{");
				for (int k = 0; k < 3; ++k) {
					printf("%d, ", temp.paren.at(i).at(j).at(k));
				}
				printf("}\n");
			}
			printf("g(n): %d    h(n): %d\n\n", static_cast<int>(temp.GN.at(i)), 0);
		}
		print_vector(temp.vect);
		print_GH(temp);

		printf("***Directions***\n");
		for (int l = 0; l < temp.dir.size(); ++l) {
			cout << temp.dir.at(l) << endl;
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
}


//print explored set's size		(functional)
void Tree::print_expanded_size() {
	if (!this->explored.empty()) {
		cout << "Expanded: " << this->explored.size() << " \n";
	}
	printf("Maximum queue size: %d nodes\n", this->frontier_size);
}

//print g(n) and h(n) of a node.		(functional)
void Tree::print_GH(Node a) {
	printf("g(n): %d    h(n): %d\n\n", static_cast<int>(a.cost), 0);
}

//given a node, print the vector of the node and it's g(n) and h(n) component.		(functional)
void Tree::print_node(Node a) {
	for (int i = 0; i < 3; ++i) {
		printf("{ ");
		for (int j = 0; j < 3; ++j) {
			printf("%d, ", a.vect.at(i).at(j));
		}
		printf("}\n");
	}
	printf("g(n): %d	h(n): %d\n", (int)a.cost, 0);
	cout << endl;
}


void Tree::frontier_update() {
	if (this->frontier_size < this->frontier.size()) {
		this->frontier_size = this->frontier.size();
	}
}