#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Graph
{
	private:
		int numCities;
		int numRoutes;
		map<string, vector<pair<string, double>>> cities;
		vector<pair<string, string>> sepEdges;
		vector<string> path;
		vector<string> euler;

	public:
		Graph(int, int);
		// Create the graph
		void addRoute(string, string, double);

		//part 1: Find the connected components and the bridges
		int analyseGraph();
		int returns();
		vector<pair<string, string>> sepReturn();

		// Part 2: Find a ticket using Dijkstra
		double findCost(string source, string destination);
		vector<string> getPath();

		// Part 3: Try to do a tour of all cities
		vector<string> PrimMST(string);
		map<string, vector<string>> constructMST(vector<pair<string, string>>);
		void eulerianTour(map<string, vector<string>>, string, 
			map<string, bool>);
		// NOTE : If necessary, you can change the
		//parameters to this function.

};

#endif
