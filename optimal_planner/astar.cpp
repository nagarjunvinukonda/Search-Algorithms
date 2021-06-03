 
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_set>
#include <queue>

#include "astar.hpp"
using namespace std;
#define INF 9999


/* comparator function for priority queue */
bool path::compare::operator() (const node* a, const node* b) {
    return a->f > b->f;
}


void path::_createNodes()
{
	// This function is called by the constructor to create a matrix of same size as that of the given matrix but to store the adresses of each nodes
	node* n = NULL;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[1].size(); j++)
		{
			n = new node;
			n->f = INF;
			n->g = INF;
			n->h = 0;
			n->x = i;
			n->y = j;
			n->prev = NULL;
			adr[i][j] = n;                // storing the address of new node for discretized point [x,y] in adr[i][j]

		}
	}
}


// this function is called by the input() method to update the heuristics of each and every node which were initialized with a value 0
void path::_updateHeuristic()  
{
	for(int i=0; i<map.size(); i++){
        for(int j=0; j<map[1].size(); j++){

			adr[i][j]->h = euclideanDistance(i,j,_i_goal, _j_goal);
        }
    }

}

int path::euclideanDistance(int i1, int j1, int i2, int j2){
    return int(sqrt( pow(i2-i1,2) + pow(j2-j1,2)));
}


//This function checks the neighbours of given nodes if they are in free space, have already been visited, are out of bounds or lie in obstacles
	//Neighbour_index = {N,0} {S,1}  {E,2}  {W,3}
