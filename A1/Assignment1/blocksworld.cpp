#include <iostream>
#include <unistd.h>
#include <string>
#include <stdint.h>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <cstring>
#include "state.h"
#include "node.h"

using namespace std;

// Goal: Implement A* Search to solve "Blocksworld" AI search
// write a program that could solve random instances of problem 
// Implementation must be based on itreative algorithm (Graph Seach)
// and Priority Queue
// Develop a heuristic, h(n) to improve efficiency

// class blocksworld {
    
// };

void aStar (vector<string> inState, vector<string> gState, unsigned int MAX_iterationS, string fileName) {

    State* initialState = new State(inState); 
    State* goalState = new State(gState);
    Node* initialNode = new Node(nullptr, initialState, goalState, 0);

    // if (initialNode->goalCheck(goalState)) {
    //     cout << "At the goal state!" << endl;
    //     cout << "Done!" << endl;
    //     return;
    // }
    
    //Queue and Map 
    priority_queue<Node*, vector<Node*>, CompareScore> frontier;
    unordered_map<string, Node*> reached;

    frontier.push(initialNode);
    reached[initialNode->hash()] = initialNode;
    
    Node* childNode;
    vector<Node*> childrenNode;
    int maxQ = 0;
    int iteration = 0;
    
    while(!frontier.empty() && iteration < MAX_iterationS) {

        if (frontier.size() > maxQ) {
            maxQ = frontier.size();
        }

        initialNode = frontier.top();
        frontier.pop();
        childrenNode = initialNode->successors();

        for (int i = 0; i < childrenNode.size(); i++) {

            childNode = childrenNode.at(i);

            // Reached GoalState
            if (childNode->goalCheck(goalState)) {
                cout << "Success! iteration=" << iteration << ", cost=" << childNode->score << ", depth=" << childNode->pathDistance << ", max queue size=" << maxQ << endl;
                childNode->printPath();
                cout << "statistics: " << fileName << " method Astar " << "H1" << " planlen " << childNode->score << " iter " <<  iteration << " maxq " << maxQ;
                return;
            }
            
            try {
                if (childNode->score < reached.at(childNode->hash())->score) {
                    reached[childNode->hash()] = childNode;    
                    frontier.push(childNode);
                }
            } catch (out_of_range& e){
                reached[childNode->hash()] = childNode;    
                frontier.push(childNode);
            }
        }

    iteration++;

    }
    // Run through loop if can not find solution return failed
    cout << "statistics: " << fileName << " method Astar " << "H1" << " planlen " << "FAILED" << " iter " <<  iteration << " maxq " << maxQ;
    
    //cout << "Failed: No solution is able to solve in " << MAX_iterationS << endl;
}



int main(int argc,  char **argv) {
    // argv[0] is the program name in this instance "blocksworld"
    string fileName = argv[1];

    // Default 
    string h = "H1";
    unsigned int MAX_iterationS = 100000;

    for(int i = 2; i < argc - 1; i+=2) {
        if(strcmp( argv[i], "-H") == 0)
            h = argv[i+1];
        else if(strcmp( argv[i],"-MAX_ITERS ") == 0)
            MAX_iterationS = atoi(argv[i+1]);
    }

    // Flags

    ifstream inputFile(fileName, ios::in);
    
    // Data gather
    int num_stack, num_block, num_move;
    string line;

    getline(inputFile, line);
    std::istringstream input(line);
    input >> num_stack;
    input >> num_block;
    input >> num_move;
    
    //cout << num_stack << num_block << num_move << endl;

    // Skip Separator line
    getline(inputFile, line);
    // Initialize the states 
    vector<string> startStack, goalStack;

    for (int i = 0; i < num_stack; i++) {
        getline(inputFile, line);
        startStack.push_back(line);
    }

    // Skip Separator line
    getline(inputFile, line);

    for (int i = 0; i < num_stack; i++) {
        getline(inputFile, line);
        goalStack.push_back(line);
    }

    aStar(startStack, goalStack, MAX_iterationS, fileName);

    
    // startStack = createState(inputFile, num_stack);
    // goalStack = createState(inputFile, num_stack);

    return 0;
}


//FILE *file_handler = fopen(argv[1], "r"); // "r" is to read-only
// if (!file_handler) {
//     fprintf(stderr, "Error opening file '%s'\n", argv[1]);
//     return EXIT_FAILURE;
// }fclose(file_handler);
//char buff[BUFSIZE];