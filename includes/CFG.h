#ifndef CFG_H
#define CFG_H

#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <list>
#include <iostream>

// BasicBlock node
struct Node {
    std::string label;
    int id;
};

// Control Flow Graph
// Nodes are basic blocks
class CFG {
public:
    // empty cfg
    CFG();
    // build cfg from assembly file
    CFG(std::string filename);

    // records nodes in nodes_, add edge to adj_
    void addEdge(const Node &from, const Node &to);
    // records node in nodes_
    void addNode(const Node &node);
    // returns true if label is in nodes_
    bool contains(std::string label);
    // returns id of node with label
    int getNode(std::string label);
    // returns label of node with id
    std::string getNode(int id);

    // prints nodes_
    void printNodes();
    // prints adj_
    void printGraph();

    void toDot(std::string filename);
    void toDot(std::ostream &out);

private:
    // adjacency list for nodes
    std::vector<std::list<int> > adj_;
    std::vector<std::string> nodes_;

    // Parses assembly file and builds CFG
    void parseAssembly(std::string filename);
};

#endif