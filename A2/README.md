To run the Program, **(NOTE TESTED IN VSCODE - WINDOWS OS & TESTED ON compute.cs.tamu.edu)**

System CPU: Ryzen 5 5600X
RAM: 32GB
GPU: GEFORCE RTX 3080TI

- Run the makefile in correct Directory by typing in  "make"
- Continue by typing "./ttt"


**All the command can be used**

- show: shows the current state of the board

- reset: resets the state of the board to empty (removes all the pieces)

- move P R C: put piece P (X or O) in row R (A, B, or C) and column C (1, 2, or 3)

- choose P: invoke Minimax to figure out the optimal place to put piece P on the board

- pruning: show the state of pruning (on or off)

- quit: exit the program

**The program includes ttt.cpp that generate a ttt class to keep track of the board state which houses the following function:**

 - void resetBoard(); // resets the game
  
 - void showBoard(); // show the current board state
  
 - void movePiece(char, char, int); // Player move
  
 - void movePieceAI(char, int, int); // AI move
  
 - void setBoard(const char board[3][3]); // set the board 
  
 - bool positionEmpty(int, int); // determine if position is empty
  
 - vector<pair<int,int>> legalMoves(); // return an list of generate possible moves for the current state
  
 - char winCondition(); // Determine if the current state has a winner or draw etc
  
 - float utility(int depth, char player, char notPlayer); // utility function to determine if leaf node terminal state
  



**Outside of the program we have recursive function:**

- pair<int, int> miniMaxAlphaBeta(ttt* state, int depth, char player); // function for miniMax
  
- pair<pair<int, int>, float> minscore(ttt state, int depth, char player, char notPlayer, float alpha, float beta); // function for minscore
  
- pair<pair<int, int>, float> maxscore(ttt state, int depth, char player, char notPlayer, float alpha, float beta); // funciton for maxscore
  
- bool gameOver(ttt* state, char player); //To determine if the game state is terminal 
  
 

