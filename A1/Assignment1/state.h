#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

class State {
    private:
    //     int num_stack;
    //     string hashValue;
    vector<string> current;
    
    public:
        State(vector<string> state): current(state) {};
        void print();
        bool compare(State* s);
        string hash(); // create unique hash to differentiate and track each state visited
        vector<State*> successors(); 
        float heuristic(State& goal);
};





#endif