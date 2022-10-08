#include <vector>
#include <string>
#include <stdexcept>

#ifndef PARSER_H
#define PARSER_H

using namespace std;

class Literal{
    public:
        string symbol;
        bool isNegative;

        Literal(string symbol, bool isNegative);
};

class Clause {
    public:
        vector<Literal> literals;
        void printLiteral();

};

vector<Clause> load_kb(string fname);

void show_kb(vector<Clause>& KB);

class SyntaxError : public runtime_error
{
public:
  SyntaxError(string s);
};

class RuleApplicationError : public runtime_error
{
public:
  RuleApplicationError(string s);
};

#endif

