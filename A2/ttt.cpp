#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm> 

using namespace std;

int iteration = -1;

class ttt {
    //private:
        
        // Board coordinates
        // (A 1) (A 2) (A 3)
        // (B 1) (B 2) (B 3)
        // (C 1) (C 2) (C 3)

    public:
        ttt() = default;
        ttt(const ttt& copy);
        ttt& operator=(const ttt& copy);

        char board[3][3] = {{'.','.','.'},{'.','.','.'},{'.','.','.'}};
        bool pruning = false;
        //ttt() : board{{'.','.','.'},{'.','.','.'},{'.','.','.'}} {};
        void resetBoard();
        void showBoard();
        void movePiece(char, char, int); // Player
        void movePieceAI(char, int, int); // AI
        void setBoard(const char board[3][3]);
        bool positionEmpty(int, int);
        vector<pair<int,int>> legalMoves();
        char winCondition();
        
        float utility(int depth, char player, char notPlayer);
        void choosePiece(ttt state, char player);
};

pair<int, int> miniMaxAlphaBeta(ttt* state, int depth, char player);
pair<pair<int, int>, float> minscore(ttt state, int depth, char player, char notPlayer, float alpha, float beta);
pair<pair<int, int>, float> maxscore(ttt state, int depth, char player, char notPlayer, float alpha, float beta);

ttt::ttt(const ttt& copy) {
    this->setBoard(copy.board);
    this->pruning = copy.pruning;
}

ttt& ttt::operator=(const ttt& copy) {
    this->setBoard(copy.board);
    this->pruning = copy.pruning;
    return *this;
}

void ttt::resetBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '.';
        }
    }
}

void ttt::showBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// Player's Choice
void ttt::movePiece(char player, char row, int column) {
    //cout << "flag 1" << endl;
    if (player == 'X' || player == 'O') {
        
        int rowNum;
        

        if (row == 'A') {
            rowNum = 0;
        } else if (row == 'B') {
            rowNum = 1;
        } else if (row == 'C') {
            rowNum = 2;
        } else {
            cout << "Please enter a correct row A, B, or C" << endl;
            return;
        }

        if (column < 1 || column > 3) {
            cout << "Please enter a correct column 1, 2, or 3" << endl;
            return;
        }

        // since the board starts at 0
        column--; 

        // Check if the position is already filled
        if (positionEmpty(rowNum, column) == true) {
            board[rowNum][column] = player;
        } else {
            return;
        }

        
        //cout << "flag 2" << endl;
        showBoard();
    } else {
        cout << "Please enter a correct pieces X or O";
    }
}

void ttt::movePieceAI(char player, int row, int column) {
    board[row][column] = player;
}

void ttt::setBoard(const char board[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            this->board[i][j] = board[i][j];
        }
    }
}

bool ttt::positionEmpty(int row, int column) {
    if (board[row][column] == '.') {
        return true;
    }
    cout << "This position has already been Taken" << endl;
    return false;
}

vector<pair<int, int>> ttt::legalMoves() {

    vector<pair<int, int>> legalMovesList;
    //int pos = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            //pos++;
            if (board[i][j] == '.') {
                legalMovesList.push_back(make_pair(i,j));
            }
        }
    }
    return legalMovesList;
}

char ttt::winCondition() {
    // char copyBoard[3][3];
    // std::copy(&board[0][0], &board[0][0]+3*3,&copyBoard[0][0]);
    // board[row][col]
    // check all rows for win
    for (int i = 0; i < 3; i++) { 
        if (board[i][1] != '.' && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return board[i][1];
        }
    }

    // check all cols for win
    for (int j = 0; j < 3; j++) { 
        if (board[1][j] != '.' && board[0][j] == board[1][j] && board[0][j] == board[2][j]) {
            return board[1][j];
        }
    }

    // check all diagonals for win
    if (board[1][1] != '.' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return board[1][1];
    }

    if (board[1][1] != '.' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return board[1][1];
    }

    // check for all position filled for draw
    bool flag = true;
    for (int k = 0; k < 3; k++) {
        for (int l = 0; l < 3; l++) {
            if (board[k][l] == '.') {
                flag = false;
            }
        }
    }
    if (flag == false) {
        return 'C'; // Not all position filled
    } else {
        return 'D'; // All position filled -> Draw
    }
    
}

pair<int, int> miniMaxAlphaBeta(ttt* state, int depth, char player) {
    //char currentBoard[3][3] = board;
    //cout << "Flag miniMax" << endl;
    // initialize values

    // char copyBoard[3][3];
    // std::copy(&board[0][0], &board[0][0]+3*3,&copyBoard[0][0]);

    ttt currentBoard(*state);
    float alpha = -1*std::numeric_limits<float>::infinity();
    float beta = std::numeric_limits<float>::infinity();
    char currentPlayer = player;
    char notPlayer = (currentPlayer == 'X') ? 'O' : 'X';

    //cout << currentPlayer << endl;
    //cout << notPlayer << endl;

    pair<int, int> move; //= make_pair(-1, -1);
    float score; // = 0;
    pair<pair<int, int>, int> test = maxscore(currentBoard, -1, currentPlayer, notPlayer, alpha, beta);
    move = test.first;
    //score = test.second; 

    // if (purning == false) {

    // }
    return move;
}