bool path::_CheckValidCell(int i, int j, int neighbour_index)
{

	switch (neighbour_index)
	{
	case 0:  // check north
		if (i <= 0 )
		{

			return false;
		}
		else
		{
			it = closed.find(adr[i-1][j]);
			if (map[i - 1][j] == 1 || it != closed.end())  // upper element is an obstacle  OR the upper element has already been visited
			{
				return false;
			}
			else
			{
				//cout << "\n North Valid";
				return true; 
			}
		}
		break;


	case 1:  // check south
		if (i >= map.size()-1)
		{
			//cout << "\n South InValid";
			return false;
		}
		else
		{ 
			it = closed.find(adr[i+1][j]);  
			if (map[i + 1][j] == 1 || it != closed.end())  // lower element is an obstacle  OR the lower element has already been visited
			{
				//cout << "\n South NotValid";
				return false;
			}
			else
			{
				//cout << "\n South Valid";
				return true;
			}
		}
		break;


	case 2:  // check east
		if (j >= map[1].size()-1)
		{
			return false;
		}
		else
		{	
			it = closed.find(adr[i][j + 1]);
			if (map[i][j + 1] == 1 || it != closed.end())  // east element is an obstacle  OR the east element has already been visited
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		break;

	case 3:  // check west
		if (j <= 0)
		{
			return false;
		}
		else
		{
			it = closed.find(adr[i][j - 1]);
			if (map[i][j-1] == 1 || it!=closed.end())  // west element is an obstacle OR the west element has already been visited
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		break;

	}
}


// This function updates a particular neighbour's distance as given by the neighbour_index
	//Neighbour_index = {N,0} {S,1}  {E,2}  {W,3}
void path::_updateDistance(int i, int j, int cs)  // here the i and j represent index of Neighbours and the parent node
{

	node* temp=NULL;
	node* parent = NULL;


	switch (cs)
	{
	case 0: // update North
		temp = adr[i][j];
		parent = adr[i + 1][j]; 		 // parent is the node whose north element we are updating here. Thus it will lie exactly BELOW it


		if (temp->g > parent->g + 1)     // update distance if and only if current distance is more than parent distance + cost to go
		{
			temp->g = parent->g + 1;	 // update the cost to node
			temp->f = temp->g + temp->h; // update the total cost
			temp->prev = parent;         // store the prev of current node as parent of current
			open.push(temp);  			 // push this node into the priority queue
		}
		break;

	case 1: // update South
		temp = adr[i][j];
		parent = adr[i - 1][j]; 		 // parent is the node whose south element we are updating here. Thus it will lie exactly ABOVE it


		if (temp->g > parent->g + 1) 	 // update distance if and only if current distance is more than parent distance + cost to go
		{
			temp->g = parent->g + 1;	 // update the cost to node
			temp->f = temp->g + temp->h; // update the total cost
			temp->prev = parent;         // store the prev of current node as parent of current
			open.push(temp);  			 // push this node into the priority queue
		}
		break;

	case 2: // update East
		temp = adr[i][j];
		parent = adr[i][j -1]; // parent is the node whose east element we are updating here. Thus it will lie exactly to its left


		if (temp->g > parent->g + 1)  // update distance if and only if current distance is more than parent distance + cost to go
		{
			temp->g = parent->g + 1;	 // update the cost to node
			temp->f = temp->g + temp->h; // update the total cost
			temp->prev = parent;         // store the prev of current node as parent of current
			open.push(temp); 			 // push this node into the priority queue
		}
		break;

	case 3: // update West
		temp = adr[i][j];
		parent = adr[i][j+1]; // parent is the node whose west element we are updating here. Thus it will lie exactly to its right

		if (temp->g > parent->g + 1)  // update distance if and only if current distance is more than parent distance + cost to go
		{
			temp->g = parent->g + 1;	 // update the cost to node
			temp->f = temp->g + temp->h; // update the total cost
			temp->prev = parent;         // store the prev of current node as parent of current
			open.push(temp);  			 // push this node into the priority queue
		}
		break;
	}
}



// This function checks the neighbours of given nodes if they are in free space, have already been visited, are out of bounds or lie in obstacles
	// If the node is a free space, it updates its distance g & f
void path::_exploreNeighbours(int curr_i, int curr_j)
{
	int i;
	int j;
	// North
	if (_CheckValidCell(curr_i,curr_j, 0) == true)
	{
		i = curr_i - 1;
		j = curr_j;
		//cout << "\n North Valid";
		_updateDistance(i, j, 0);
	}
	//else { cout << "\n North InValid"; }

	// South
	if (_CheckValidCell(curr_i, curr_j, 1) == true)
	{
		i = curr_i + 1;
		j = curr_j;
		//cout << "\n South Valid";
		_updateDistance(i, j, 1);

	}
	//else { cout << "\n South InValid"; }
	// East
	if (_CheckValidCell(curr_i, curr_j, 2) == true)
	{
		i = curr_i;
		j = curr_j+1;
		// << "\n East Valid";
		_updateDistance(i, j, 2);

	}
	//else { cout << "\n East InValid"; }
	// West
	if (_CheckValidCell(curr_i, curr_j, 3) == true)
	{
		i = curr_i;
		j = curr_j-1;
		//cout << "\n West Valid";
		_updateDistance(i, j, 3);

	}

}




// This function traces the optimum path found by the A* algorithm
void path::trackThePath()
{

	node* curr=NULL;
	if(adr[_i_goal][_j_goal]->prev ==NULL){
		curr =NULL;
	}
	else{

		curr = adr[_i_goal][_j_goal];
	}

	while(curr!=NULL){
        final_path.emplace_back(curr);
		curr = curr->prev;

    }

}


/**
 * Check if the x, y coordinates are valid
 * @param x X coordinate (row)
 * @param y Y coordinate (col)
 * @param grid The grid
 */

bool path::IsValidInput(int i, int j, vector<vector<int>> map) {
    
	if(map.empty()){
		// cout<<"Input Map is Empty"<<endl;
		return false;
	}

	bool res = true;
	bool verbose =false;

    if (i < 0 || i > map.size()-1) {
		verbose = true;
        if (verbose)
            cout << "Input x coord is invalid" << endl;
        res = false;
    }
    if (j < 0 || j > map[1].size()-1) {
		verbose = true;
        if (verbose)
            cout << "Input y coord is invalid" << endl;
        res = false;
    }
    return res;
}


// This Algorithm is A_star implementation using linked lists. The Complexity of Algorithm is depened on size of the map since we are having constant hurestic. 
// Goal of this function is to store the start element in the 'Open' set which is a priority queue of all the nodes. The priority queue in c++ gets updated when any new element is inserted into the queue
// We pop the top element of the priority queue as that has the MINIMUM f(x) (i.e total cost) and store that top element in the 'CLOSED' set which is a collection of all the visited nodes. We then EXPLORE its neighbours 
// While EXPLORING the neighbours of the given node, we CHECK if that node is an OBSTACLE or is already been visited and exists in the CLOSED set (to ease this task of searching an element in a container, we implement CLOSED as an unordered set)
// While EXPLORING if a Node's f(x) gets updated, we store the address of previous node which called this node in 'prev' pointer inside the struct 'node'.
// ALL these steps are executed in a loop until the end goal node is encountered.

vector<vector<int>>path::search(vector<vector<int>> map, array<int,2>start,array<int,2>goal){

	vector<vector<int>> output_path;

	if(!IsValidInput(_i_start,_j_start, map)||!IsValidInput(_i_goal,_j_goal,map)){
		return output_path;
	}
	
	this->map = map;	

	for (int i = 0; i < map.size(); i++)
	{
		vector<node*> tempvec;
		for (int j = 0; j < map[1].size(); j++)
		{
			tempvec.push_back(NULL);
		}
		adr.push_back(tempvec);
	}
	
	_createNodes();

	_i_start=start[0];
	_j_start=start[1];
	_i_goal=goal[0];
	_j_goal=goal[1];



	_updateHeuristic();  					// this takes the end coordinates and updates heuristics of each node stored in the 'adr' 2Dvector.
	
	node* temp = adr[_i_start][_j_start];		// Also update the g(x) of the start node here itself.
	temp->g = 0;
	temp->f = (temp->g) + (temp->h);


	open.push(adr[_i_start][_j_start]);
	int i_curr = 0;
	int j_curr = 0;
	_found_flag = false;
	
	while (!open.empty() && _found_flag != true)
	{
		node* temp = open.top();
        closed.insert(temp);
		open.pop();
		i_curr = temp->x;
		j_curr = temp->y;


		if (i_curr == _i_goal && j_curr == _j_goal)
		{
			
			_found_flag = true;  	// set false true and terminate the loop
			
		}
		else
		{
			_exploreNeighbours(i_curr, j_curr);
		}

	}

	path::trackThePath();

	int size = final_path.size();

	for(int i=size-1; i>=0; i--){

		std::vector<int> point{final_path[i]->x,final_path[i]->y};
        output_path.emplace_back( point );
	}

	return output_path;

}



// int main()
// {



// 	array<int,2>start = {4, 0};
// 	array<int,2>goal = {6, 9};

// 	vector<vector<int>> world_state = {{0,0,1,0,1,0,0,0,0,0},
// 									   {0,0,1,0,0,1,0,1,1,1},
// 									   {0,0,0,0,1,0,1,1,1,1},
// 									   {0,0,1,0,0,0,0,0,0,0},
// 									   {0,0,1,0,1,0,1,1,0,1},
// 									   {0,0,1,0,0,0,1,0,0,0},
// 									   {0,0,1,0,1,0,0,0,1,0}};  



// 	path p1;

// 	vector<vector<int>>optimal_path = p1.search(world_state,start, goal);

// 	for(vector<int> i: optimal_path){

// 		cout<<i[0]<<" "<<i[1]<<endl;
// 	}


// 	return 0; 
	
// }
	