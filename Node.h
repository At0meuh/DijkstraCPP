#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;

class Node
{
private:
	string name;
	vector<pair<Node*,int>> neighbors;

public:
	Node();
	Node(string);
	Node(string,const vector<pair<Node*,int>>&);
	Node(string,Node*,int);

	string getName()const;
	void setName(const string& n);
	
	vector<pair<Node*, int>> getNeighbors();
	
	void addNeighbor(Node*, int);
	void addNeighbor(vector<pair<Node*,int>>);
	
	void showNeighbors();

	bool operator==(const Node& n2) const {
		return name == n2.getName();
	}
};

