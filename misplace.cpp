#include "misplace.h"


misplace::misplace() {
	this->root = Node();
	this->goal_vector = vector<Node>();
	this->frontier = list<Node>();
	this->explored = vector<Node>();
}


void misplace::set_mroot(Node add) {
	this->root = add;
}

void misplace::add_mfrontier(Node add) {
	this->frontier.push_back(add);
}

void misplace::add_mexplored(Node add) {
	this->explored.push_back(add);
}

void misplace::add_mgoal(Node add) {
	this->goal_vector.push_back(add);
}

bool misplace::mcompare_goal(Node add) {

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
}

bool misplace::ismExplored(Node add) {

	if (this->explored.empty()) {
		return false;
	}
	else {
		for (int i = 0; i < this->explored.size(); ++i) {
			if (this->explored.at(i).vect == add.vect) {
				return true;
			}
		}
		return false;
	}
}

bool misplace::ismFrontier(Node add) {

	list<Node>::iterator it;
	for (it = this->frontier.begin(); it != this->frontier.end(); ++it) {
		if (it->vect == add.vect) {
			return true;
		}
	}
	return false;
}

void misplace::remove_mfrontier(Node add) {
	list<Node>::iterator it;
	for (it = this->frontier.begin(); it != this->frontier.end(); ++it) {
		if (it->vect == add.vect) {
			this->frontier.erase(it);
			return;
		}
	}
	return;
}

void misplace::mexpand_left(Node add) {
	Node temp = add;
	int a;
	int b;

	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a).at(temp.b - 1); //get # for position left of blank
	temp.vect.at(temp.a).at(temp.b - 1) = a; //swap blank and # to the left of blank.
	temp.vect.at(temp.a).at(temp.b) = b;

	temp.b = temp.b - 1; //change columns by 1 value to the left/

	++temp.cost;
	//temp.child_list = vector<Node>();  //initalize an empty child list for our newly expanded set.
	//add.child_list.push_back(temp);

	//temp.paren.push_back(add.vect);
	//temp.parent_vector.push_back(add);

	temp.dir.push_back("Move left");
	temp.depth.push_back(temp.cost);
	calc_misplace(&temp);

	if (!ismExplored(temp) && !ismFrontier(temp)) {
		add_mfrontier(temp);
	}

}

void misplace::mexpand_right(Node add) {
	Node temp = add;
	int a;
	int b;

	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a).at(temp.b + 1); //get # for position right of blank
	temp.vect.at(temp.a).at(temp.b + 1) = a; //swap blank and # to the right of blank.
	temp.vect.at(temp.a).at(temp.b) = b;

	temp.b = temp.b + 1; //change columns by 1 value to the right

	++temp.cost;
	//temp.child_list = vector<Node>();  //initalize an empty child list for our newly expanded set.
	//add.child_list.push_back(temp);	//add this node to add's child list.

	//temp.paren.push_back(add.vect);
	//temp.parent_vector.push_back(add);

	temp.dir.push_back("Move right");
	temp.depth.push_back(temp.cost);
	calc_misplace(&temp);

	if (!ismExplored(temp) && !ismFrontier(temp)) {
		add_mfrontier(temp);
	}
}

void misplace::mexpand_up(Node add) {
	Node temp = add;
	int a;
	int b;

	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a - 1).at(temp.b); //get # for position above blank
	temp.vect.at(temp.a - 1).at(temp.b) = a; //swap blank and # to the above blank.
	temp.vect.at(temp.a).at(temp.b) = b;

	temp.a = temp.a - 1; //change columns by 1 value to the left

	++temp.cost;
	//temp.child_list = vector<Node>();  //initalize an empty child list for our newly expanded set.
	//add.child_list.push_back(temp);

	//temp.paren.push_back(add.vect);
	//temp.parent_vector.push_back(add);

	temp.dir.push_back("Move up");
	temp.depth.push_back(temp.cost);
	calc_misplace(&temp);

	if (!ismExplored(temp) && !ismFrontier(temp)) {
		add_mfrontier(temp);
	}
}

void misplace::mexpand_down(Node add) {
	Node temp = add;
	int a;
	int b;

	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a + 1).at(temp.b); //get # for position underneath  blank
	temp.vect.at(temp.a + 1).at(temp.b) = a; //swap blank and # to the underneath blank.
	temp.vect.at(temp.a).at(temp.b) = b;

	temp.a = temp.a + 1; //change columns by 1 value to the left

	++temp.cost;
	//temp.child_list = vector<Node>();  //initalize an empty child list for our newly expanded set.
	//add.child_list.push_back(temp);

	//temp.paren.push_back(add.vect);
	//temp.parent_vector.push_back(add);

	temp.dir.push_back("Move down");
	temp.depth.push_back(temp.cost);
	calc_misplace(&temp);

	if (!ismExplored(temp) && !ismFrontier(temp)) {
		add_mfrontier(temp);
	}

}

