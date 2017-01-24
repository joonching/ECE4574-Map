/*
	File: graph.h
	Description: All I want to do for this class is to be able to create a graph/map/grid as the "sensor inputs" come in. 
				 By doing this I will only create a map for where there is data from the rover.
				 Therefore, my assumption is that this map is getting generated as the rover moves around the real world map.

	Requirements:
		- Create a "map" that should not be restricted by SIZE. 
			+ Therefore if SIZE changes I should not have to change code but simply the size variable.
			+ Map should be generated already before the pathfinding begins
		- Each Edge should have a weight and a difficulty value for A*
			+ The difficulty should be set to 1000 initially
			+ The lowest weight will be 2 besides destiation and the highest will be 100;
			+ The destination should have weight and difficulty set to 0
		- Should be able to test multiple graphs
		- Only input should be for obstacle
			+ obstacle should have weight to it and location -- for now the obstacles will be weight values from sensors
				+ however, the obstacle's representation (i.e. weight) may change so keep it flexible


	Testing (on QT):
		- Check you can change the size of the nodes and the graph will correspondingly change
		- Check that the graph has pre-initialized values (i.e. 1000 and 100)
		- Check that when you add a weight the weight and the corresponding node is changed
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


//The graph will represent an adjency matrix
class graph
{
	public:
		graph();
		graph(int node_size);
		void delete_graph();
		void add_weight(int cur_pos, int destination, int weight);
		void display_matrix();
		
		//**FUNCTIONS FOR TESTING**
		int return_weight(int position, int destination);
		int return_nodes();
		int return_size_of_nodes();
		int return_size_of_edges();
	private:
		void create_map();
		int nodes;
		vector<vector<wt_diff>> my_graph;
};