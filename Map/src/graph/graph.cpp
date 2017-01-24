#include "graph.h"


graph::graph()
{
	//Initialization of the graph
	nodes = 10;
	create_map();
}
graph::graph(int node_size)
{

}
void graph::set_nodes(int n)
{
	nodes = n;
	my_graph.clear();
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
		//temp_graph[i].difficulty = 1000;
		temp_graph[i].weight = 100;
		temp_graph[i].visited = false;
	}

	for (int i = 0; i < nodes; i++)
	{
		my_graph.push_back(temp_graph);
		my_graph[i][i].weight = 5;
		my_graph[i][i].h_val = nodes*nodes;
		my_graph[i][i].movement_cost = 1000;
		//my_graph[i][i].prev.push_back(-1);
	}
}
void graph::reset(bool clear)
{
	for (int i = 0; i < nodes; i++)
	{
		my_graph[i][i].visited = false;
		my_graph[i][i].weight = 5;
		my_graph[i][i].h_val = nodes*nodes;
		if (clear)
			my_graph[i][i].movement_cost = 1000;
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
void graph::display_maptc()
{
	cout << "\n\n\n";
	for (int i = 0; i < nodes; i++)
	{
		cout << i << ": ";
		cout << my_graph[i][i].movement_cost << ", ";
		cout << endl;
	}
}
void graph::display_hvals()
{
	cout << "\n\n\n";
	for (int i = 0; i < nodes; i++)
	{
		cout << i << ": ";
		cout << my_graph[i][i].h_val << ", ";
		cout << endl;
	}
}
int graph::return_lowest_path(int start, int des, int pos, vector<int> &path)
{
	my_graph[pos][pos].visited = true;
	vector<int> temp_path;
	temp_path = return_neighbor(pos);
	int min = 0;
	int node = pos;
	bool found = false;
	for (int i = 0; i < (int)temp_path.size(); i++) {
		int index = temp_path[i];
		if (index == des) {
			node = index;
			found = true;
			i = (int)temp_path.size();
		}
		else if (!my_graph[index][index].visited) {
			if (!min) {
				min = my_graph[index][index].movement_cost;
				node = index;
				found = true;
			}
			else if (my_graph[index][index].movement_cost < min) {
				min = my_graph[index][index].movement_cost;
				node = index;
				found = true;
			}
			//cout << "node:" << node << endl;
		}
	}
	if (!found) {
		path.pop_back();
		node = path.back();
	}
	//cout << node;
	return node;
}
int graph::get_hval(int pos)
{
	return my_graph[pos][pos].h_val;
}
int graph::get_movementc(int pos)
{
	return my_graph[pos][pos].movement_cost;
}
void graph::set_movementc(int pos, int val)
{
	my_graph[pos][pos].movement_cost = val;
}
void graph::set_hvals(int pos, int val)
{
	my_graph[pos][pos].h_val = val;
}
void graph::set_weight(int pos, int val, int mc)
{
	my_graph[pos][pos].weight = val;
	my_graph[pos][pos].movement_cost = mc;
}
vector<int> graph::return_neighbor(int pos)
{
	vector<int> ret_vec;
	for (int i = 0; i < nodes; i++) {
		int temp = my_graph[pos][i].weight;
		if (temp < 50 && i != pos) {
			ret_vec.push_back(i);
		}
	}
	//print_neighbor(ret_vec);
	return ret_vec;
}
void graph::print_neighbor(vector<int> neigh)
{
	for (int i = 0; i < neigh.size(); i++) {
		cout << neigh[i] << " ";
	}
	cout << endl;
}
/*
	TODO: FIX ... The order is wrong
			...look at debugger and step through...problem is something with your prev
			...your adding a previous at the wrong step or what not...check on that
			...do this and your pathfinding is done~~~


void graph::assign_h_vals(int des)
{
	//first search through your current nodes to find connections
	vector<int> path_list;
	//usually this will be current position...if keeping track of current position
	int cur_pos = 0;
	path_list.push_back(cur_pos);
	my_graph[cur_pos][cur_pos].visited = true;
	while (cur_pos < nodes) {
		for (int i = cur_pos; i < nodes; i++) {
			bool valid_path = false;
			for (int j = 0; j < nodes; j++) {
				if (my_graph[i][j].weight < 50 && i != j && !my_graph[j][j].visited) {
					if (j == des) {
						valid_path = true;
						my_graph[j][j].visited = true;	
						cout << "list: ";
						for (int c = 0; c < (int)path_list.size(); c++)
							cout << path_list[c] << ", ";
						cout << j << endl;
						int cur_h_val = (int)path_list.size()+1;
						if (my_graph[cur_pos][cur_pos].h_val > cur_h_val && my_graph[cur_pos][cur_pos].h_val != 0)
							my_graph[cur_pos][cur_pos].h_val = cur_h_val;
						//-1 since i will increment after it leaves this for loop
						i = path_list.back() - 1;
						j = nodes;
					}
					else {
						valid_path = true;
						my_graph[j][j].visited = true;
						if (path_list.size() == 1)
						{
							int prev = path_list.back();
							for (int t = 0; t < my_graph[prev][prev].prev.size(); t++) {
								if (my_graph[prev][prev].prev[t] >= 0) {
									int temp = my_graph[prev][prev].prev[t];
									my_graph[temp][temp].visited = false;
									my_graph[temp][temp].prev[t] = -1;
								}
							}
						}
						path_list.push_back(j);
						cout << "list: ";
						for (int c = 0; c < (int)path_list.size(); c++)
							cout << path_list[c] << ", ";
						cout << endl;
						i = j-1;
						j = nodes;
						if ((int)path_list.size() > my_graph[cur_pos][cur_pos].h_val) {
							int pos = path_list[(int)path_list.size() - 2];
							int prev = path_list.back();
							for (int t = 0; t < my_graph[prev][prev].prev.size(); t++) {
								if (my_graph[prev][prev].prev[t] >= 0) {
									int temp = my_graph[prev][prev].prev[t];
									my_graph[temp][temp].visited = false;
									my_graph[temp][temp].prev[-1];
								}
							}
							my_graph[pos][pos].prev[0] = prev;
							path_list.pop_back();
							i = pos - 1;
							j = nodes;
						}
					}
				}
			}
			//TODO: You need to add in a method such that you kee
			if (!valid_path) {
					if (path_list.size() > 1) {
						int pos = path_list[(int)path_list.size() - 2];
						int prev = path_list.back();
						for (int t = 0; t < (int)my_graph[prev][prev].prev.size(); t++) {
							if (my_graph[prev][prev].prev[t] >= 0) {
								int temp = my_graph[prev][prev].prev[t];
								my_graph[temp][temp].visited = false;
								my_graph[temp][temp].prev[0] = -1;
							}
						}

						my_graph[pos][pos].prev.push_back(prev);
						path_list.pop_back();
						i = pos - 1;
					}
					else {
						int prev = path_list.back(); //0
						int temp = my_graph[prev][prev].prev[0]; //1
						my_graph[temp][temp].visited = false;
						my_graph[temp][temp].prev[0] = -1;
						my_graph[prev][prev].visited = false;
						my_graph[prev][prev].prev[0] = -1;
						i = nodes;
						path_list.pop_back();
					}
			}
		}
		cur_pos++;
		path_list.push_back(cur_pos);
	}
}
*/
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
void graph::do_astar(graph& test_graph)
{
	//a_star pathfind;
	//pathfind.construct_testmap1(test_graph);
	//pathfind.start_path(7, 4);
}
