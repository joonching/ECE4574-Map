//This is the graph header file
//graph.h
/*
Requirements:
	- Create a "map" that should not be restricted by SIZE. 
		+ Therefore if SIZE changes I should not have to change code but simply the size variable.
	- Each Edge should have a weight and a difficulty value for A*
		+ The difficulty should be set to 1000 initially
		+ The lowest weight will be 1
		+ The destination should have weight and difficulty set to 0
	- Should be able to test multiple graphs
	- Only input should be for obstacle
		+ obstacle should have weight to it and location
			+ however, the obstacle's representation (i.e. weight) may change so keep it flexible


Testing (on QT):
	- 
*/


#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

struct wt_diff
{
	int weight;
	int difficulty;
};

//the graph will represent an adjency matrix
class graph
{
	public:
		graph();
		void delete_graph();
		void add_edge(int origin, int destination, int weight);
		void display();
	private:
		int nodes;
		vector<wt_diff> my_graph;
		
};