//
// Created by hendrik on 04.12.24.
//
#include "std_lib_inc.h"
#include <string.h>

class Player {
    public:
        Player(unsigned int startRow, unsigned int startColumn){
            position[0] = startRow;
            position[1] = startColumn;
            keyCount = 0;
        }
        Player(unsigned int startRow, unsigned int startColumn, unsigned int numberOfKeys){
            position[0] = startRow;
            position[1] = startColumn;
            keyCount = numberOfKeys;
        }
        unsigned int getRow(){
            return position[0];
        }
        unsigned int getColumn(){
            return position[1];
        }
        int setRow(unsigned int newRow){
            position[0] = newRow;
            return 0;
        }
        int setColumn(unsigned int newColumn){
            position[1] = newColumn;
            return 0;
        }
        unsigned int getKeyCount(){
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
        unsigned int position[2];
        unsigned int keyCount;
};

class Field{
    public:
        Field(unsigned int rows, unsigned int columns, vector<vector<char>> newMaze){
            if(!checkValidField(rows,columns,newMaze)){
                throw std::invalid_argument("Invalid maze");
            }
            maxRow = rows;
            maxColumn = columns;
            kMaze = newMaze;
            /**
            for(vector<char> row : newMaze){
                vector<char> newVector = row;
                kMaze.push_back(newVector);
            }
            cout << kMaze[1][1] << "\n";
            for(unsigned int i= 0; i < rows; i++){
                vector<char> row;
                for(unsigned int j = 0; j < columns; i++){
                    row.push_back(newMaze[i][j]);
                }
                kMaze.push_back(row);   
                row.clear();
            } */
        }
        char getFieldValue(unsigned int row, unsigned int column){
            cout << row << "|" << this->maxRow << endl;
            cout << column << "|" << this->maxColumn << endl;
            if(row >= maxRow || column >= maxColumn){
                throw std::invalid_argument("Tried to read out of bounds Field");
            }
            return kMaze[row][column];
        }
        int changeField(unsigned int row, unsigned int column, char newField){
            if(!checkValidChar(newField)){
                throw std::invalid_argument("Tried to write invalid char to Field");
            }else if(row >= maxRow || column >= maxColumn){
                throw std::invalid_argument("Tried to write out of bounds Field");
            }
            
            kMaze[row][column] = newField;
            return 0;
        }
        unsigned int maxRow;
        unsigned int maxColumn;
    private:
        vector<vector<char>> kMaze;

        bool checkValidChar(char charToCheck){
            constexpr char validChars[6] = {'.', '#', 'Z', 'K', 'T', 'A'};
            bool valid = false;
            
            for(char possibleChar : validChars){
                if(charToCheck == possibleChar){
                    valid = true;
                }
            }
            
            return valid;
        }
        bool checkValidField(unsigned int rows, unsigned int columns, vector<vector<char>> mazeToCheck){
            if(mazeToCheck.size() != rows){
                return false;
            }
            for(unsigned int i = 0; i < rows; i++){
                if(mazeToCheck[i].size() != columns){
                    return false;
                }
                for(unsigned int j = 0; j < columns; j++){
                    if(!checkValidChar(mazeToCheck[i][j])){;
                        cout << mazeToCheck[i][j] << "\n";
                        return false;
                    }
                }
            }
            return true;
            
        }
};

//Exception bei falscher Bewegung & falsche Eingabe
//Nicht bei Geist
class GameState {
    public:
        GameState(Field * newField, Player * newPlayer){    
            field = newField;
            player = newPlayer;
            hitbyghost = false; 
        }
        bool alive(){
            return hitbyghost;
        }
        int touchGhost(){
            hitbyghost = true;
            return 0;
        }
        Field * field;
        Player * player;
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
vector<char*> splitString(string toSplit){
    vector<char*> splittedStr;

    char * word = strtok(toSplit.data(), " ");
    while(word != nullptr){
        splittedStr.push_back(word);
        word = strtok(nullptr, " ");
    }

    return splittedStr;
}

GameState initializeGame(string initString){
    vector<char *> initData = splitString(initString);
    if(initData.size() < 4){
        throw std::invalid_argument("At least 4 arguments necessary");
    }

    unsigned int rows = atoi(initData[0]);
    unsigned int columns = atoi(initData[1]);
    
    if(initData.size() != (4 + rows)){
        throw std::invalid_argument("Wrong number of arguments given");
    }

    vector<vector<char>> maze;
    for(unsigned int i = 0; i < rows; i++){
        vector<char> row;
        for(unsigned int j = 0; j < columns; j++){
            row.push_back(initData[2+i][j]);
        }
        maze.push_back(row);
        row.clear();
    }

    unsigned int playerRow = atoi(initData[2+rows]);
    unsigned int playerColumn = atoi(initData[3+rows]);
    cout << size(maze) << "\n";

    if(playerRow >= rows || playerColumn >= columns){
        throw std::invalid_argument("Player out of bounds of maze");
    }
    GameState newGame(new Field(rows,columns,maze),new Player(playerRow,playerColumn));
    cout << size(newGame.field->kMaze) << "sdas\n";
    
    return newGame;
}

int printGame(GameState game){
    for (unsigned int i = 0; i < game.field->maxRow; i++) {
        cout << "2\n";
        for (unsigned int j = 0; j < game.field->maxColumn; j++) {
            cout << "3\n";
            if (i == game.player->getRow() && j == game.player->getColumn()) {
                cout << 'S' << "  ";
            }else {
                cout << "3.2\n";
                cout << game.field->getField(i,j) << "  ";
            }
        }
        cout << "4\n";
    }
    cout << "5\n";
    return 0;
}
/* In der main-Funktio wird zunächst die Ausgangssituation vom Labyrinth ausgegeben,
 * dann Inputs genommen und je nach Input die gewünschten Funktionen
 * des Bewegens vom Charakter, die Ausgabe der Hilfe oder bei nicht zulässiger Eingabe
 * ein entsprechender Hinweis ausgegeben
 * Das Programm wird beendet wenn der Spielercharakter 'S' das Ziel 'Z' erreicht hat */
int main()
{

    cout << "Bitte Spieleingaben tätigen\n";
    cout << "Schema: <Zeilen> <Spalte> <Labyrinth-Zeichen> <Spieler Zeile> <Spieler Spalte>\n";

    string initInput = "2 2 .. .. 0 1";
    //getline(cin, initInput, '\n');

    GameState game = initializeGame(initInput);

    cout << game.field->getField(1,1) << "\n";
    //printGame(game);
}