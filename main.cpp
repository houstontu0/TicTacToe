#include <iostream>
#include <ctype.h>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
using namespace std;


void PlayerTurn(int b[3][3], int marker) { // when it's the player's turn
    string playerinput;
    int col;
    int row;

    while (true) { // gets input from the player and checks for errors
        cout << "Which square would you like?" << endl;
        cout << "Enter the column first then the row. Ex: B2. ('q' to quit)" << endl;
        cin >> playerinput;
        if (playerinput == "q") { // if they enter a q then exit the program
            cout << "Okay bye." << endl;
            exit(0);
        }
        if (playerinput.length() != 2) { // if it is not 2 characters then have them try again
            cout << "Invalid input. Please enter 2 characters like the example." << endl;
            continue;
        }

        char colInput = toupper(playerinput.at(0)); // makes input an uppercase
        switch (colInput) {
            case 'A':
                col = 0;
                break;
            case 'B':
                col = 1;
                break;
            case 'C':
                col = 2;
                break;
            default:
                col = -1;
                break;
        }

        char rowInput = toupper(playerinput.at(1));
        switch (rowInput) {
            case '1':
                row = 0;
                break;
            case '2':
                row = 1;
                break;
            case '3':
                row = 2;
                break;
            default:
                row = -1;
                break;
        }
        if (row == -1 || col == -1) {
            cout << "Invalid input. Please try again." << endl;
            continue;
        }
        if (b[row][col] != 2) { // if the spot is not equal to a ___ then try again
            cout << "This spot has been taken. Please select an open spot." << endl;
            continue;
        }
        break;
    }
    b[row][col] = marker; // set their input to the place on the board
}

void ComputerTurn(int b[3][3], int marker) { // random input from the computer
    srand(time(0));
    while (true) {
        int randomcol = rand() % 3;
        int randomrow = rand() % 3;
        if (b[randomrow][randomcol] == 2) {
            b[randomrow][randomcol] = marker;
            break;
        }
    }
}

char convertToChar(int a) { // convert their input to a char
    switch(a) {
        case 0:
            return 'O';
        case 1:
            return 'X';
        case 2:
            return '_';
        default:
            throw "Invalid Input";
    }
}

void PrintBoard(int b[3][3]) { // print the board
    cout << "  _A_|_B_|_C_|" << endl;
    cout << "1|_" << convertToChar(b[0][0]) << "_|_" << convertToChar(b[0][1]) << "_|_" << convertToChar(b[0][2]) << "_|" << endl;
    cout << "2|_" << convertToChar(b[1][0]) << "_|_" << convertToChar(b[1][1]) << "_|_" << convertToChar(b[1][2]) << "_|" << endl;
    cout << "3|_" << convertToChar(b[2][0]) << "_|_" << convertToChar(b[2][1]) << "_|_" << convertToChar(b[2][2]) << "_|" << endl << endl;
}

bool CheckWinner(int b[3][3], int marker) { // checking for a winner
    if ((b[0][0] == marker && b[0][0] == b[1][1] && b[0][0] == b[2][2]) || (b[0][2] == marker && b[0][2] == b[1][1] && b[0][2] == b[2][0])) {
        return true; // checks for winners diagonally and if yes then return true
    }
    for (int i = 0; i < 3; i++) {
        if (b[i][0] == marker && b[i][0] == b[i][1] && b[i][0] == b[i][2]) {
            return true; // checks for a winner vertically and if yes then return true
        }
    }
    for (int j = 0; j < 3; j++) {
        if (b[0][j] == marker && b[0][j] == b[1][j] && b[0][j] == b[2][j]) {
            return true; // checks for a winner horizontally and if yes then return true
        }
    }
    return false; // if none of them then return false
}

int CheckRemainingSpots(int b[3][3]) { // counting the amount of remaining spots open
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == 2) {
                count += 1;
            }
        }
    }
    return count;
}

int main() {
    while (true) {
        char playGame;
        bool winnerFound = false;
        int board[3][3] = {
                {2, 2, 2},
                {2, 2, 2},
                {2, 2, 2}
        };
        int computerMarker = 0; // computer is o
        int playerMarker = 1; // player is x
        int turn;

        srand(time(0));
        cout << "Start a new game? (Y/N)" << endl;
        cin >> playGame;
        if (playGame == 'Q' || playGame == 'q') { // if the player wants to quite
            cout << "Okay bye." << endl;
            exit(0);
        } else if (playGame == 'Y' || playGame == 'y') { // if the player wants to play
            if (rand() % 2 == 1) {
                cout << "After a random coin flip, you will go first." << endl;
                turn = playerMarker;
            } else {
                cout << "After a random coin flip, the computer will go first." << endl;
                turn = computerMarker;
            }

            PrintBoard(board);
            while (true) { // while there are no winners left, alternate between the winner and the player
                if (turn == computerMarker) {
                    cout << "It's the computer's turn" << endl << endl;
                    ComputerTurn(board, computerMarker);
                    winnerFound = CheckWinner(board, computerMarker);
                    PrintBoard(board);
                    if (winnerFound) {
                        cout << "The computer won!" << endl;
                        break;
                    } else if (CheckRemainingSpots(board) == 0) {
                        cout << "There's been a tie!" << endl;
                        break;
                    } else {
                        turn = playerMarker;
                    }
                }
                if (turn == playerMarker) {
                    cout << "It's the player's turn" << endl << endl;
                    PlayerTurn(board, playerMarker);
                    PrintBoard(board);
                    winnerFound = CheckWinner(board, playerMarker);
                    if (winnerFound) {
                        cout << "You won!" << endl;
                        break;
                    } else if (CheckRemainingSpots(board) == 0) {
                        cout << "There's been a tie!" << endl;
                        break;
                    } else {
                        turn = computerMarker;
                    }
                }
            }
        } else if (playGame == 'N' || playGame == 'n') { // if the player doesn't want to play
            cout << "Okay bye." << endl;
            return 0;
        } else { // if the player doesn't input a y, n, or q
            cout << "Please enter a 'Y' or 'N'." << endl;
            continue;
        }
    }
}