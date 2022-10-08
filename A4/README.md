To run the Program, **(NOTE TESTED IN VSCODE - WINDOWS OS & TESTED ON compute.cs.tamu.edu)**

System CPU: Ryzen 5 5600X
RAM: 32GB
GPU: GEFORCE RTX 3080TI

- Run the makefile in correct Directory by typing in  "make"
- Continue by typing ```./dpll <cnf file> <optional: -UCH>```
- *CNF is locate in the KB folder
- ```-UCH``` option turns off the Unit Clause heuristic

**The program includes dpll.cpp, parser.h and parser.cpp that generate a model from DPLL to solve problem with Propositional Satisfiability:**

Also included: 
- ```Nqueens.py``` which generates Nqueen.cnf by ```python3 Nqueens.py X > Xqueens.cnf``` where **X** is the number of queens you want
- Transcript Folder that stores all the transcript for SAMMY, mapcolor1&2, and Nqueens CNF Satisfiability. 
- (** NOTE: for 6queens and 8queens, we turn off the each iteration of DPLL and its model, since it overflows the terminal**)
- RESULTS.txt shows the end results for the test


