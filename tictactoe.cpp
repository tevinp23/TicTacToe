#include <iostream>
#include <limits>
using namespace std;

//function to print the board
void PrintMatrix(const char tttb[3][3]) {
    for (int i = 0; i < 3; i++) {
        cout << tttb[i][0] << "|" << tttb[i][1] << "|" << tttb[i][2] << endl;
        if (i != 2) // Only print separator between rows
            cout << "-----" << endl;
    }
}

//function to see if there's a winner
bool FoundWinner(const char tttb[3][3], char player) {
    // Check horizontal and vertical
    for (int i = 0; i < 3; i++) {
        if ((tttb[i][0] == player && tttb[i][1] == player && tttb[i][2] == player) || // Horizontal
            (tttb[0][i] == player && tttb[1][i] == player && tttb[2][i] == player)) { // Vertical
            return true; // Return winner if found
        }
    }
    // Check both diagonals, return true if a winner is found
    return (tttb[0][0] == player && tttb[1][1] == player && tttb[2][2] == player) || // Main diagonal
           (tttb[0][2] == player && tttb[1][1] == player && tttb[2][0] == player);   // Anti-diagonal
}

//function to see if there's a tie
bool FoundTie(const char tttb[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tttb[i][j] == ' ')
                return false; // Board is not full
        }
    }
    return true; // Board is full, return tie
}

//function to get valid input for row and column
bool GetValidInput(int& x, int& y) {
    cout << "Row (0-2): "; // prompt for row
    if (!(cin >> x)) { // check for valid integer input
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        cout << "Invalid input. Please enter an integer between 0 and 2." << endl;
        return false; // return false for invalid input
    }

    cout << "Column (0-2): "; // prompt for column
    if (!(cin >> y)) { // check for valid integer input
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        cout << "Invalid input. Please enter an integer between 0 and 2." << endl;
        return false; // return false for invalid input
    }

    // check if input is in valid range
    if (x < 0 || x >= 3 || y < 0 || y >= 3) {
        cout << "Invalid input. Please enter numbers between 0 and 2." << endl;
        return false; // return false for out-of-bound input
    }
    
    return true; // return true if input is valid
}

//function to capture location and place X or O on the board
void Capture_xy_Location(char tttb[3][3], char currentPlayer) {
    int x, y; // declare variables for row and column
    bool validInput = false; // assume input doesn't work

    do {
        cout << "Where do you want to place an " << currentPlayer << "?" << endl; // ask for input

        if (GetValidInput(x, y)) { // get input and validate
            if (tttb[x][y] == ' ') { // check if location is empty
                tttb[x][y] = currentPlayer; // place X or O on the board
                validInput = true; // set input as valid
            } else {
                cout << "Location already taken." << endl; // location is occupied
            }
        }
    } while (!validInput); // loop until valid input is received
}

int main() {
    char tttb[3][3] = { // declare the array
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char currentPlayer = 'X'; // initialize with X
    bool result = false; // game result

    // Print instructions for the user
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    cout << "Players take turns placing X and O on the 3x3 grid." << endl;
    cout << "The first player to get 3 in a row (horizontal, vertical, or diagonal) wins." << endl;
    cout << "Enter the row and column numbers to place your mark (0, 1, or 2)." << endl;

    PrintMatrix(tttb); // function to print the matrix

    while (!result) { 
        Capture_xy_Location(tttb, currentPlayer); // get input and update board
        PrintMatrix(tttb); // function to print the matrix

        if (FoundWinner(tttb, currentPlayer)) { // check if there's a winner
            cout << currentPlayer << " wins!" << endl;
            result = true; // set result as true to end the game
        } else if (FoundTie(tttb)) { // check if there's a tie
            cout << "It's a tie!" << endl;
            result = true; // set result as true to end the game
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // switch between X and O
        }
    }

    return 0; // end program
}
