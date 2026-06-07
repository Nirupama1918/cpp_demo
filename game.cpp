#include <iostream>
using namespace std;

char board[3][3];

void initializeBoard() {
    char ch = '1';
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = ch++;
        }
    }
}

void displayBoard() {
    cout << "\n";
    for(int i = 0; i < 3; i++) {
        cout << " ";
        for(int j = 0; j < 3; j++) {
            cout << board[i][j];
            if(j < 2) cout << " | ";
        }
        cout << "\n";
        if(i < 2)
            cout << "---|---|---\n";
    }
    cout << "\n";
}

bool checkWin() {
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == board[i][1] &&
           board[i][1] == board[i][2])
            return true;

        if(board[0][i] == board[1][i] &&
           board[1][i] == board[2][i])
            return true;
    }

    if(board[0][0] == board[1][1] &&
       board[1][1] == board[2][2])
        return true;

    if(board[0][2] == board[1][1] &&
       board[1][1] == board[2][0])
        return true;

    return false;
}

bool makeMove(int position, char player) {
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    if(position < 1 || position > 9)
        return false;

    if(board[row][col] == 'X' || board[row][col] == 'O')
        return false;

    board[row][col] = player;
    return true;
}

int main() {
    char replay;

    do {
        initializeBoard();

        int move, turns = 0;
        char player = 'X';

        while(true) {
            displayBoard();

            cout << "Player " << player
                 << ", enter position (1-9): ";
            cin >> move;

            if(!makeMove(move, player)) {
                cout << "Invalid Move! Try Again.\n";
                continue;
            }

            turns++;

            if(checkWin()) {
                displayBoard();
                cout << "Player " << player
                     << " Wins!\n";
                break;
            }

            if(turns == 9) {
                displayBoard();
                cout << "Game Draw!\n";
                break;
            }

            player = (player == 'X') ? 'O' : 'X';
        }

        cout << "\nPlay Again? (Y/N): ";
        cin >> replay;

    } while(replay == 'Y' || replay == 'y');

    cout << "Thank You for Playing!\n";

    return 0;
}