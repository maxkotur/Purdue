#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include "graph.cpp"

using namespace std;


// Part 1 : Find the connected components and the bridge
void part1(ifstream &inputfile, ofstream &outputfile) {
  int v, e;
  inputfile >> v >> e;
  Graph graph(v, e);
  for (int i = 0; i < e; i++) {
    string cityA, cityB;
    double cost;
    inputfile >> cityA >> cityB >> cost;
    graph.addRoute(cityA, cityB, cost);
  }
  int con = graph.returns();
  vector<pair<string, string>> sep = graph.sepReturn();
  int num = sep.size();
  outputfile << con << "\n";
  outputfile << num << "\n";
  for (int i = 0; i < sep.size(); i++) {
    if (sep[i].first.compare(sep[i].second) > 0) {
      string temp = sep[i].first;
      sep[i].first = sep[i].second;
      sep[i].second = temp;
    }
  }
  sort(sep.begin(), sep.end());
  for (int i = 0; i < sep.size(); i++) {
    outputfile << sep[i].first << " " << sep[i].second;
    if (i != sep.size()-1) {
      outputfile << '\n';
    }
  }
}

// Part 2 :  Find a ticket using Dijkstra
void part2(ifstream &inputfile, ofstream &outputfile) {
  int v, e;
  inputfile >> v >> e;
  Graph graph(v, e);
  for (int i = 0; i < e; i++) {
    string cityA, cityB;
    double cost;
    inputfile >> cityA >> cityB >> cost;
    graph.addRoute(cityA, cityB, cost);
  }
  string source;
  string destination;
  inputfile >> source;
  if (source == "END") {
    return;
  }
  inputfile >> destination;
  double cost = graph.findCost(source, destination);
  if (cost == -1) {
    outputfile << "not found";
  }
  else {
    for (int i = graph.getPath().size() - 1; i > -1; i--) {
      outputfile << graph.getPath()[i] << " ";
    }
    int z = cost;
    double a = cost - z;
    string c = to_string(a);
    c = c.substr(0, 4);
    outputfile << cost;
    string y = c.substr(c.length()-1, c.length());
    if (c == "0.00") {
      outputfile << ".00";
    }
    else if (y == "0") {
      outputfile << "0";
    }
  }
  while (1) {
    inputfile >> source;
    if (source == "END") {
      return;
    }
    outputfile << "\n";
    inputfile >> destination;
    double cost = graph.findCost(source, destination);
    if (cost == -1) {
      outputfile << "not found";
    }
    else {
      for (int i = graph.getPath().size() - 1; i > -1; i--) {
        outputfile << graph.getPath()[i] << " ";
      }
      int z = cost;
      double a = cost - z;
      string c = to_string(a);
      outputfile << cost;
      c = c.substr(0, 4);
      string y = c.substr(c.length()-1, c.length());
      if (c == "0.00") {
        outputfile << ".00";
      }
      else if (y == "0") {
        outputfile << "0";
      }
    }
  }
}

// Part 3 :Try to do a tour of all cities
void part3(ifstream &inputfile, ofstream &outputfile) {
  int v, e;
  inputfile >> v >> e;
  Graph graph(v, e);
  for (int i = 0; i < e; i++) {
    string cityA, cityB;
    double cost;
    inputfile >> cityA >> cityB >> cost;
    graph.addRoute(cityA, cityB, cost);
  }
  string source;
  inputfile >> source;
  vector<string> eul = graph.PrimMST(source);
  if (eul.size() == v) {
    for (int i = 0; i < eul.size(); i++) {
      outputfile << eul[i];
      if (i != eul.size()-1) {
        outputfile << '\n';
      }
    }
  }
  else {
    outputfile << "not found";
  }
}

 int main(int argc, char *argv[])
 {
	//Read in the test case
    ifstream inputfile;
    ofstream outputfile;

    if(argc==3){
        inputfile.open(argv[1]);
        outputfile.open(argv[2]);
    }
    else{
        cout<<"Not enough arguments"<<endl;
    }

    string str;

    getline(inputfile, str);
    int part;
    stringstream convert(str);
    convert >> part;


	 if(part == 1) part1(inputfile, outputfile);
	 else if(part == 2) part2(inputfile, outputfile);
	 else if(part == 3) part3(inputfile, outputfile);

	 return 0;
 }
