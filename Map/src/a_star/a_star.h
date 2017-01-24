/*
	File: a_star.h
	Description: The a_star class should be responsible for creating a path of nodes based on
		the A* algorithm.
		
	Requirements: 
		- H-values need to be inputted accordingly to start and end position
			+ use the Manhattan method
		- I will be able to create a map with the path of least resistance
		- Ignore all obstacles part of list
			+ obstacles are determined in the graph class and not internally in this class
			+ Therefore, it is not obstacle dependent and the obstacle can change without affecting the a_star
		- Should be able to test multiple start and destinations
		- Only requires the nodes that are in the map and their corresponding edges.
			+ not dependent on map layout -- as of now
			+ all difficulty/cost values will be stored in matrix

	Testing (on QT)
		- check you can return the path of least resistance/fastest route
		- check that you never include an obstacle as a part of the list
		- check that you can find the best path with multiple start and destination points
*/

#ifndef ASTAR_HEADER
#define ASTAR_HEADER

#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>
#include "../graph/graph.h"

using namespace std;

struct edges
{
	int pos;
	int parent;
};

class a_star
{
public:
	a_star();
	void start_path(int pos, int des);
	void get_path();
	void find_path();
	bool find_duplicate(int node);
	void find_neighbors(int parent, int node);
	void find_lowest_open();
	void check_duplicate(int pos, int parent);
	void print_open();
	void print_maptc();
	void print_path();
	void reset(bool clear);

	/***FUNCTIONS BELOW ARE FOR TESTING***/
	void construct_testmap1(graph &my_graph);
	void construct_testmap2(graph &my_graph);
	int return_openlist(int pos);
	vector<int> return_path();
private:
	vector<edges> open_list;
	vector<edges> closed_list;
	vector<int> path;
	vector<int> neighbors;
	graph a_graph;
	int start;
	int dest;
	int mov_cost;
};
#endif