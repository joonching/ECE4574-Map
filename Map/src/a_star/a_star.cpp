#include "a_star.h"
#include <algorithm>
a_star::a_star()
{
	mov_cost = 10;
}

void a_star::start_path(int pos, int des)
{
	start = pos;
	dest = des;

	edges temp;
	temp.pos = pos;
	temp.parent = pos;
	a_graph.set_weight(start, 0, 0);
	find_neighbors(start,start);
	//closed_list.push_back(temp);
	find_path();
	get_path();
}
void a_star::reset(bool clear)
{
	open_list.clear();
	closed_list.clear();
	path.clear();
	a_graph.reset(clear);
}
void a_star::get_path()
{
	path.push_back(start);
	int node = a_graph.return_lowest_path(start, dest, start, path);
	//cout << "node: " << node << endl;
	while ( node != dest) {
		if (!find_duplicate(node))
			path.push_back(node);
		node = a_graph.return_lowest_path(start, dest, node, path);
	}
	path.push_back(node);
	//print_path();
}
bool a_star::find_duplicate(int node)
{
	for (int i = 0; i < (int)path.size(); i++) {
		if (node == path[i])
			return true;
	}
	return false;
}
void a_star::find_neighbors(int parent, int node)
{
	neighbors.clear();
	vector<int> temp_list;
	temp_list = a_graph.return_neighbor(node);
	neighbors = temp_list;
	/*
	cout << "node:" << node << " neigh: ";
	for (int i = 0; i < (int)temp_list.size(); i++)
	{
		cout << temp_list[i] << " ";
	}*/
	//cout << endl;
	int par_movc = a_graph.get_movementc(parent);
	for (int i = 0; i < (int)temp_list.size(); i++)
	{
		int node_hv = a_graph.get_hval(temp_list[i]);
		int node_tc = a_graph.get_movementc(temp_list[i]);
		/*
		cout << "node:" << temp_list[i];
		cout << " pm-" << par_movc;
		cout << " tc-" << node_tc;
		cout << " hv-" << node_hv << endl;
		*/
		if ((par_movc + node_hv + mov_cost) < node_tc)
		{
			check_duplicate(temp_list[i], parent);
			a_graph.set_movementc(temp_list[i], par_movc + node_hv + mov_cost);
		}
	}
}
void a_star::find_lowest_open()
{
	int min = a_graph.get_movementc(open_list[0].pos);
	int index = 0;
	for (int i = 0; i < (int)open_list.size(); i++) {
		if (a_graph.get_movementc(open_list[i].pos) < min) {
			min = a_graph.get_movementc(open_list[i].pos);
			index = i;
		}
	}
}
void a_star::check_duplicate(int pos, int parent)
{
	edges temp_e;
	temp_e.pos = pos;
	temp_e.parent = parent;
	bool found = false;
	for (int i = 0; i < (int)open_list.size(); i++) {
		if (open_list[i].pos == temp_e.pos) {
			open_list[i].parent = temp_e.parent;
			found = true;
		}
	}
	if (!found) {
		open_list.push_back(temp_e);
	}
}
void a_star::find_path(){
	closed_list = open_list;
	open_list.clear();
	int closed_size = (int)closed_list.size();
	while (closed_size) {
		for (int i = 0; i < closed_size; i++) {
			int pos = closed_list[i].pos;
			int par = closed_list[i].parent;
			find_neighbors(pos, pos);
		}
		closed_list = open_list;
		open_list.clear();
		closed_size = (int)closed_list.size();
	}
}
void a_star::print_open()
{
	for (int i = 0; i < (int)open_list.size(); i++)
	{
		cout << "parent: " << open_list[i].parent << endl;
		cout << "pos: " << open_list[i].pos << endl;
	}
}
void a_star::print_maptc()
{
	a_graph.display_maptc();
}
void a_star::print_path()
{
	cout << "path: ";
	for (int i = 0; i < (int)path.size(); i++) {
		cout << path[i] << ", ";
	}
	cout << endl;
}

/***FUNCTIONS BELOW ARE FOR TESTING***/
void a_star::construct_testmap1(graph &my_graph)
{
	my_graph.set_hvals(0, 5);
	my_graph.set_hvals(1, 4);
	my_graph.set_hvals(2, 6);
	my_graph.set_hvals(3, 3);
	my_graph.set_hvals(4, 4);
	my_graph.set_hvals(5, 2);
	my_graph.set_hvals(6, 1);
	my_graph.set_hvals(7, 6);
	my_graph.set_hvals(8, 6);
	my_graph.set_hvals(9, 5);
	a_graph = my_graph;
	//a_graph.display_hvals();
}
void a_star::construct_testmap2(graph &my_graph)
{
	my_graph.set_hvals(0, 5);
	my_graph.set_hvals(1, 4);
	my_graph.set_hvals(2, 6);
	my_graph.set_hvals(3, 3);
	my_graph.set_hvals(4, 4);
	my_graph.set_hvals(5, 2);
	my_graph.set_hvals(6, 1);
	my_graph.set_hvals(7, 6);
	my_graph.set_hvals(8, 6);
	my_graph.set_hvals(9, 5);
	a_graph = my_graph;
	//a_graph.display_hvals();
}
int a_star::return_openlist(int pos)
{
	//cout << neighbors[pos];
	return neighbors[pos];
}

vector<int> a_star::return_path()
{
	return path;
}