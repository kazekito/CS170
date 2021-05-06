#include "Etree.h"

E_tree::E_tree() {
	this->root = Node();
	this->goal_vector = vector<Node>();
	this->frontier = list<Node>();
	this->explored = vector<Node>();
	this->frontier_size = 0;
}


void E_tree::set_root(Node a) {
	this->root = a;
}


void E_tree::add_frontier(Node a) {
	this->frontier.push_back(a);
}


void E_tree::add_explored(Node a) {
	this->explored.push_back(a);
}


void E_tree::add_goal(Node a) {
	this->goal_vector.push_back(a);
}


bool E_tree::compare_goal(Node a) {
	bool tru = true;
	vector<vector<int>> temp{
		{1,2,3},
		{4,5,6},
		{7,8,0}
	};

	if (a.vect == temp) {
		return true;
	}
	else {
		return false;
	}


	return tru;

}


bool E_tree::isExplored(Node a) {
	bool temp = true;
	if (this->explored.empty()) {
		temp = false;
	}
	else {
		for (int i = 0; i < this->explored.size(); ++i) {
			if (this->explored.at(i).vect == a.vect) {
				return true;
			}
		}
		temp = false;
	}

	return temp;
}


bool E_tree::isFrontier(Node a) {
	list<Node>::iterator it;
	for (it = this->frontier.begin(); it != this->frontier.end(); ++it) {
		if (it->vect == a.vect) {
			return true;
		}
	}

	return false;
}


Node E_tree::get_lowestcost() {
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


void E_tree::remove_frontier(Node a) {
	list<Node>::iterator it;
	for (it = this->frontier.begin(); it != this->frontier.end(); ++it) {
		if (it->vect == a.vect) {
			this->frontier.erase(it);
			return;
		}
	}

	return;
}


void E_tree::expand_left(Node add) {
	Node temp = add;
	int a; int b;
	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a).at(temp.b - 1); //get # for position left of blank
	temp.vect.at(temp.a).at(temp.b - 1) = a; //swap blank and # to the left of blank.
	temp.vect.at(temp.a).at(temp.b) = b;

	++temp.cost; //increase cost of our state.
	temp.b = temp.b - 1; //change columns by 1 value to the left/

	H_calc(&temp);

	temp.paren.push_back(add.vect);
	temp.dir.push_back("Move left");
	temp.GN.push_back(add.cost);
	temp.HN.push_back(add.Hcost);
	temp.TN.push_back(add.Tcost);


	if (!isExplored(temp) && !isFrontier(temp)) {
		add_frontier(temp);
	}

}

void E_tree::expand_right(Node add) {
	Node temp = add;
	int a;
	int b;

	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a).at(temp.b + 1); //get # for position right of blank
	temp.vect.at(temp.a).at(temp.b + 1) = a; //swap blank and # to the right of blank.
	temp.vect.at(temp.a).at(temp.b) = b;
	++temp.cost;
	temp.b = temp.b + 1; //change columns by 1 value to the right/

	H_calc(&temp);

	temp.paren.push_back(add.vect);
	temp.dir.push_back("Move right");
	temp.GN.push_back(add.cost);
	temp.HN.push_back(add.Hcost);
	temp.TN.push_back(add.Tcost);

	if (!isExplored(temp) && !isFrontier(temp)) {
		add_frontier(temp);
	}
}

void E_tree::expand_up(Node add) {
	Node temp = add;
	int a; int b;
	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a - 1).at(temp.b); //get # for position above blank
	temp.vect.at(temp.a - 1).at(temp.b) = a; //swap blank and # to the above blank.
	temp.vect.at(temp.a).at(temp.b) = b;

	++temp.cost; //increase cost of our state.
	temp.a = temp.a - 1; //change columns by 1 value to the left/

	H_calc(&temp);

	temp.paren.push_back(add.vect);
	temp.dir.push_back("Move up");
	temp.GN.push_back(add.cost);
	temp.HN.push_back(add.Hcost);
	temp.TN.push_back(add.Tcost);

	if (!isExplored(temp) && !isFrontier(temp)) {
		add_frontier(temp);
	}
}

void E_tree::expand_down(Node add) {
	Node temp = add;
	int a; int b;
	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a + 1).at(temp.b); //get # for position underneath  blank
	temp.vect.at(temp.a + 1).at(temp.b) = a; //swap blank and # to the underneath blank.
	temp.vect.at(temp.a).at(temp.b) = b;

	++temp.cost; //increase cost of our state.
	temp.a = temp.a + 1; //change columns by 1 value to the left/

	H_calc(&temp);

	temp.paren.push_back(add.vect);
	temp.dir.push_back("Move down");
	temp.GN.push_back(add.cost);
	temp.HN.push_back(add.Hcost);
	temp.TN.push_back(add.Tcost);

	if (!isExplored(temp) && !isFrontier(temp)) {
		add_frontier(temp);
	}

}

