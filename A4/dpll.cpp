#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "parser.h"

using namespace std;


typedef unordered_map<string, bool> MODEL;
enum Eval { FALSE, TRUE, MAYBE};
bool unitClauseFlag = true;
int DPLL_calls = 0;

void printModel(MODEL* model, vector<string> symbols) {
  for (unsigned int i = 0; i < symbols.size(); i++) {
    cout << symbols.at(i) << "=";
    if(model->find(symbols.at(i)) == model->end()) {
      cout << "? ";
    } else {
      //cout << model->at(symbols.at(i)) << endl;
      if (model->at(symbols.at(i))) {
        cout << "T ";
      } else {
        cout << "F ";
      }
    }
  }
  cout << endl;
  cout << "true props: ";
  //Get all True Propositions
  for (unsigned int i = 0; i < symbols.size(); i++) {
    if (model->find(symbols.at(i)) == model->end()) {
      continue;
    } else {
      if (model->at(symbols.at(i)) == TRUE) {
        cout << symbols.at(i) << " ";
      }
    }
  }

  cout << endl;
}

vector<string> obtainSymbols(vector<Clause> clauses) {
  MODEL model;
  vector<string> symbols;
  for (unsigned int i = 0; i < clauses.size(); i++) {
    vector<Literal> tokens = clauses[i].literals;
    for (unsigned int j = 0; j < tokens.size(); j++) {
      if (model.find(tokens[j].symbol) == model.end()) {
        model.insert(make_pair(tokens[j].symbol,true));
        symbols.push_back(tokens[j].symbol);
      }
    }
  }
  return symbols;
}

Eval Satisfies(Clause statement, MODEL* model) {
  vector<Literal> temp = statement.literals;
  vector<string> regularSymbol;
  vector<string> negativeSymbol;

  for (unsigned int i = 0; i < temp.size(); i++) {
    if(temp[i].isNegative == TRUE) {
      negativeSymbol.push_back(temp[i].symbol);
    } else {
      regularSymbol.push_back(temp[i].symbol);
    }
  }

  // evaluate statements
  Eval symbolConsistent = FALSE;
  bool hasUnassignedSymbol = false;

  for (string str : regularSymbol) {
    if (model->find(str) == model->end()) {
      hasUnassignedSymbol = true;
    } else if (model->at(str) == true) {
      symbolConsistent = TRUE;
    }
  }
    
  for (string negStr : negativeSymbol) {
    if (model->find(negStr) == model->end()) {
      hasUnassignedSymbol = true;
    }else if (model->at(negStr) == false) {
      symbolConsistent = TRUE;
    }
  }
    
  if (symbolConsistent == FALSE && hasUnassignedSymbol) {
    symbolConsistent = MAYBE;
  }
  return symbolConsistent;
}

unsigned int numSatClauses(vector<Clause> clauses, MODEL* model) {
  unsigned int satClauses = 0;
  for(Clause ex : clauses) {
    if(Satisfies(ex, model) == TRUE) {
      satClauses++;  
    }
  }
  return satClauses;
}

bool hasFalseClauses(vector<Clause> clauses, MODEL* model) {
  for (Clause ex : clauses) {
    if(Satisfies(ex, model) == FALSE) {
      return true;
    }
  }
  return false;
}

MODEL* deepCopy(MODEL* previousModel) {
  MODEL* newModel = new MODEL();
  for(auto it : *previousModel)
    newModel->insert(it);

  return newModel;
}

pair<string, Eval> findUnitLiteral(Clause statement, vector<string> symbols, MODEL* model) {
  if (Satisfies(statement, model) != MAYBE) {
    return make_pair("",FALSE);
  }
    
  vector<Literal> temp = statement.literals;
  vector<string> regularSymbol;
  vector<string> negativeSymbol;

  for (unsigned int i = 0; i < temp.size(); i++) {
    if (temp[i].isNegative == TRUE) {
      negativeSymbol.push_back(temp[i].symbol);
    }
    else {
      regularSymbol.push_back(temp[i].symbol);
    }
  }

  unsigned int unassignedSymbol = 0;
  string unitSymbolName = "";
  Eval unitSymbolValue = FALSE;

  for (string str : regularSymbol) { // find any positive unassigned symbol
    if (model->find(str) == model->end()) {
      unassignedSymbol++;
      unitSymbolName = str;
      unitSymbolValue = TRUE;
    }
  }
    

  for (string negStr : negativeSymbol) {  // find any negative unassigned symbol
    if (model->find(negStr) == model->end()) {
      unassignedSymbol++;
      unitSymbolName = negStr;
      unitSymbolValue = FALSE;
    }
  }

  if (unassignedSymbol == 1) {
    return make_pair(unitSymbolName, unitSymbolValue);
  } else {
    return make_pair("",FALSE);
  }

}

