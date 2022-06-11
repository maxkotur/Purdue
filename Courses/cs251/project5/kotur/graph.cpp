#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <bits/stdc++.h>
#include <algorithm>
#include <iterator>
#include "graph.h"

#define INFI 1000000



/*
	Graph class for use in Project 5.

	This provided code does not include any specific data structure
	for storing a graph, only a list of methods that will be called
	from main. Based on the project handout and the lecture slides,
	select a method for storing the graph and implement it here.

*/

// Constructor for Graph
Graph::Graph(int Vertices, int routes) {
  numCities = Vertices;
	numRoutes = routes;
}

void Graph::addRoute(string cityA, string cityB, double cost) {
	if (cities.find(cityA) == cities.end()) {
    vector<pair<string, double>> vect;
    vect.push_back(pair<string, double> (cityB, cost));
    cities.insert(pair<string, vector<pair<string, double>>> (cityA, vect));
  }
  else if (cities.find(cityA) != cities.end()) {
    cities.at(cityA).push_back(pair<string, double> (cityB, cost));
  }
  if (cities.find(cityB) == cities.end()) {
    vector<pair<string, double>> vect;
    vect.push_back(pair<string, double> (cityA, cost));
    cities.insert(pair<string, vector<pair<string, double>>> (cityB, vect));
  }
  else if (cities.find(cityB) != cities.end()) {
    cities.at(cityB).push_back(pair<string, double> (cityA, cost));
  }
	return;
}

int Graph::analyseGraph() {
	stack<string> s;
  map<string, string> m;
  map <string, string> :: iterator it;
	map<string, bool> disc;
	map<string, int> disTimes;
  map<string, int> evaFun;
  map<string, vector<pair<string, double>>>::iterator itr;
  string v;
  int num = 0;
  for (itr = cities.begin(); itr != cities.end(); ++itr) {
    if (num == 0) {
      v = itr->first;
      num++;
    }
    disc.insert(pair<string, bool> (itr->first, false));
		disTimes.insert(pair<string, int> (itr->first, INFI));
    evaFun.insert(pair<string, int> (itr->first, INFI));
  }
  stack<pair<string, int>> per;
  string parent = "NULL";
  string root = v;
	s.push(v);
	int connectedComp = 0;
	bool truth = false;
	sepEdges.clear();
	while (!truth) {
		connectedComp++;
		truth = true;
		int disTime = 0;
		while (!s.empty()) {
			v = s.top();
      s.pop();
      if (m.find(v) == m.end()) {
        m.insert(pair<string, string> (v, parent));
      }
      if (!disc.at(v)) {
        disc.at(v) = true;
        disTime++;
        disTimes.at(v) = disTime;
        if (disTime < evaFun.at(v)) {
          evaFun.at(v) = disTime;
        }
      }
      int count = 0;
      for (int i = 0; i < cities.at(v).size(); i++) {
        string u = cities.at(v)[i].first;
        if (!disc.at(u)) { // tree edge
          count++;
          s.push(u);
        }
        else if (disc.at(u) && u != parent) { // back edge
          if (evaFun.at(v) > disTimes.at(u)) {
            evaFun.at(v) = disTimes.at(u);
          }
          string temp = v;
          while (temp != root && m.at(temp) != u) {
            if (evaFun.at(m.at(temp)) > evaFun.at(temp)) {
              evaFun.at(m.at(temp)) = evaFun.at(temp);
            }
            temp = m.at(temp);
          }
        }
      }
      if (count > 1) {
        per.push(pair<string, int> (v, count));
      }
      if (s.size() != 0 && count == 0) {  
        parent = per.top().first;
        int pars = per.top().second - 1;
        per.pop();
        per.push(pair<string, int> (parent, pars));
        if (per.top().second == 0) {
          per.pop();
          string t = per.top().first;
          int pars = per.top().second - 1;
          per.pop();
          per.push(pair<string, int> (t, pars));
        }
      }
      else {
        parent = v;
      }
		}
		for (itr = cities.begin(); itr != cities.end(); ++itr) {
			if (!disc.at(itr->first)) {
				s.push(itr->first);
        while (!per.empty()) {
          per.pop();
        }
				truth = false;
				break;
			}
		}
	}
  for (it = m.begin(); it != m.end(); ++it) {
    if (it->second != "NULL" && evaFun.at(it->first) > disTimes.at(it->second)) {
      pair<string, string> p(it->second, it->first);
      sepEdges.push_back(p);
    }
  }
  return connectedComp;
}

/*
evaFun(v) = min { disc(v),
									min { evaFun(u) | (v , u) is a tree edge },
									min { disc(w) | (v , w) is a back edge}
								}
*/

int Graph::returns() {
  int num;
  num = analyseGraph();
  return num;
}

