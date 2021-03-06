// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
// Created by <Tuan Pham> on <4/17/2018>

#include "stdafx.h"
#include <stdio.h>
#include <limits.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Number of vertices in the graph
#define V 10

//Return the name of city by index
string city(int index)
{
	string city[V] = { "Detroit", "St. Louis", "Chicago", "Los Angeles", "New York",
		"Washington DC", "Miami", "Denver", "Seattle", "Dallas" };
	return city[index];
}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int MinDistance(int dist[], bool sptSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

/*
Function to print shortest path from source to destination
parent[] holds the visited cities
child[] holds the distance betweem visited cities
*/
void PrintPath(int parent[], int child[], int p, int dist[], int dest)
{
	//Base case: If p is source
	if (parent[p] == -1)
		return;
	string printLine = ""; string line;

	PrintPath(parent, child, parent[p], dist, dest);

	printLine = " --> " + city(p);
	while (printLine.length() < 20) {
		printLine = printLine + " ";
	}	
	cout << printLine;
	cout <<"Distance: " << child[p] << endl;
	if (p == dest)
		return;
	else {
		cout << left << setw(15);
		cout << city(p);
	}
		
}



// A utility function to print the final distance
void PrintSolution(int dist[], int n, int dest, int src)
{
	int smallest = dist[0];
	int index = 0;
	for (int i = 0; i < V; i++)
	{
		if (dist[i] > 0 && i == dest)
		{
			smallest = dist[i];
			index = i;
		}
	}
	cout << "\nThe total distance from " << city(src) << " to " << city(dest)
		<< " is " << smallest << " miles.\n\n";

}



// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void Dijkstra(int graph[V][V], int src, int dest)
{
	int dist[V];     // The output array.  dist[i] will hold the shortest
					 // distance from src to i

	bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
					// path tree or shortest distance from src to i is finalized
	int parent[V];
	int child[V];
	// Initialize all distances as INFINITE, stpSet[] as false, and path-parent[] as -1
	for (int i = 0; i < V; i++)
	{
		parent[i] = -1;
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}
	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in first iteration.
		int u = MinDistance(dist, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from 
			// u to v, and total weight of path from src to  v through u is 
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
			{
				dist[v] = dist[u] + graph[u][v];
				parent[v] = u;				//get the visited city
				child[v] = graph[u][v];		//get the distance through visited city
			}
	}

	//print the path to every visited cities along with their distances
	if (dist[dest] == INT_MAX)
		// There is no path
		cout << "\nThere is no path from cities you chose.\n\n";
	else {
		cout << "\nThe path from " << city(src) << " to " << city(dest) << " is :" << endl;
		cout << left << setw(15); 
		cout << city(src);
		PrintPath(parent, child, dest, dist, dest);

		// print the constructed distance array
		PrintSolution(dist, V, dest, src);
	}
}

// Function to check invalid integer number and limited number
int CheckInput(int input)
{
	bool correctInput = false;
	while (!correctInput) {
		while (!(cin >> input)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input.  Try again: ";
		}
		if (input >= 1 && input <= 10)
			correctInput = true;
		else {
			cout << "Please choose a number from 1 to 10: ";
		}
	}
	return input;
}


int main()
{
	/* The graph representation for 10 city distances */
	int graph[V][V] = { { 0, 470, 250, 0, 0, 0, 1185, 0, 0, 0 },
						{ 0, 0, 0, 0, 0, 0, 0, 800, 0, 555 },
						{ 250, 0, 0, 0, 720, 600, 1185, 0, 0, 0 },
						{ 0, 0, 0, 0, 0, 0, 0, 810,925, 1250 },
						{ 0, 0, 720, 0, 0, 215, 0, 0, 0, 0 },
						{ 0, 0, 0, 0, 215, 0, 915, 0, 0, 1190 },
						{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						{ 0, 0, 925, 810, 0, 0, 0, 0, 1030, 0 },
						{ 0, 0, 0, 0, 0, 0, 0, 1030, 0, 0 },
						{ 0, 555, 0, 1250, 0, 1190, 0, 0, 0, 0 }
	};
	// Display the list of cities
	for (int i = 0; i < V; i++) {
		cout << i + 1 << ". " << city(i) << endl;
	}
	int from=0, to=0;
	string confirm;

	do {
		cout << "\nChoose a city number you want to fly from: "; 
		from = CheckInput(from);
	
		cout << "\nChoose a city number you want to fly to: "; 
		to = CheckInput(to);
		while (to == from) {
			cout << "You chose the same city, please pick a difference city: ";
			to = CheckInput(to);
		}
		Dijkstra(graph, from-1, to-1);
		cout << "Would you like to continue (Y/N) ?";
		cin >> confirm;

	} while (confirm == "Y" || confirm == "y");

	system("pause");
	return 0;
}