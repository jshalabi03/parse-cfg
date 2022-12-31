#include <fstream>
#include <iostream>

#include "CFG.h"
#include "FileUtil.h"

CFG::CFG() {
}

CFG::CFG(std::string filename) {
    parseAssembly(filename);
}

void CFG::addEdge(const Node &from, const Node &to) {
    adj_[from.id].push_back(to.id);
    nodes_[from.id] = from.label;
    nodes_[to.id] = to.label;
}

void CFG::addNode(const Node &node) {
    nodes_[node.id] = node.label;
}

bool CFG::contains(std::string label) {
    for (std::string node : nodes_)
        if (node == label) return true;

    return false;
}

int CFG::getNode(std::string label) {
    for (int i = 0; i < nodes_.size(); ++i)
        if (nodes_[i] == label) return i;

    return -1;
}

std::string CFG::getNode(int id) {
    return nodes_[id];
}

void CFG::printGraph() {
    for (int i = 0; i < adj_.size(); ++i) {
        std::cout << nodes_[i] << ": ";
        for (int j : adj_[i]) {
            std::cout << nodes_[j] << " ";
        }
        std::cout << std::endl;
    }
}

void CFG::printNodes() {
    for (int i = 0; i < nodes_.size(); ++i) {
        std::cout << nodes_[i] << ": " << i << std::endl;
    }
}

void CFG::toDot(std::string filename) {
    std::ofstream out(filename);
    this->toDot(out);
    out.close();
}

void CFG::toDot(std::ostream &out) {
    out << "digraph CFG {" << std::endl;
    for (int i = 0; i < adj_.size(); ++i) {
        for (int j : adj_[i]) {
            out << "\t" << "\"" << nodes_[i] << "\"" << " -> " << "\"" << nodes_[j] << "\"" << std::endl;
        }
    }
    out << "}" << std::endl;
}

void CFG::parseAssembly(std::string filename) {
    // TEMPORARY DATA STRUCTURES TO BUILD CFG
    std::unordered_map<int, std::list<int> > tmp_adj_;
    std::unordered_map<int, std::string> tmp_nodes_;

    // TMP HELPERS
    auto tmpContainsLabel = [&](std::string label) {
        for (std::pair<int,std::string> node : tmp_nodes_) {
            if (node.second == label) return true;
        }
        return false;
    };

    auto tmpAddNode = [&](Node node) {
        tmp_nodes_[node.id] = node.label;
    };

    auto tmpGetNodeID = [&](std::string label) {
        for (std::pair<int,std::string> node : tmp_nodes_) {
            if (node.second == label) return node.first;
        }
        return -1;
    };

    auto tmpGetNodeLabel = [&](int id) {
        return tmp_nodes_[id];
    };

    auto tmpAddEdge = [&](Node from, Node to) {
        tmp_adj_[from.id].push_back(to.id);
        tmp_nodes_[from.id] = from.label;
        tmp_nodes_[to.id] = to.label;
    };

    // PARSE FILE, POPULATE TMP ADJ AND NODES
    std::ifstream file(filename);
    std::string line;
    int id = 0;
    Node curr_node;
    while (std::getline(file, line)) {
        if (isComment(line)) {
            continue;
        } else if (isLabel(line)) {
            curr_node.label = getLabel(line);
            if (!tmpContainsLabel(curr_node.label)) {
                curr_node.id = id++;
                tmpAddNode(curr_node);
            } else {
                curr_node.id = tmpGetNodeID(curr_node.label);
            }
        } else if (isJumpInstruction(line)) {
            Node next_node;
            next_node.label = getJumpDestination(line);
            if (!tmpContainsLabel(next_node.label)) {
                next_node.id = id++;
                tmpAddNode(next_node);
            } else {
                next_node.id = tmpGetNodeID(next_node.label);
            }
            tmpAddEdge(curr_node, next_node);
        }
    }

    // HELPER FOR REMOVING LONE NODES
    auto nodeExistsInTmpAdj = [&](int id) {
        for (std::pair<int,std::list<int> > from : tmp_adj_) {
            for (int to : from.second) {
                if (to == id) return true;
            }
        }
        return false;
    };

    // RECORD LONE NODES
    std::vector<int> to_remove;
    for (std::pair<int,std::string> node : tmp_nodes_) {
        if (tmp_adj_.find(node.first) != tmp_adj_.end()) continue;

        if (!nodeExistsInTmpAdj(node.first)) {
            to_remove.push_back(node.first);
        }
    }

    // REMOVE LONE NODES
    for (int i : to_remove) {
        tmp_nodes_.erase(i);
    }

    // POPULATE NODES
    std::unordered_map<int,int> new_labels;
    for (int i = 0; i < tmp_nodes_.size(); ++i) {
        if (tmp_nodes_[i] != "") {
            if (i != nodes_.size()) {
                new_labels[i] = nodes_.size();
            }
            nodes_.push_back(tmp_nodes_[i]);
        }
    }

    // POPULATE ADJ
    adj_ = std::vector<std::list<int>>(nodes_.size());
    for (std::pair<int,std::list<int> > from : tmp_adj_) {
        if (new_labels.find(from.first) != new_labels.end()) {
            from.first = new_labels[from.first];
        }
        for (int to : from.second) {
            if (new_labels.find(to) != new_labels.end()) {
                to = new_labels[to];
            }
            adj_[from.first].push_back(to);
        }
    }
}