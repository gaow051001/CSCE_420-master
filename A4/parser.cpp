#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sstream> 
#include <fstream>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

#include "parser.h"

Literal::Literal(string symbol, bool isNegative) : symbol(symbol), isNegative(isNegative) {}

void Clause::printLiteral() {
  for (Literal index: literals) {
    cout << (index.isNegative ? "-" : "") << index.symbol << " ";
  }
  cout << endl;
}

vector<Clause> load_kb(string fname) {
  vector<Clause> KB;
  ifstream input;
  input.open(fname);
  string line;
  while (getline(input,line)) { 
    istringstream iss(line);
    vector<string> tokens;
    Clause sentence;
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));

    if(tokens.at(0)[0] == '#' || !tokens.size()) {
      continue;
    } 
    
    for (string token: tokens) {
      //cout << token[0] << endl;
      //cout << token << endl;
      if(token[0] != '#') {
        sentence.literals.push_back(Literal((token[0] == '-' ? token.substr(1, string::npos) : token) ,token[0] == '-'));
      } 
    }
    KB.push_back(sentence);
  }
  return KB;
}

void show_kb(vector<Clause>& KB) {
  for (unsigned int i = 0 ; i<KB.size() ; i++) {
    cout << i << ". ";
    KB[i].printLiteral();
    //cout <<  << endl;
  }
}

SyntaxError::SyntaxError(string s) : runtime_error{"Syntax Error: "+s} {} 

RuleApplicationError::RuleApplicationError(string s) : runtime_error("Rule Application Error: "+s) {} 
