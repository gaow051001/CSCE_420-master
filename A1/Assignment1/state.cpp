#include "state.h"
#include "node.h"

void State::print() {
    for (unsigned int i = 0; i < current.size(); i++) {
        cout << current.at(i) << endl;
    }
    cout << ">>>>>>>>>>>>>>>" << endl;
}

string State::hash() {
    string currentHash = "";
    for (int i = 0; i < current.size(); i++) {
        currentHash += current.at(i) + ";";
    }
    return currentHash;
}

bool State::compare(State* cmp) {

    if (cmp->current.size() != current.size()) {
        return false;
    }
    
    else {
        for (int i = 0; i < current.size(); i++) {
            if (current.at(i) != cmp->current.at(i)) {
                return false;
            }
        }
        return true;
    }
}

vector<State*> State::successors() {
    vector<State*> child;
    for (int i = 0; i < current.size(); i++) {
        for (int j = 0; j < current.size(); j++) {
            if (i == j) {
                j++;
            } else {
                State* child_take = new State(current);
                if (child_take->current.at(j).size() > 0) {
                    child_take->current.at(i).push_back(child_take->current.at(j).back());
                    child_take->current.at(j).pop_back();
                    child.push_back(child_take);
                }

                State* child_give = new State(current);
                if (child_give->current.at(i).size() > 0) {
                    child_give->current.at(j).push_back(child_give->current.at(i).back());
                    child_give->current.at(i).pop_back();
                    child.push_back(child_give);
                }
                
            }
        }
    }
    return child;
}

float State::heuristic(State& goal) {

    bool correctStack = true; 
    int currentLoc = 0;
    int distance = 0;
    float weight = 0;
    
    // Loop through stack state and determine the distance between current vs goal state
    // Weight is add to those with incorrect order in stack
    for (int i = 0; i < current.size(); i++) {

        if (current.at(i).length() > goal.current.at(i).length()) { 
            currentLoc = goal.current.at(i).length(); 
            distance = current.at(i).length() - goal.current.at(i).length();        
        } else {
            currentLoc = current.at(i).length();
        }
    
        for (int j = 0; j < currentLoc; j++) {                                       
            if (current.at(i).at(j) == goal.current.at(i).at(j)) {            
                if (!correctStack) {
                    weight += 4;
                }
            } else {                                                         
                weight += 2;
                correctStack = false;
            }
            for (int l = 0; l < currentLoc; l++) {                                  
                if(l != j && current.at(i).at(j) == goal.current.at(i).at(l)) { 
                    weight += 2;
                }
            }
        }
        
        weight += (2*distance); 
        correctStack = true;
        distance = 0;
    }

    return weight;
}