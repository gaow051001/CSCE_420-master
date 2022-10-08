#include "node.h"
#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

Node::Node(Node* pt, State* cs, State* gs, int pd) {
    parent = pt;
    currentState = cs;
    goalState = gs;
    pathDistance = pd;
    score = pd + cs->heuristic(*gs);

}

bool Node::goalCheck(State* cmp) {
    return currentState->compare(cmp);
}

vector<Node*> Node::successors() {
    
    vector<State*> childStates = currentState->successors();
    vector<Node*> childNodes;

    for (int i = 0; i < childStates.size(); i++) {
        Node* childNode = new Node(this, childStates.at(i), this->goalState, this->pathDistance+1);
        childNodes.push_back(childNode);
    }

    return childNodes;

}

string Node::hash() {
    return currentState->hash();
}

int Node::printPath() {
    if (this->parent) {
        this->parent->printPath();
    }

    cout << "move " << pathDistance << ", pathcost=" << pathDistance << ", heuristic=" << "1" << ", f(n) = g(n) + h(n) =" << score << endl;
    this->currentState->print();

    return 1;
}