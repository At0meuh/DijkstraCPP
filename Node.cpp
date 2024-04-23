#include "Node.h"

Node::Node() = default;

Node::Node(string n)
{
    setName(n);
}

Node::Node(string na, const vector<pair<Node*, int>>& n)
{
    setName(na);
    neighbors = n;
}

Node::Node(string na,Node* n, int w)
{
    setName(na);
    addNeighbor(n,w);
}

vector<pair<Node*, int>> Node::getNeighbors()
{
    return neighbors;
}

void Node::addNeighbor(Node* n, int w)
{
    neighbors.emplace_back(n,w);
    n->neighbors.emplace_back(this,w);
}

void Node::addNeighbor(vector<pair<Node*, int>> n)
{
    for(pair<Node*,int> p : n)
    {
        neighbors.emplace_back(p);
        p.first->addNeighbor(this,p.second);
    }
}



void Node::showNeighbors()
{
    cout<<getName()<<" neighbors : {";
    for(pair<Node*,int> p : neighbors)
    {
        cout<<"("<<p.first->getName()<<";"<<p.second<<")";
    }
    cout<<"}";
}

string Node::getName() const
{
    return name;
}

void Node::setName(const string& n)
{
    name = n;
}