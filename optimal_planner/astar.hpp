#ifndef astar_hpp
#define astar_hpp

# pragma once


#include <cmath>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_set>
#include <queue>
#include <memory>
using namespace std;



class path {

	public:

		// define the struct node;
        struct node {
			// this struct will have variable to store x-cord, y-cord, cost-to-come(g), cost-to-go(h), total-cost(f) & addr of 'parent' node
			int x;
			int y;
			float f;
			float g;
			float h;
			node* prev;
	    };

		struct compare{
			bool operator()(const node* a, const node* b);
		};

		// a priority queue implementation of to-be-visited nodes 
		// This struct node is used to adjust the 'priority_queue' with nodes as element .. prioritizes nodes based on their f-value
		priority_queue<node*, std::vector<node*>, compare> open;

		unordered_set<node*> closed;  // a hashmap implementation of the visited nodes;

		unordered_set<node*>::iterator it;
		
		vector<vector<int>> search(vector<vector<int>>map, array<int,2>start,array<int,2>goal);

		void trackThePath(); // This method is used to update the 'output_map' 2D vector for the final path found by A*

		int euclideanDistance(int i1, int j1, int i2, int j2);

		bool IsValidInput(int x, int y, vector<vector<int>> map);


	private:
		vector<vector<int>> map;			// To store the data of map obtained from user through main();

		vector<vector<node*>> adr;			// vector to store address of each new node;
		
		vector<node*> final_path;  		// Stores the output path obtained as a result of A*

		int _i_start {0};		// x-co-ordinate of start point
		int _j_start {0};		// y-co-ordinate of start point
		int _i_goal {0};         // x-coordinate of end point
		int _j_goal {0}; 		// y-coordinate of end point

		bool _found_flag = false;  // this flag will be set to true if the element is found and we will exit of the while loop in Astar method

		void _createNodes(); // To create nodes for each element of input map and store its address in addr 
		void _updateHeuristic();  // Update the heuristics function depending upon the goal location as obtained from Input methods
		void _exploreNeighbours(int curr_i, int curr_j);  // Search the neighbours of a given node and add them to the queue if they are valid
		bool _CheckValidCell(int i, int j, int neighbour_index); // to check the validity of the neighbouring nodes
		void _updateDistance(int i, int j, int neighbour_indexs); // To update the distance of a neighbouring node if the node is a valid node

};

#endif