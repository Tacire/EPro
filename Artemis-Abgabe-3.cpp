//
// Created by schlafentzug on 22.12.24.
//
#include "std_lib_inc.h"
#include <string.h>

class badInit{};
class badInput{};
class badMovement{};

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
        bool hasKey(){
            if(keyCount>0){
                return true;
            }
            return false;
        }
        void addKey(){
            keyCount++;
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
                throw badInit{};
            }
            maxRow = rows;
            maxColumn = columns;
            kMaze = newMaze;
        }
        char getFieldValue(unsigned int row, unsigned int column){
            if(row >= maxRow || column >= maxColumn){
                throw badMovement{};
            }
            return kMaze[row][column];
        }
        int changeField(unsigned int row, unsigned int column, char newField){
            if(!checkValidChar(newField)){
                throw badInit{};
            }else if(row >= maxRow || column >= maxColumn){
                throw badInit{};
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
            reachedGoal = false;
        }
        bool gameWon(){
            return reachedGoal;
        }
        bool gameOver(){
            return hitbyghost;
        }
        void reachGoal(){
            reachedGoal = true;
        }
        void touchGhost(){
            hitbyghost = true;
        }
        Field * field;
        Player * player;
    private:
        bool hitbyghost;
        bool reachedGoal;
};
// Gibt eine kurze Hilfe aus
void display_help() {
    cout << "Willkommen zum Labyrinth-Spiel!\n";
    cout << "Ziel des Spiels: Finde den Weg vom Startpunkt (S) zum Ziel (Z).\n";
    cout << "Spielfeld-Erklaerung:\n";
    cout << "S - Startpunkt: Hier beginnt der Spieler.\n";
    cout << "Z - Ziel: Erreiche diesen Punkt, um das Spiel zu gewinnen.\n";
    cout << "# - Wand: Diese Felder sind nicht begehbar.\n";
    cout << ". - Leeres Feld: Diese Felder koennen betreten werden.\n";
    cout << "\nSteuerung:\n";
    cout << "w - Nach oben bewegen\n";
    cout << "a - Nach links bewegen\n";
    cout << "s - Nach unten bewegen\n";
    cout << "d - Nach rechts bewegen\n";
    cout << "Nach jeder Befehlseingabe muss die Eingabetaste (Enter) gedrueckt werden, um sich zu bewegen.\n";
    cout << "\nViel Erfolg im Labyrinth!\n";
}

void quit_game(){
    cout << "Schoenen Tag noch!\n";
    exit(0);
}
//Überprüft auf Collision mit Wand, Tuer & Grenze vor Bewegung
void checkCollision(GameState game, char input) {
    bool movementPossible = false;
    switch (input) {
        case 'w':
            if ((game.player->getRow() - 1) < 0 || game.field->getFieldValue(game.player->getRow() - 1,game.player->getColumn()) == '#') {
                movementPossible = false;
            }
            else if(game.field->getFieldValue(game.player->getRow() - 1,game.player->getColumn()) == 'T' && !(game.player->hasKey())){
                movementPossible = false;
            }
            else {
                movementPossible = true;
            }
        break;
        case 's':
            if ((game.player->getRow() + 1) > (game.field->maxRow -1) || game.field->getFieldValue(game.player->getRow() + 1,game.player->getColumn()) == '#') {
                movementPossible = false;
            }
            else if(game.field->getFieldValue(game.player->getRow() + 1,game.player->getColumn()) == 'T' && !(game.player->hasKey())){
                movementPossible = false;
            }
            else {
                movementPossible = true;
            }
        break;
        case 'a':
            if ((game.player->getColumn() - 1) < 0 || game.field->getFieldValue(game.player->getRow(),game.player->getColumn() - 1) == '#') {
                movementPossible = false;
            }
            else if(game.field->getFieldValue(game.player->getRow(),game.player->getColumn() - 1) == 'T' && !(game.player->hasKey())){
                movementPossible = false;
            }
            else {
                movementPossible = true;
            }
        break;
        case 'd':
            if ((game.player->getColumn() + 1) > (game.field->maxColumn-1) || game.field->getFieldValue(game.player->getRow(),game.player->getColumn() + 1) == '#') {
                movementPossible = false;
            }
            else if(game.field->getFieldValue(game.player->getRow(),game.player->getColumn() + 1) == 'T' && !(game.player->hasKey())){
                movementPossible = false;
            }
            else {
                movementPossible = true;
            }
        break;
    }
    if(!movementPossible){
        throw badMovement{};
    }
}