void E_tree::expand(Node a) {
	int tempa = a.a;
	int tempb = a.b;

	if (compare_goal(a)) {
		add_goal(a);
		if (this->frontier.size() == 1) {
			this->frontier.front() = Node();
		}
		else {
			//remove_frontier(a);
		}
	}
	else if (!isExplored(a) && !compare_goal(a)) {
		if (tempa == 0 && tempb == 0) { //blank is at top left corner.
			add_explored(a);
			expand_right(a);
			expand_down(a);
		}
		else if (tempa == 0 && tempb == 1) { //blank is at the top corner
			add_explored(a);
			expand_right(a);
			expand_down(a);
			expand_left(a);
		}
		else if (tempa == 0 && tempb == 2) { //blank is at top right corner
			add_explored(a);
			expand_left(a);
			expand_down(a);
		}
		else if (tempb == 0 && tempa == 1) { //blank is at the left corner.
			add_explored(a);
			expand_right(a);
			expand_up(a);
			expand_down(a);
		}
		else if (tempb == 0 && tempa == 2) {  //blank is at the bottom left
			add_explored(a);
			expand_up(a);
			expand_right(a);
		}
		else if (tempa == 2 && tempb == 1) { //blank is at the bottom corner
			add_explored(a);
			expand_up(a);
			expand_left(a);
			expand_right(a);
		}
		else if (tempa == 2 & tempb == 2) { //bottom right corner.
			add_explored(a);
			expand_up(a);
			expand_left(a);
		}
		else if (tempb == 2 && tempa == 1) { //right corner.
			add_explored(a);
			expand_left(a);
			expand_up(a);
			expand_down(a);
		}
		else if (tempb == 1 && tempa == 1) {
			add_explored(a);
			expand_left(a);
			expand_right(a);
			expand_up(a);
			expand_down(a);
		}
	}

	remove_frontier(a);
}

void E_tree::expand_frontier() {
	while (this->goal_vector.empty()) {
		frontier_update();
		print_node(get_lowestcost());
		expand(get_lowestcost());
		goal_exist();
	}
}

bool E_tree::position_checker(double value, double i, double j) {

	if (value == 1 && i == 0.0 && j == 0.0) {
		//printf("Value %f is true\n",value);
		return true;
	}
	else if (value == 2 && i == 0.0 && j == 1.0) {
		return true;
	}
	else if (value == 3 && i == 0.0 && j == 2.0) {
		return true;
	}
	else if (value == 4 && i == 1.0 && j == 0.0) {
		return true;
	}
	else if (value == 5 && i == 1.0 && j == 1.0) {
		return true;
	}
	else if (value == 6 && i == 1.0 && j == 2.0) {
		return true;
	}
	else if ((value == 7.0 && i == 2.0 && j == 0.0)) {
		return true;
	}
	else if (value == 8 && i == 2.0 && j == 1.0) {
		return true;
	}
	else if (value == 0 && i == 2.0 && j == 2.0) {
		return true;
	}
	else {
		return false;
	}

	return false;
}

double E_tree::position_diff(double value, double i, double j) {
	double temp_i;
	double temp_j;
	double j_diff;
	double i_diff;
	double answer;
	double temp;

	if (value == 0.0) {
		temp_i = 2.0;
		temp_j = 2.0;
	}
	else if (value == 1.0) {
		temp_i = 0.0;
		temp_j = 0.0;
	}
	else if (value == 2.0) {
		temp_i = 0.0;
		temp_j = 1.0;
	}
	else if (value == 3.0) {
		temp_i = 0.0;
		temp_j = 2.0;
	}
	else if (value == 4.0) {
		temp_i = 1.0;
		temp_j = 0.0;
	}
	else if (value == 5.0) {
		temp_i = 1.0;
		temp_j = 1.0;
	}
	else if (value == 6.0) {
		temp_i = 1.0;
		temp_j = 2.0;
	}
	else if (value == 7) {
		temp_i = 2.0;
		temp_j = 0.0;
	}
	else if (value == 8.0) {
		temp_i = 2.0;
		temp_j = 1.0;
	}

	i_diff = abs(temp_i - i);
	j_diff = abs(temp_j - j);

	temp = pow(i_diff, 2) + pow(j_diff, 2);
	answer = sqrt(temp);

	return answer;
}

void E_tree::H_calc(Node* a) {

	double count = 0.0;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (!position_checker(a->vect.at(i).at(j), i, j)) {
				count = count + position_diff(a->vect.at(i).at(j), i, j);
			}
		}
	}

	a->Hcost = count;
	a->Tcost = a->cost + count;
}


void E_tree::print_node(Node a) {
	for (int i = 0; i < 3; ++i) {
		cout << "{ ";
		for (int j = 0; j < 3; ++j) {
			cout << a.vect.at(i).at(j) << ", ";
		}
		printf("}\n");
	}

	cout << endl;
	printf("g(n): %f	h(n): %f	f(n): %f\n", a.cost, a.Hcost, a.Tcost);
}

void E_tree::goal_exist() {
	if (!this->goal_vector.empty()) {
		printf("Goal Found\n");
		printf("\n\n***Solution***\n");
		Node temp = this->goal_vector.at(0);
		for (int i = 0; i < temp.paren.size(); ++i) {
			print_vector(temp.paren.at(i));
			printf("g(n): %f   h(n): %f   f(n): %f\n\n", temp.GN.at(i), temp.HN.at(i), temp.TN.at(i));
		}
		print_vector(temp.vect);
		printf("g(n): %f   h(n): %f   f(n): %f\n\n", temp.cost, temp.Hcost, temp.Tcost);

		printf("\n\n***Directions***\n");
		for (int j = 0; j < temp.dir.size(); ++j) {
			cout << temp.dir.at(j) << endl;
		}
	}
}


void E_tree::print_vector(vector<vector<int>> a) {
	for (int i = 0; i < 3; ++i) {
		cout << "{ ";
		for (int j = 0; j < 3; ++j) {
			printf("%d, ", a.at(i).at(j));
		}
		cout << "}\n";
	}
}

void E_tree::print_expanded() {
	printf("Expanded: %d nodes\n", this->explored.size());
	printf("Maximum queue size: %d nodes\n", this->frontier_size);
}

void E_tree::frontier_update() {
	if (this->frontier_size < frontier.size()) {
		this->frontier_size = frontier.size();
	}
}