pair<string, Eval> nextSymbols(vector<Clause> clauses, vector<string> symbols, MODEL* model) {
  if (unitClauseFlag) {
    for (unsigned int i = 0; i < clauses.size(); i++) {
      pair<string,Eval> unitLiteral = findUnitLiteral(clauses[i], symbols, model);
      if(unitLiteral.first != "")
        return unitLiteral;
    }
  }

  for (unsigned int i = 0; i < symbols.size(); i++) {
      if(model->find(symbols.at(i)) == model->end()) {
        return make_pair(symbols.at(i), MAYBE);
      } 
  }

  cout << "Error" << endl;
  return make_pair("",MAYBE);
}

MODEL* DPLL(vector<Clause> clauses, vector<string> symbols, MODEL* model) {
  ++DPLL_calls; // Iterations Called
  //printModel(model, symbols);
  //cout << "Amount of clauses satisfied: " << numSatClauses(clauses, model) << "/" << clauses.size() << endl;
  
  if (numSatClauses(clauses, model) == clauses.size()) {
    return model;
  }

  if (hasFalseClauses(clauses, model)) {
    //cout << "back-tracking..." << endl;
    return nullptr;
  }

  // NOTE: Eval=TRUE/FALSE is "forced", Eval=MAYBE is "trying"
  pair<string,Eval> newSymbol = nextSymbols(clauses, symbols, model);
  MODEL* newModelFalse = deepCopy(model);
  MODEL* newModelTrue = deepCopy(model);

  if (newSymbol.second != MAYBE) {
    if (newSymbol.second == TRUE) {
      //cout << "Force Symbol " << newSymbol.first << " = true" << endl << endl;
      newModelTrue->insert(make_pair(newSymbol.first,true));
      return DPLL(clauses, symbols, newModelTrue);
    }
    else if (newSymbol.second == FALSE) {
      //cout << "Force Symbol " << newSymbol.first << " = false" << endl << endl;
      newModelFalse->insert(make_pair(newSymbol.first,false));
      return DPLL(clauses, symbols, newModelFalse);
    }    
  } else {
    newModelFalse->insert(make_pair(newSymbol.first,false));
    newModelTrue->insert(make_pair(newSymbol.first,true));
    // Test the Model with force Truth/False
    //cout << "Try " << newSymbol.first << " = false" << endl << endl;
    MODEL* falseModel = DPLL(clauses, symbols, newModelFalse);

    if(falseModel != nullptr) {
      return falseModel;
    }

    //cout << "Try " << newSymbol.first << " = true" << endl << endl;
    MODEL* trueModel = DPLL(clauses, symbols, newModelTrue);

    return trueModel;
  }
  cout << "Error: Flag" << endl;
  return nullptr;
}

int main(int argc, char* argv[]) {
  if (argc != 2 && argc != 3) {
    cout << "Wrong input arguments: please use the form ./dpll <*.cnf> <optional: -unit>" << endl;
    exit(1);
  }

  if (argc == 3) {
    string flag = argv[2];
    if (flag == "-UCH") {
      unitClauseFlag = false;
    }
  }

  try {
    cout << "*** DPLL ***" << endl;
    vector<Clause> KB = load_kb(argv[1]); // load KB
    
    show_kb(KB); // print KB
    cout << "...tracing info..." << endl;

    cout << endl;

    if (unitClauseFlag) {
      cout << "Running with Unit Clause Heuristic" << endl;
    } else {
      cout << "Running without Unit Clause Heuristic" << endl; 
    }

    cout << endl;
        
    vector<string> symbols = obtainSymbols(KB); // obtain all symbols in KB
    MODEL* model = new MODEL(); // empty model
    MODEL* goalModel = DPLL(KB, symbols, model); // Recursion-DPLL
    
    if (goalModel != nullptr) { // print results
      cout << endl;
      cout << "success! found a model" << endl;
      cout << "model: ";
      printModel(goalModel, symbols);
      cout << "DPLL_calls: " << DPLL_calls << endl;
    } else {
      cout << "failure! could not find a model" << endl;
      cout << "DPLL_calls: " << DPLL_calls << endl;
      cout << "Unsatisfiable Model" << endl;
    }
  } catch(const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}