pair<pair<int, int>, float> maxscore(ttt state, int depth, char player, char notPlayer, float alpha, float beta) {
    iteration++;
    //pair<int, int> move = make_pair(-1, -1);
    //depth++;

    // cout << endl;
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         cout << board[i][j];
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    // Terminal State
    //Flag 
    //cout << "Flag Maxscore" << endl;
    if (state.winCondition() != 'C') { // player == state.winCondition() || notPlayer == state.winCondition() || state.winCondition() == 'D'
        //cout << "flag max" << endl;
        pair<int, int> move = make_pair(-1, -1);
        // float testValue = utility(board, depth, player);
        // cout << testValue << endl;
        return make_pair(move, state.utility(depth, player, notPlayer)); 
    }

    float score = -1*std::numeric_limits<float>::infinity();
    pair<int, int> move;

    vector<pair<int,int>> legalMove = state.legalMoves();
    // cout <<  "Max" << endl;
    // for (int m = 0; m < legalMove.size(); m++) {
    //     cout << "(" << legalMove[m].first << ", " << legalMove[m].second << ")" << endl;
    // }
    // cout << endl;
    
    for (int i = 0; i < legalMove.size(); i++) {
        // char copyBoard[3][3];
        // std::copy(&board[0][0], &board[0][0]+3*3,&copyBoard[0][0]);
        // copyBoard[legalMove[i].first][legalMove[i].second] = player;
        ttt newState(state);
        newState.movePieceAI(player, legalMove[i].first, legalMove[i].second);
        float score2;
        //pair<int, int> move2; //= legalMove[i];
        // cout << endl;
        // for (int i = 0; i < 3; i++) {
        //     for (int j = 0; j < 3; j++) {
        //         cout << copyBoard[i][j];
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        //break;
        //return;

        pair<pair<int, int>, float> test = minscore(newState, depth + 1, player, notPlayer, alpha, beta);
        //move2 = test.first; 
        score2 = test.second; 

        //mm_score;
        if(depth == -1) {
            cout << "move (" << char(legalMove[i].first + 65) << "," << legalMove[i].second << ") mm_score: " << score2 << endl;
        }

        //cout << score2 << endl;
        if (score2 > score) {
            score = score2; 
            move = legalMove[i];
            //cout << "move " << move.first << " " << move.second << endl;
            alpha = std::max(alpha, score);
            //copyBoard[legalMove[i].first][legalMove[i].second] = ' ';
        } 

        if (state.pruning && score >= beta) {
            return make_pair(move, score);
        }
        //pair<int, int> currentMove = legalMove[i];
    }
    //cout << "move " << move.first << " " << move.second << endl;
    return make_pair(move, score);
}

pair<pair<int, int>, float> minscore(ttt state, int depth, char player, char notPlayer, float alpha, float beta) {
    iteration++;
    //pair<int, int> move = make_pair(-1, -1);
    //depth++;
    // cout << endl;
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         cout << board[i][j];
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    // Terminal State
    if (state.winCondition() != 'C') { //player == state.winCondition() || notPlayer == state.winCondition() || state.winCondition() == 'D'
        //cout << "flag max" << endl;
        pair<int, int> move = make_pair(-1, -1);
        // float testValue = utility(board, depth, player);
        // cout << testValue << endl;
        return make_pair(move, state.utility(depth, player, notPlayer)); 
    }

    float score = std::numeric_limits<float>::infinity();
    pair<int, int> move(-1,-1);

    vector<pair<int,int>> legalMove = state.legalMoves();

    // cout <<  "Min" << endl;
    // for (int m = 0; m < legalMove.size(); m++) {
    //     cout << "(" << legalMove[m].first << ", " << legalMove[m].second << ")" << endl;
    // }
    // cout << endl;

    for (int i = 0; i < legalMove.size(); i++) {
        ttt newState(state);
        newState.movePieceAI(notPlayer, legalMove[i].first, legalMove[i].second);
         // = legalMove[i];
        // char copyBoard[3][3];
        // std::copy(&board[0][0], &board[0][0]+3*3,&copyBoard[0][0]);
        // copyBoard[legalMove[i].first][legalMove[i].second] = notPlayer;//player;
        float score2;
        //pair<int, int> move2;
        // cout << endl;
        // for (int i = 0; i < 3; i++) {
        //     for (int j = 0; j < 3; j++) {
        //         cout << copyBoard[i][j];
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        //break;
        //return;

        pair<pair<int, int>, float> test = maxscore(newState, depth+1, player, notPlayer, alpha, beta);
        //move2 = test.first; 
        score2 = test.second;
        //cout << score2 << endl;
        if (score2 < score) {
            score = score2; 
            move = legalMove[i];
            beta = min(beta, score);
            //copyBoard[legalMove[i].first][legalMove[i].second] = ' ';
        } 

        if (state.pruning && score <= alpha) {
            return make_pair(move, score);
        }
        //pair<int, int> currentMove = legalMove[i];
    }
    //cout << "move " << move.first << " " << move.second << endl;
    return make_pair(move, score);
}