void interactWithField(GameState game){
    unsigned int row = game.player->getRow();
    unsigned int column = game.player->getColumn();
    if(game.field->getFieldValue(row,column) == 'T'){
        game.player->useKey();
        game.field->changeField(row,column,'.');
    }else if(game.field->getFieldValue(row,column) == 'K'){
        game.player->addKey();
        game.field->changeField(row,column,'.');
    }else if(game.field->getFieldValue(row,column) == 'A'){
        game.touchGhost();
    }
}

// Behandelt Bewegungsaktionen
void move(GameState game, char input){
    checkCollision(game,input);
    switch(input){
        case 'w':
            game.player->setRow(game.player->getRow() - 1);
            break;
        case 'a':
            game.player->setColumn(game.player->getColumn() - 1);
            break;
        case 's':
            game.player->setRow(game.player->getRow() + 1);
            break;
        case 'd':
            game.player->setColumn(game.player->getColumn() + 1);
            break;
    }    
    
}
/**
 * Oberfunktion die den Input und folgende Aktionen handled
 */
void handleInput(GameState game, char input){
    if (!(input == 'w' || input == 'a' || input == 's' || input == 'd' || input == 'h' || input == 'q')) {
        throw badInput{};
    }

    if(input == 'h'){
        display_help();
    }else if(input == 'q'){
        quit_game();
    }else{
        move(game, input);
    }
}

/** Initializing  Game &
 *  Checking for Inputerrors
 */
GameState initializeGame(string initString){
    vector<char*> initData; 

    //splitting init data by whitespace
    char * word = strtok(initString.data(), " ");
    while(word != nullptr){
        initData.push_back(word);
        word = strtok(nullptr, " ");
    }

    if(initData.size() < 4){
        throw badInit{};
    }

    unsigned int rows = strtol(initData[0],nullptr,10);
    unsigned int columns = strtol(initData[1],nullptr,10);
    
    if(initData.size() != (4 + rows)){
        throw badInit{};
    }
    if(rows > 20 || columns > 20){
        throw badInit{};
    }

    //creating maze out of parsed data
    vector<vector<char>> maze;
    for(unsigned int i = 0; i < rows; i++){
        vector<char> row;
        for(unsigned int j = 0; j < columns; j++){
            row.push_back(initData[2+i][j]);
        }
        maze.push_back(row);
        row.clear();
    }

    //Parsing Player Data
    unsigned int playerRow = strtol(initData[2+rows],nullptr,10);
    unsigned int playerColumn = strtol(initData[3+rows],nullptr,10);
    //Checking correct startpossision
    if((playerRow >= rows || playerColumn >= columns) || maze[playerRow][playerColumn] != '.'){
        throw badInit{};
    }

    //Initializing class instances & game
    GameState newGame(new Field(rows,columns,maze),new Player(playerRow,playerColumn));
    
    //Let's go
    return newGame;
}

int printGame(GameState game){
    for (unsigned int i = 0; i < game.field->maxRow; i++) {
        for (unsigned int j = 0; j < game.field->maxColumn; j++) {
            if (i == game.player->getRow() && j == game.player->getColumn()) {
                cout << "S" << "  ";
            }else {
                cout << game.field->getFieldValue(i,j) << "  ";
            }
        }
        cout << "\n";
    }
    return 0;
}
/* In der main-Funktio wird zunächst die Ausgangssituation vom Labyrinth ausgegeben,
 * dann Inputs genommen und je nach Input die gewünschten Funktionen
 * des Bewegens vom Charakter, die Ausgabe der Hilfe oder bei nicht zulässiger Eingabe
 * ein entsprechender Hinweis ausgegeben
 * Das Programm wird beendet wenn der Spielercharakter 'S' das Ziel 'Z' erreicht hat */
int main()
{
    try{
        cout << "Bitte Spieleingaben tätigen\n";
        cout << "Schema: <Zeilen> <Spalte> <Labyrinth-Zeichen> <Spieler Zeile> <Spieler Spalte>\n";

        string initInput;
        getline(cin, initInput, '\n');

        GameState game = initializeGame(initInput);
        printGame(game);

        char input;
        cin >> input;
        while(cin){
            try{
                handleInput(game, input);
                printGame(game);
                if(game.gameOver()){
                    cout << "Du hast verloren :(\n";
                    exit(0);
                }else if(game.gameWon()){
                    cout << "Du hast gewonnen!\n";
                    exit(0);
                }
            }catch(badInput&){
                cout << "Die Eingabe kenne ich nicht. Gib 'h' ein, um eine Hilfe zu erhalten.\n";
            }catch(badMovement&){
                cout << "Bewegung nicht moeglich!\n";
            }
            cin >> input;
        }
    } catch(badInit&){
        cout << "Fehler beim Einlesen des Labyrinths.\n";
        exit(0);
    }
}