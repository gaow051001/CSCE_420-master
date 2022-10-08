#ifndef NODE_H
#define NODE_H


#include <string>
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>
#include <queue>
#include "state.h"

using namespace std;

class Node{

    public:
        Node* parent;
        State* currentState;
        State* goalState;
        int pathDistance;
        float score;

        Node() : parent(nullptr), currentState(nullptr), pathDistance(0) {};
        Node(Node* pt, State* cs, State* gs, int pd);
        bool goalCheck(State*);
        vector<Node*> successors();
        string hash();
        int printPath();
};

struct CompareScore {
    bool operator()(Node const *n1, Node const *n2) {
        return n1->score > n2->score;
    }

};


#endif