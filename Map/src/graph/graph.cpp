#include "graph.h"


graph::graph()
{
	//Initialization of the graph
	nodes = 5;
	create_map();
}
graph::graph(int node_size)
{
	this->nodes = node_size;
	create_map();
}
/*
Purpose: This is the function used to add obstacle weight or sensor reading to assign grid weight values
	The cur_pos and destination represent the current position and the destination getting scanned
	This does not mean that the rover will move to this destination...essentially the destination will just tell you direction or side
	Remember that the map has been pre-initialized 
*/
void graph::add_weight(int position, int destination, int weight)
{
	my_graph[position][destination].weight = weight;
	my_graph[destination][position].weight = weight;
} 

/*
Purpose: This function will just initialize a adjency matrix with default values.
	This is under the assumption that the rover will go through and scan the 
*/
void graph::create_map()
{
	//create the size of all possible nodes
	vector<wt_diff> temp_graph(nodes);
	for (int i = 0; i < nodes; i++)
	{
		temp_graph[i].difficulty = 1000;
		temp_graph[i].weight = 100;
	}

	for (int i = 0; i < nodes; i++)
	{
		my_graph.push_back(temp_graph);
		my_graph[i][i].weight = 2;
	}
}

void graph::display_matrix()
{
	cout << "\n\n\n";
	for (int i = 0; i < nodes; i++)
	{
		cout << i << ": ";
		for (int j = 0; j < nodes; j++)
		{
			cout << my_graph[i][j].weight << ", ";
		}
		cout << endl;
	}
}


/*ALL TEST FUNCTIONS BELOW*/

int graph::return_weight(int position, int destination)
{
	return my_graph[position][destination].weight;
}
int graph::return_nodes()
{
	return nodes;
}

int graph::return_size_of_edges()
{
	return my_graph[0].size();
}

int graph::return_size_of_nodes()
{
	return my_graph.size();
}