//
// Created by hendrik on 04.12.24.
//
#include "std_lib_inc.h"

// Labyrinth-Dimensionen als konstanter Ausdruck
constexpr int kRows = 5;
constexpr int kCols = 5;

// Labyrinth-Definition
// Interpretiere als Zeilen, dann Spalten
const vector<vector<char>> kMaze = {
    {'#', '.', '.', '.', '.'},
    {'#', '.', '#', '.', '.'},
    {'.', 'Z', '#', '.', '.'},
    {'.', '#', '#', '#', '.'},
    {'.', '.', '.', '.', '.'},
};

// Startposition des Spielers
const vector<int> kPlayerStartPosition = {4, 0};

/*  Diese Funktion printed das Labyrinth richtig formatiert auf die Konsole
 *  inklusive der momentanen Position des Spielers */
int printLabyrinth(vector<int> playerPosition) {
    for (int i = 0; i < kRows; ++i) {
        for (int j = 0; j < kCols; ++j) {
            if (i == playerPosition[0] && j == playerPosition[1]) {
                cout << 'S' << "  ";
            }
            else {
                cout << kMaze[i][j] << "  ";
            }
        }
        cout << "\n";
    }
    return 0;
}

/* Diese Funktion überprüft, ob der nächste Schritt des
 * Spielers zu einer kollision mit einem # führen oder ihn aus
 * dem Bereich des Labyrinths bringen würde
 * Wenn die gewünschte Bewegung möglich ist, gibt sie true
 * zurück, sonst false */
bool checkCollision(vector<int> currentPlayerPosition, char input) {
    bool movementPossible = false;
    switch (input) {
        case 'w':
            if ((currentPlayerPosition[0] - 1) < 0 || kMaze[(currentPlayerPosition[0] - 1)][currentPlayerPosition[1]] == '#') {
                movementPossible = false;
            }
            else {
                movementPossible = true;
            }
        break;
        case 's':
            if ((currentPlayerPosition[0] + 1) > (kRows-1) || kMaze[(currentPlayerPosition[0] + 1)][currentPlayerPosition[1]] == '#') {
                movementPossible = false;
            }
            else {
                movementPossible = true;
            }
        break;
        case 'a':
            if ((currentPlayerPosition[1] - 1) < 0 || kMaze[currentPlayerPosition[0]][(currentPlayerPosition[1] - 1)] == '#') {
                movementPossible = false;
            }
            else {
                movementPossible = true;
            }
        break;
        case 'd':
            if ((currentPlayerPosition[1] + 1) > (kCols-1) || kMaze[currentPlayerPosition[0]][(currentPlayerPosition[1] + 1)] == '#') {
                movementPossible = false;
            }
            else {
                movementPossible = true;
            }
        break;
    }
    return movementPossible;
}

/* Diese Funktion bewegt den Charakter, indem sie die momentane Position
 * als 2D vector nimmt und diese dann entsprechend von input anpasst */
vector<int> moveCharacter(vector<int> currentPlayerPosition, char input) {
    vector<int> workingPlayerPosition = currentPlayerPosition;
    switch (input) {
        case 'w':
            workingPlayerPosition[0] -= 1;
        break;
        case 's':
            workingPlayerPosition[0] += 1;
        break;
        case 'a':
            workingPlayerPosition[1] -= 1;
        break;
        case 'd':
            workingPlayerPosition[1] += 1;
        break;
    }
    return workingPlayerPosition;
}

/* Diese Funktion überprüft, ob die Eingabe des Nutzers zulässig ist
 * Wenn ja, gibt sie true zurück, sonst false */
bool checkInputValid(char input) {
    bool validInput = false;
    if (input == 'w' || input == 'a' || input == 's' || input == 'd' || input == 'h') {
        validInput = true;
    }
    return validInput;
}

/* Diese Funktion überprüft, ob der Spieler das Ziel, welches
 * im Labyrinth mit 'Z' dargestellt ist, erreicht hat
 * Wenn ja gibt sie true zurück, sonst false */
bool checkGoalReached(vector<int> currentPlayerPosition) {
    bool goalReached = false;
    if (kMaze[currentPlayerPosition[0]][currentPlayerPosition[1]] == 'Z') {
        goalReached = true;
    }
    return goalReached;
}

/* In der main-Funktio wird zunächst die Ausgangssituation vom Labyrinth ausgegeben,
 * dann Inputs genommen und je nach Input die gewünschten Funktionen
 * des Bewegens vom Charakter, die Ausgabe der Hilfe oder bei nicht zulässiger Eingabe
 * ein entsprechender Hinweis ausgegeben
 * Das Programm wird beendet wenn der Spielercharakter 'S' das Ziel 'Z' erreicht hat */
int main()
{
    printLabyrinth(kPlayerStartPosition);
    vector<int> currentPlayerPosition = kPlayerStartPosition;
    char input;
    cin >> input;
    while (cin) {
        bool validInput = checkInputValid(input);
        if (!validInput) {
            cout << "Diese Eingabe kenne ich nicht. Gib 'h' ein, um eine Hilfe zu erhalten.\n";
            printLabyrinth(currentPlayerPosition);
        }
        if (input == 'h') {
            cout << "Wenn du bei diesem Spiel Hilfe brauchst frag wen anders :D\n";
        }

        bool movementPossible = checkCollision(currentPlayerPosition, input);
        if (movementPossible) {
            currentPlayerPosition = moveCharacter(currentPlayerPosition, input);
            printLabyrinth(currentPlayerPosition);
        }
        else if (!movementPossible && validInput && input != 'h') {
            cout << "Bewegung nicht moeglich!\n";
            printLabyrinth(currentPlayerPosition);
        }

        if (checkGoalReached(currentPlayerPosition)) {
            cout << "Ziel erreicht! Herzlichen Glueckwunsch!\n";
            break;
        }
        cin >> input;
    }
}