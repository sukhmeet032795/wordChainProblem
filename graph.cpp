#include <iostream>
#include <string>
#include <limits.h>
#include <queue>

using namespace std;

class graph_list
{
public:
	graph_list(int);
	void add_node(string);
	void print();
	void find_shortest_path(string, string);
	int find_index(string);
private:
	class edge {
	public:
		int index;
		edge *next;
	};
	class vertex
	{
	public:
		string val;
		edge* next;
	};
	int nodeCount;
	vertex *list;
};

graph_list::graph_list(int nodes)
{
	int i;

	nodeCount = 0;
	
	list = new vertex[nodes];

	//Initialize the pointer of each index, notice we don't initialize the variable on the index
	for (i = 0; i < nodes; i++)
	{
		//Give the value of the array index either some dummy value or the value of the node
		//We can choose either or because in this interpretation our array index is the value of the node
		list[i].val = "";
		list[i].next = NULL;
	}
}

bool is_adjacent(string a, string b) {
	if(a.length() != b.length()) return false;
	int count = 0;

	for(int i=0; i<a.length(); ++i) {
		if(a.at(i) != b.at(i)) ++count;
	}

	return count == 1;
}

void graph_list::add_node(string input) {
	list[nodeCount++].val = input;

	for(int i=0; i<nodeCount-1; ++i) {
		if(is_adjacent(list[i].val, list[nodeCount-1].val)) {
			edge * new_edge = new edge();
			new_edge->index = i;
			new_edge->next = list[nodeCount-1].next;
			list[nodeCount-1].next = new_edge;

			new_edge = new edge();
			new_edge->index = nodeCount-1;
			new_edge->next = list[i].next;
			list[i].next = new_edge;
		}
	}
}

void graph_list::print() {
	edge *temp;
	for(int i=0; i<nodeCount; ++i) {
		cout << "v: " << list[i].val << " -> ";
		temp = list[i].next;
		while(temp != NULL) {
			cout << list[temp->index].val << " -> ";
			temp = temp->next;
		}
		cout << "[NULL]" <<endl;
	}
}

int graph_list::find_index(string input) {
	for(int i=0; i<this->nodeCount; ++i) {
		if(this->list[i].val.compare(input) == 0) {
			return i;
		}
	}
	return -1;
}

void copy_path(int *a, int *b, int size) {
	for(int i=0; i < size; ++i) {
		a[i] = b[i];
	}
}

void graph_list::find_shortest_path(string input, string input2) {
	bool *processed = new bool[nodeCount];
	edge **temp = new edge *[nodeCount];
	int *stored = new int[nodeCount];
	int *cur = new int[nodeCount];
	int path_index = -1, stored_path_index = nodeCount +1;
	int *distances = new int[nodeCount];
	int i;

	for(i=0; i< nodeCount; ++i) {
		processed[i] = false;
		distances[i] = INT_MAX;
	}

	processed[find_index(input)] = true;
	cur[++path_index] = find_index(input);
	temp[path_index] = list[cur[path_index]].next;

	while(path_index >= 0) {

		if(temp[path_index] == NULL) {
			--path_index;
		} else {
			if(!processed[temp[path_index]->index] && (distances[temp[path_index]->index] > path_index)) {
				distances[temp[path_index]->index] = path_index;
				processed[temp[path_index]->index] = true;

				cur[path_index+1] = temp[path_index]->index;

				temp[path_index] = temp[path_index]->next;
				++path_index;
				temp[path_index] = list[cur[path_index]].next;
				if(list[cur[path_index]].val.compare(input2) == 0) {
					copy_path(stored, cur, path_index + 1);
					stored_path_index = path_index;
					processed[cur[path_index]] = false;
					--path_index;
				}
			} else temp[path_index] = temp[path_index]->next;
		}
	}

	if(stored_path_index <= nodeCount) {
		cout << "[Length:" << stored_path_index+1 << "]" << endl;

		cout << "[Path] :-> ";

		for(i=0; i < stored_path_index; ++i) {
			cout << list[stored[i]].val << " -> ";
		}
	 	cout << list[stored[i]].val << endl;
 	} else cout << "There is no such path possible\n";
}

int main() {
	int count = 0, i;
	string input, input2;
	graph_list *graph = NULL;
	
	cout << "Enter number of words to add in dictionary: ";
	cin >> count;
	graph = new graph_list(count);

	for(i=0; i < count; ++i) {
		cout << "Enter word: ";
		cin >> input;
		graph->add_node(input);
	}

	graph->print();

	cout << "Enter start word: ";
	cin >> input;

	cout << "Enter final word: ";
	cin >> input2;

	graph->find_shortest_path(input, input2);

	return 0;
}







