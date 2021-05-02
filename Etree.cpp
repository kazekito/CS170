#include "ucs.h"



E_tree::E_tree(){
	this->root = Node();
	this->goal_vector = vector<Node>();
	this->frontier = list<Node>();
	this->explored = vector<Node>();
}


void E_tree::set_root(Node a){
	this->root = a;
}

void E_tree::add_frontier(Node a){
	this->frontier.push_back(a);
}

void E_tree::add_explored(Node a){
	this->explored.push_back(a);
}

void E_tree::add_goal(Node a){
	this->goal_vector.push_back(a);
}

bool E_tree::compare_goal(Node a){
	bool tru = true;
	vector<vector<int>> temp{
		{1,2,3},
		{4,5,6},
		{7,8,0}
	};
	
	if (a.vect == temp){
		return true;
	}
	else{
		return false;
	}

	
	return tru;
	
}

bool E_tree::isExplored(Node a){
	bool temp = true;
	if (this->explored.empty()){
		temp = false;
	}
	else {
		for (int i = 0; i < this->explored.size(); ++i){
			if (this->explored.at(i).vect == a.vect){
				return true;
			}
		}
		temp = false;
	}
	
	return temp;
}

bool E_tree::isFrontier(Node a){
	list<Node>::iterator it;
	for (it = this->frontier.begin(); it != this->frontier.end(); ++it){
		if (it->vect == a.vect){
			return true;
		}
	}
	
	return false;
}

Node E_tree::get_lowestcost(){
	list<Node>::iterator it;
	Node temp;
	temp = frontier.front();
	for (it = this->frontier.begin(); it != this->frontier.end(); ++it){
		if (it->Tcost < temp.Tcost){
			temp = *it;
		}
	}
	
	return temp;
}

void E_tree::remove_frontier(Node a){
	list<Node>::iterator it;
	for (it = this->frontier.begin(); it != this->frontier.end(); ++it){
		if (it->vect == a.vect){
			this->frontier.erase(it);
			return;
		}
	}
}

void E_tree::expand_left(Node &a){
	
}

void E_tree::expand_right(Node &a){
	
}

void E_tree::expand_up(Node &a){
	
}

void E_tree::expand_down(Node &a){
	
}

void E_tree::expand(Node a){
	
}

void E_tree::expand_frontier(){
	
}

bool E_tree::position_checker(double value, double i, double j){
	
	if (value == 1 && i == 0.0 && j == 0.0){
		//printf("Value %f is true\n",value);
		return true;
	}
	else if (value == 2 && i == 0.0 && j == 1.0){
		return true;
	}
	else if (value == 3 && i == 0.0 && j == 2.0){
		return true;
	}
	else if (value == 4 && i == 1.0 && j == 0.0){
		return true;
	}
	else if (value == 5 && i == 1.0 && j == 1.0){
		return true;
	}
	else if (value == 6 && i == 1.0 && j == 2.0){
		return true;
	}
	else if ((value == 7.0 && i == 2.0 && j == 0.0)){
		return true;
	}		
	else if (value == 8 && i == 2.0 && j == 1.0){
		return true;
	}
	else if (value == 0 && i == 2.0 && j == 2.0){
		return true;
	}	
	else{
		return false;
	}
	
	return false;
}

double E_tree::position_diff(double value, double i, double j){
	double temp_i;
	double temp_j;
	double j_diff;
	double i_diff;
	double answer;
	double temp;
	
	if (value == 0.0){
		temp_i = 2.0;
		temp_j = 2.0;
	}
	else if (value == 1.0){
		temp_i = 0.0;
		temp_j = 0.0;
	}
	else if (value == 2.0){
		temp_i = 0.0;
		temp_j = 1.0;
	}
	else if (value == 3.0){
		temp_i = 0.0;
		temp_j = 2.0;
	}
	else if (value == 4.0){
		temp_i = 1.0;
		temp_j = 0.0;
	}
	else if (value == 5.0){
		temp_i = 1.0;
		temp_j = 1.0;
	}
	else if (value == 6.0){
		temp_i = 1.0;
		temp_j = 2.0;
	}
	else if (value == 7){
		temp_i = 2.0;
		temp_j = 0.0;
	}
	else if (value == 8.0){
		temp_i = 2.0;
		temp_j = 1.0;
	}
	
	i_diff = abs(temp_i - i);
	j_diff = abs(temp_j - j);
	
	temp = pow(i_diff,2) + pow(j_diff,2);
	answer = sqrt(temp);
	
	return answer;
}

void E_tree::H_calc(Node *a){

	double count = 0.0;
	
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			if (!position_checker(a->vect.at(i).at(j),i,j)){
				count = count +  position_diff(a->vect.at(i).at(j),i,j);
			}
		}
	}
	
	a->Hcost = count;
	a->Tcost = a->cost + count;
}


void E_tree::print_T(Node a){
	printf("Total cost: %f\n",a.Tcost);
}

void E_tree::print(){
	printf("%f\n", this->frontier.front().Tcost);
}