float ttt::utility(int depth, char player, char notPlayer) {
    //cout << "flag Utility" << endl;
    float point = 0.0;
    // char copyBoard[3][3];
    // std::copy(&board[0][0], &board[0][0]+3*3,&copyBoard[0][0]);
    char winningPlayer = winCondition();
    if (winningPlayer == 'D') {
        //cout << "flag u1" << endl;
        //return 0.0;
        //point = 0;
    } else if (winningPlayer == player) {
        //cout << "flag u2" << endl;//(1 - (0.1 * depth))
        //return ((float)1 - (0.1 * (float)depth));
        point = ((float)1 - (0.1 * (float)depth));
    } else if (winningPlayer == notPlayer) {
        //cout << "flag u3" << endl;
        //return ((float)-1 + (0.1 * (float)depth));
        point = ((float)-1 + (0.1 * (float)depth));
    } else {
        //cout << "flag u4" << endl;
        //return 0.0;
        //point = 0;
    }
    return point;
    
   
}

bool gameOver(ttt* state, char player) {
    if(state->winCondition() != 'C') {
        char currentPlayer = player;
        char notPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        float value = state->utility(0, currentPlayer, notPlayer);
        if(value == 1) {
            cout << "*** " << currentPlayer << " wins! ***" << endl;
        }
        else if(value == -1) {
            cout << "*** " << notPlayer << " wins! ***" << endl;
        }
        else {
            cout << "*** it's a draw! ***" << endl;
        }
        return true;
    }
    return false;
}

void ttt::choosePiece(ttt state, char player){
    //cout << "Flag ChoosePiece" << endl;
    // char copyBoard[3][3];
    // std::copy(&board[0][0], &board[0][0]+3*3,&copyBoard[0][0]);

    // cout << endl;
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         cout << copyBoard[i][j];
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    //ttt currentBoard(*state);

    //pair<int, int> move = miniMaxAlphaBeta(currentBoard, 0, player);
    // cout << move.first << " " << move.second << endl;
    // char row;
    // if (move.first == 0) {
    //     row = 'A';
    // } else if (move.first == 1) {
    //     row = 'B';
    // } else if (move.first == 2) {
    //     row = 'C';
    // }
    // movePiece(player, row, move.second+1);
}

int main() { // int argc,  char **argv
    // Default Value
    bool pruning = false;
    ttt* test = new ttt;
    cout << "Welcome to Tic-Tac-Toe" << endl;

    // Initialize board
    //test.resetBoard();
    test->showBoard();

    string input;
    do {
        // cin >> input;
        cout << "> ";
        input = "";
        getline(cin, input);
        // board[0][0] = 'X'; // test
        if (input.find("show") != string::npos) {
            test->showBoard();
        } else if (input.find("reset") != string::npos) {
            test->resetBoard();
            cout << "Board has been reset!" << endl;
            test->showBoard();

            bool pruning = test->pruning;
            delete test;
            test = new ttt;
            test->pruning = pruning;

        } else if (input.find("move") != string::npos) {
            string type;
            char piece;
            char row;
            int column;
            std::istringstream iss(input);
            if (iss >> type >> piece >> row >> column) {
                cout << type << " " << piece << " " << row << " " << column << endl;
                test->movePiece(piece, row, column);
            }  
            if(gameOver(test, piece)) {

                bool pruning = test->pruning;
                delete test;
                test = new ttt;
                test->pruning = pruning;

            }
            //test.showBoard();
        } else if (input.find("choose") != string::npos) {
            iteration = -1;
            string type;
            char piece;
            std::istringstream iss(input);
            if (iss >> type >> piece) {
                cout << type << " " << piece << endl;
                pair<int, int> move = miniMaxAlphaBeta(test, -1, piece);
                test->movePieceAI(piece, move.first, move.second);
                cout << "number of searched nodes: " << iteration << endl;
                test->showBoard();
                //test->choosePiece(test, piece);

            } 
            if(gameOver(test, piece)) {

                bool pruning = test->pruning;
                delete test;
                test = new ttt;
                test->pruning = pruning;

            }
            // if (winCondition()) {

            // }
        } else if (input.find("pruning on") != string::npos) {
            string type;
            char piece;
            std::istringstream iss(input);
            if (iss >> type >> piece) {
                //cout << type << " " << piece << endl;
            }
            test->pruning = true;
            cout << "pruning=" << int(test->pruning) << endl;

        } else if (input.find("pruning off") != string::npos) {
            string type;
            char piece;
            std::istringstream iss(input);
            if (iss >> type >> piece) {
                //cout << type << " " << piece << endl;
            }
            test->pruning = false;
            cout << "pruning=" << int(test->pruning) << endl;
        } else if (input.find("pruning") != string::npos) {
            //string type;
            // std::istringstream iss(input);
            // if (iss >> type >> piece) {
            //     cout << type << " " << piece << endl;
            // }
            cout << "pruning " << ((test->pruning) ? "on" : "off") << endl;
        }
        
    } while (input != "quit");

    cout << "Good Bye!" << endl;

    return 0;
}