vector<pair<string, string>> Graph::sepReturn() {
  return sepEdges;
}

double Graph::findCost(string source, string destination) {
  priority_queue<pair<double, string>, vector<pair<double, string>>, 
  greater<pair<double, string>>> pq;
  map<string, bool> inMST;
  map<string, double> dist;
  map<string, string> parent;
  map<string, vector<pair<string, double>>>::iterator itr;
  pq.push(pair<double, string> (0, source));
  for (itr = cities.begin(); itr != cities.end(); ++itr) {
    if (itr->first != source) {
     pq.push(pair<double, string> (INFI, itr->first));
    }
    inMST.insert(pair<string, bool> (itr->first, false));
    dist.insert(pair<string, double> (itr->first, INFI));
  }
  parent.insert(pair<string, string> (source, ""));
  dist.at(source) = 0;
  while (!pq.empty()) {
    string v = pq.top().second;
    pq.pop();
    int size = cities.at(v).size();
    for (int i = 0; i < size; i++) {
      string u = cities.at(v)[i].first;
      double w = cities.at(v)[i].second;
      if (dist.at(u) > dist.at(v) + w) {
        dist.at(u) = dist.at(v) + w;
        if (parent.find(u) == parent.end()) {
          parent.insert(pair<string, string> (u, v));
        }
        else {
          parent.at(u) = v;
        }
        pq.push(pair<double, string> (dist.at(u), u));
      }
    }
  }
  string temp = destination;
  path.clear();
  path.push_back(destination);
  while (parent.at(temp) != "") {
    path.push_back(parent.at(temp));
    temp = parent.at(temp);
  }
  if (dist.at(destination) == INFI) {
    return -1;
  }
  return dist.at(destination);
}

vector<string> Graph::getPath() {
  return path;
}

vector<string> Graph::PrimMST(string source) {
  priority_queue<pair<double, string>, vector<pair<double, string>>, 
  greater<pair<double, string>>> pq;
  map<string, double> key;
  vector<pair<string, string>> parent;
  map<string, bool> inMST;
  map<string, bool> vis;
  map<string, vector<pair<string, double>>>::iterator itr;
  for (itr = cities.begin(); itr != cities.end(); ++itr) {
    key.insert(pair<string, double> (itr->first, INFI));
    if (itr->first != source) {
      parent.push_back(pair<string, string> (itr->first, ""));
      pq.push(pair<double, string> (INFI, itr->first));
    }
    
    inMST.insert(pair<string, bool> (itr->first, false));
    vis.insert(pair<string, bool> (itr->first, false));
  }
  pq.push(pair<double, string> (0, source));
  while (!pq.empty()) {
    string v = pq.top().second;
    pq.pop();
    if (inMST.at(v)) {
      continue;
    }
    inMST.at(v) = true;
    int size = cities.at(v).size();
    for (int i = 0; i < size; i++) {
      string u = cities.at(v)[i].first;
      double w = cities.at(v)[i].second;
      if (!inMST.at(u) && key.at(u) > w) {
        key.at(u) = w;
        pq.push(pair<double, string> (key.at(u), u));
        for (int j = 0; j < numCities; j++) {
          if (parent[j].first == u) {
            parent[j].second = v;
          }
        }
      }
    }
  }
  map<string, vector<string>> mst = constructMST(parent);
  euler.clear();
  eulerianTour(mst, source, vis);
  return euler;
}

map<string, vector<string>> 
Graph::constructMST(vector<pair<string, string>> parent) {
  map<string, vector<string>> mst;
  for (int i = 0; i < parent.size(); i++) {
    if (mst.find(parent[i].first) == mst.end()) {
      vector<string> vect;
      vect.push_back(parent[i].second);
      mst.insert(pair<string, vector<string>> (parent[i].first, vect));
    }
    else if (mst.find(parent[i].first) != mst.end()) {
      mst.at(parent[i].first).push_back(parent[i].second);
    }
    if (mst.find(parent[i].second) == mst.end()) {
      vector<string> vect;
      vect.push_back(parent[i].first);
      mst.insert(pair<string, vector<string>> (parent[i].second, vect));
    }
    else if (mst.find(parent[i].second) != mst.end()) {
      mst.at(parent[i].second).push_back(parent[i].first);
    }
  }
  return mst;
}

void Graph::eulerianTour(map<string, vector<string>> mst, string source,
map<string, bool> vis) {
  vis.at(source) = true;
  euler.push_back(source);
  vector<string> sorted;
  for (int i = 0; i < mst.at(source).size(); i++) {
    if (!vis.at( mst.at(source)[i])) {
      sorted.push_back(mst.at(source)[i]);
    }
  }
  sort(sorted.begin(), sorted.end());
  for (int i = 0; i < sorted.size(); i++) {
    eulerianTour(mst, sorted[i], vis);
  }
}