void misplace::mexpand(Node a) {
	int tempa = a.a;
	int tempb = a.b;

	if (mcompare_goal(a)) {
		add_mgoal(a);
		if (this->frontier.size() == 1) {
			this->frontier.front() = Node();
		}

	}
	else if (!ismExplored(a) && !mcompare_goal(a)) {
		if (tempa == 0 && tempb == 0) { //blank is at top left corner.
			add_mexplored(a);
			mexpand_right(a);
			mexpand_down(a);
		}
		else if (tempa == 0 && tempb == 1) { //blank is at the top corner
			add_mexplored(a);
			mexpand_right(a);
			mexpand_down(a);
			mexpand_left(a);
		}
		else if (tempa == 0 && tempb == 2) { //blank is at top right corner
			add_mexplored(a);
			mexpand_left(a);
			mexpand_down(a);
		}
		else if (tempb == 0 && tempa == 1) { //blank is at the left corner.
			add_mexplored(a);
			mexpand_right(a);
			mexpand_up(a);
			mexpand_down(a);
		}
		else if (tempb == 0 && tempa == 2) {  //blank is at the bottom left
			add_mexplored(a);
			mexpand_up(a);
			mexpand_right(a);
		}
		else if (tempa == 2 && tempb == 1) { //blank is at the bottom corner
			add_mexplored(a);
			mexpand_up(a);
			mexpand_left(a);
			mexpand_right(a);
		}
		else if (tempa == 2 && tempb == 2) { //bottom right corner.
			add_mexplored(a);
			mexpand_up(a);
			mexpand_left(a);
		}
		else if (tempb == 2 && tempa == 1) { //right corner.
			add_mexplored(a);
			mexpand_left(a);
			mexpand_up(a);
			mexpand_down(a);
		}
		else if (tempb == 1 && tempa == 1) {
			add_mexplored(a);
			mexpand_left(a);
			mexpand_right(a);
			mexpand_up(a);
			mexpand_down(a);
		}
	}

	remove_mfrontier(a);
}

void misplace::expand_mfrontier() {
	while (this->goal_vector.empty()) {

		print_node(get_mlowestcost());
		mexpand(get_mlowestcost());
		goal_exist();
	}
}

Node misplace::get_mlowestcost() {

	list<Node>::iterator it;
	Node temp;
	temp = frontier.front();
	for (it = this->frontier.begin(); it != this->frontier.end(); ++it) {
		if (it->Tcost < temp.Tcost) {
			temp = *it;
		}
	}
	return temp;
}

bool misplace::mposition_checker(double value, double i, double j) {

	// check if value matches one from goal state
	if (value == 1 && i == 0 && j == 0) {
		return true;
	}
	else if (value == 2 && i == 0 && j == 1) {
		return true;
	}
	else if (value == 3 && i == 0 && j == 2) {
		return true;
	}
	else if (value == 4 && i == 1 && j == 0) {
		return true;
	}
	else if (value == 5 && i == 1 && j == 1) {
		return true;
	}
	else if (value == 6 && i == 1 && j == 2) {
		return true;
	}
	else if ((value == 7 && i == 2 && j == 0)) {
		return true;
	}
	else if (value == 8 && i == 2 && j == 1) {
		return true;
	}
	else if (value == 0 && i == 2 && j == 2) {
		return true;
	}
	else {
		return false;
	}

	return false;
}

void misplace::calc_misplace(Node* a) {
	int count = 0;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (!mposition_checker(a->vect.at(i).at(j), i, j)) {
				count = count + 1;
			}
		}
	}
	a->Hcost = count;
	a->Tcost = a->cost + count;
}

void misplace::goal_exist() {
	if (!this->goal_vector.empty()) {
		cout << "Goal!\n" << endl;
		cout << "\n Solution \n";
		Node temp = this->goal_vector.at(0);
		for (int i = 0; i < temp.paren.size(); ++i) {
			print_vector(temp.paren.at(i));
			cout << "g(n): " << temp.GN.at(i) << "\t h(n): " << temp.HN.at(i) << "\t f(n): " << temp.TN.at(i);
		}
		print_vector(temp.vect);
		cout << "g(n): " << temp.cost << "\t h(n): " << temp.Hcost << "\t f(n): " << temp.Tcost;

		cout << "\n Directions \n";
		for (int j = 0; j < temp.dir.size(); ++j) {
			cout << temp.dir.at(j) << endl;
		}
	}
}

void misplace::print_vector(vector<vector<int>> a) {
	for (int i = 0; i < 3; i++) {
		cout << "{ ";
		for (int j = 0; j < 3; j++) {
			cout << a.at(i).at(j) << ", ";
		}
		cout << "}\n";
	}
	cout << endl;
}


void misplace::print_node(Node a) {
	for (int i = 0; i < 3; ++i) {
		cout << "{ ";
		for (int j = 0; j < 3; ++j) {
			cout << a.vect.at(i).at(j) << ", ";
		}
		cout << "}" << endl;
	}
	cout << endl;
	cout << "g(n): " << a.cost << "\t h(n): " << a.Hcost << "\t f(n): " << a.Tcost << endl;
}

void misplace::print_mexpanded() {
	cout << "Nodes expanded: " << this->explored.size() << endl;
}

void misplace::print_mfrontier() {
	cout << "Max queue size: " << this->frontier.size() + 1 << endl;
}