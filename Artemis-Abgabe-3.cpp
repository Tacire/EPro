//
// Created by hendrik on 04.12.24.
//
#include "std_lib_inc.h"
#include <string>

class Player {
    public:
        Player(vector<unsigned int> startPosition){
            position = startPosition;
            keyCount = 0;
        }
        Player(vector<unsigned int> startPosition, unsigned int numberOfKeys){
            position = startPosition;
            keyCount = numberOfKeys;
        }
        int getX(){
            return position[0];
        }
        int getY(){
            return position[1];
        }
        int setPosition(vector<unsigned int> newPosition){
            position = newPosition;
            return 0;
        }
        int getKeyCount(){
            return keyCount;
        }
        int addKey(){
            keyCount++;
            return 0;
        }
        bool useKey(){
            if(keyCount>0){
                keyCount--;
                return true;
            }
            return false;
        }
    private:
        vector<unsigned int> position;
        unsigned int keyCount;
};

class Field{
    public:
        Field(unsigned int rows, unsigned int columns, vector<vector<char>> newMaze){
            if(!checkValidField(rows,columns,newMaze)){
                throw std::invalid_argument("Invalid char in Maze");
            }
            maxRow = rows;
            maxColumn = columns;
            kMaze = newMaze;
        }
        char getField(unsigned int row, unsigned int column){
            if(row >= maxRow || column >= maxColumn){
                throw std::invalid_argument("Tried to read out of bounds Field");
            }
            return kMaze[row][column];
        }
        int changeField(unsigned int row, unsigned int column, char newField){
            if(!checkInputValid(newField)){
                throw std::invalid_argument("Tried to write invalid char to Field");
            }else if(row >= maxRow || column >= maxColumn){
                throw std::invalid_argument("Tried to write out of bounds Field");
            }
            
            kMaze[row][column] = newField;
            return 0;
        }
    private:
        unsigned int maxRow;
        unsigned int maxColumn;
        vector<vector<char>> kMaze;

        bool checkValidChar(char charToCheck){
            constexpr char[] validChars = {'.', '#', 'Z', 'K', 'T', 'A'};
            bool validChar = false;
            
            for(char validChar : validChars){
                if(mazeToCheck[i][j] == validChar){
                    validChar = true;
                }
            }
            
            return validChar;
        }
        bool checkValidField(unsigned int rows, unsigned int columns, vector<vector<char>> mazeToCheck){

            if(mazeToCheck.size() != rows){
                return false;
            }

            for(int i = 0; i < rows; i++){
                if(mazeToCheck[i].size() != columns){
                    return false
                }
                for(int j = 0; j < columns, j++){
                    if(!checkValidChar(mazeToCheck[i][j])){
                        return false;
                    }
            }
            return true;
            
        }
};

//Exception bei falscher Bewegung & falsche Eingabe
//Nicht bei Geist
class GameState {
    public:
        GameState(Field newField, Player newPlayer){
            field = newField;
            player = newPlayer;
            hitbyghost = false; 
        }
        bool alive(){
            return hitbyghost;
        }
        int touchGhost(){
            hitbyghost = true;
        }
        const Field field;
        const Player player;
    private:
        bool hitbyghost;
};

/* Diese Funktion überprüft, ob die Eingabe des Nutzers zulässig ist
 * Wenn ja, gibt sie true zurück, sonst false */
bool checkInputValid(char input) {
    bool validInput = false;
    if (input == 'w' || input == 'a' || input == 's' || input == 'd' || input == 'h') {
        validInput = true;
    }
    return validInput;
}

/**
 * Splittet einen String anhand Leerzeichen
 */
vector<string> splitString(string toSplit){
    vector<string> splittedString;

    const char delimiter = " ";
    char *word = strtok(toSplit, delimiter);
    while(word != nullptr){
        splittedStr.push_back(word);
        data = strtok(nullptr, delimiter);
    }

    return splittedString;
}

GameState initializeGame(string initString){
    vector<string> initData = splitString(initString);
    if(initData.size() < 4){
        throw std::invalid_argument("At least 4 arguments necessary");
    }

    rows = stoi(initData[0]);
    columns = stoi(initData[1]);
    
    if(initData.size() != (4 + rows)){
        throw std::invalid_argument("Wrong number of arguments given");
    }

    vector<vector<char>> maze;
    for(int i = 0; i < rows; i++){
        vector<char> row;
        if(initData[2+i].length() != columns){
            throw std::invalid_argument("Columns argument not matching maze");
        }
        for(int j = 0; j < columns; j++){
            row.push_back(initData[2+i][j]);
        }
        maze.push_back(row);
        row.clear();
    }

    playerRow = atoi(initData[2+rows]);
    playerColumn = atoi(initData[3+rows])
    
    if(playerRow >= rows || playerColumn >= columns){
        throw std::invalid_argument("Player out of bounds of maze");
    }

    return GameState(Field(rows,columns,maze),Player(playerRow,playerColumn));
}

/* In der main-Funktio wird zunächst die Ausgangssituation vom Labyrinth ausgegeben,
 * dann Inputs genommen und je nach Input die gewünschten Funktionen
 * des Bewegens vom Charakter, die Ausgabe der Hilfe oder bei nicht zulässiger Eingabe
 * ein entsprechender Hinweis ausgegeben
 * Das Programm wird beendet wenn der Spielercharakter 'S' das Ziel 'Z' erreicht hat */
int main()
{

    cout << "Bitte Spieleingaben tätigen\n";
    cout << "Schema: <Zeilen> <Spalte> <Labyrinth-Zeichen> <Spieler Zeile> <Spieler Spalte>\n"

    string initInput
    cin >> initInput;
    if(cin){
        GameState game = initializeGame(initInput);
    }
}