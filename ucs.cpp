#include "ucs.h"


Tree::Tree(){
	this->root = new Node();
	this->goal_vector = new vector<Node>();
	this->frontier = new list<Node>();
	this->explored = new vector<Node>();
}
void Tree::set_root(Node *a){
	this->root = a;
}

void Tree::add_frontier(Node add){
	this->frontier->push_back(add);
}

void Tree::add_explored(Node add){
	this->explored->push_back(add);
}

void Tree::add_goal(Node add){
	this->goal_vector->push_back(add);
}

void Tree::remove_frontier(){
	this->frontier->pop_front();
}


bool Tree::compare_goal(Node add){	//check if our Node add is the same as our goal state, if not 
	bool tru = true;
	vector<vector<int>> temp{
		{1,2,3},
		{4,5,6},
		{7,8,0}
	};
	
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			if (add.vect.at(i).at(j) != temp.at(i).at(j)){
				tru = false;
				break;
			}
		}
	}
	
	return tru;
}

bool Tree::isExplored(Node add){ //execute compare add through our explored set. the logic is that if it is true, then tru = true. if it doesn't match, tru = false for the rest of the comparison. 
	bool tru;					// doing so ensure us that if there exists one state where it our node matches, then it will return true. which if true, it will break and the function will return true.
	
	for (int i = 0; i < this->explored->size(); ++i){
		tru = true;
		for (int j = 0; j < 3; ++j){
			for (int k = 0; k < 3; ++k){
				if (explored->at(k).vect.at(i).at(j) != add.vect.at(i).at(j)){
					tru = false;
				}
			}
		}
		if (tru){ break; }
	}
	
	return tru;
}

void Tree::expand_left(Node &add){
	Node temp = add;
	int a; int b; 
	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a).at(temp.b-1); //get # for position left of blank
	temp.vect.at(temp.a).at(temp.b-1) = a; //swap blank and # to the left of blank.
	temp.vect.at(temp.a).at(temp.b) = b;
	
	++temp.cost; //increase cost of our state.
	temp.b = temp.b - 1; //change columns by 1 value to the left/
	temp.child_list = new vector<Node>;  //initalize an empty child list for our newly expanded set.
	
	add.child_list->push_back(temp);
	temp.paren = &add;
	
	if (compare_goal(temp)){
		add_goal(temp);
	}
	
	if (!isExplored(temp)){
		add_explored(temp);
		add_frontier(temp);
	}
	
}

void Tree::expand_up(Node &add){
	Node temp = add;
	int a; int b; 
	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a-1).at(temp.b); //get # for position above blank
	temp.vect.at(temp.a-1).at(temp.b) = a; //swap blank and # to the above blank.
	temp.vect.at(temp.a).at(temp.b) = b;
	
	++temp.cost; //increase cost of our state.
	temp.a = temp.a - 1; //change columns by 1 value to the left/
	temp.child_list = new vector<Node>;  //initalize an empty child list for our newly expanded set.
	
	add.child_list->push_back(temp);
	temp.paren = &add;
	
	if (compare_goal(temp)){
		add_goal(temp);
	}
	
	if (!isExplored(temp)){
		add_explored(temp);
		add_frontier(temp);
	}
}

void Tree::expand_down(Node &add){
	Node temp = add;
	int a; int b; 
	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a+1).at(temp.b); //get # for position underneath  blank
	temp.vect.at(temp.a+1).at(temp.b) = a; //swap blank and # to the underneath blank.
	temp.vect.at(temp.a).at(temp.b) = b;
	
	++temp.cost; //increase cost of our state.
	temp.a = temp.a + 1; //change columns by 1 value to the left/
	temp.child_list = new vector<Node>;  //initalize an empty child list for our newly expanded set.
	
	add.child_list->push_back(temp);
	temp.paren = &add;
	
	if (compare_goal(temp)){
		add_goal(temp);
	}
	
	if (!isExplored(temp)){
		add_explored(temp);
		add_frontier(temp);
	}
}

void Tree::expand_right(Node &add){
	Node temp = add;
	int a; int b; 
	a = temp.vect.at(temp.a).at(temp.b);  //get # for blank "b"
	b = temp.vect.at(temp.a).at(temp.b+1); //get # for position right of blank
	temp.vect.at(temp.a).at(temp.b+1) = a; //swap blank and # to the right of blank.
	temp.vect.at(temp.a).at(temp.b) = b;
	
	++temp.cost; //increase cost of our state.
	temp.b = temp.b + 1; //change columns by 1 value to the left/
	temp.child_list = new vector<Node>;  //initalize an empty child list for our newly expanded set.
	
	add.child_list->push_back(temp);
	temp.paren = &add;
	
	if (compare_goal(temp)){
		add_goal(temp);
	}
	
	if (!isExplored(temp)){
		add_explored(temp);
		add_frontier(temp);
	}
}

void Tree::expand(Node add){
	int a = add.a;
	int b = add.b;
	int *c;
	while (!this->frontier->empty()){
		expand(this->frontier->front());
		this->frontier->pop_front();
	}		
	
	if (a == 0 && b == 0){ //blank is at top left corner.
		expand_right(add);
		expand_down(add);
	}
	else if (a == 0 && b > 0 && b < 2){ //blank is at the top corner
		expand_right(add);
		expand_down(add);
		expand_left(add);
	}
	else if (a == 0 && b == 2){ //blank is at top right corner
		expand_left(add);
		expand_down(add);
	}
	else if (b == 0 && a > 0 && a < 2){ //blank is at the left corner.
		expand_right(add);
		expand_up(add);
		expand_down(add);
	}
	else if (b == 0 && a == 2){  //blank is at the bottom left
		expand_up(add);
		expand_right(add);
	}
	else if (a == 2 && b > 0 && b < 2){ //blank is at the bottom corner
		expand_up(add);
		expand_left(add);
		expand_right(add);
	}
	else if (a == 2 & b == 2){ //bottom right corner.
		expand_up(add);
		expand_left(add);
	}
	else if (b == 2 && a > 0 && a < 2){ //right corner.
		expand_left(add);
		expand_up(add);
		expand_down(add);
	}
	
}

Node Tree::compare_goal(){
	int cost = goal_vector->at(0).cost;
	int i;
	Node temp;
	for (i = 0; i < this->goal_vector->size() - 1; ++i){
		if (cost > goal_vector->at(i+1).cost){
			temp = goal_vector->at(i);
			cost = goal_vector->at(i).cost;
		}
	}
	if (cost > this->goal_vector->at(this->goal_vector->size()-1).cost){
		temp = this->goal_vector->at(this->goal_vector->size()-1);
	}
	return temp;
}

void Tree::trace_goal(Node *add){
	this->answer.push(*add);
	while (add->paren != 0){
		trace_goal(add->paren);
	}
}

void Tree::print_sol(){
	while (!this->answer.empty()){
		for (int i = 0; i < 3; ++i){
			cout << "{";
			for (int j = 0; j < 3; ++j){
				cout << answer.top().vect.at(i).at(j) << ", ";
			}
			cout << "}\n";
		}
	}
}