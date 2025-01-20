/**
 * Maze-Klasse,
 * beinhaltet ein gültiges Maze, eine Pfadfindemethode sowie diverse Feldüberprüfungen
 */

#include "maze.h"

//Konstruktor für Maze, wird wenn es gültig ist
//in den passenden Dimensionen maxRows, maxColumns mit den übergebenen Daten angelegt
Maze::Maze(const int& maxRows, const int& maxColumns, const vector<vector<char>>& newMaze)
: rows_(maxRows) , cols_(maxColumns){

    //Checkt ob das Init-Maze gültig ist
    if(!valid_maze(maxRows,maxColumns,newMaze)){
        throw BadMaze{}; // Wenn Maze falsche größe / Inhalt
    }else{
        data_ = newMaze;
    }
}

// Gibt die benoetigte Schritte bis zum Ziel an
// nach vorgegebenen Agorithmus
int Maze::calculate_shortest_path_to_goal(const vector<int>& position, const int& steps){
    if(position[0] >= rows_ || position[0] < 0 || position[1] >= cols_ || position[1] < 0){
        return -1; // Out of Bounds
    }

    char field = data_[position[0]][position[1]];
    if(field == 'Z'){ // Ziel erreicht
        return 0;
    }else if(steps == 0){ // Schrittlimit erreicht
        return -1;
    }else if(field == '.' || field == 'K' || field == 'A'){ // Wenn das Feld valid ist wird rekursiv weitergesucht
        vector <int> possible_ways;
        possible_ways.push_back(calculate_shortest_path_to_goal({position[0]+1,position[1]}, steps -1));
        possible_ways.push_back(calculate_shortest_path_to_goal({position[0]-1,position[1]}, steps -1));
        possible_ways.push_back(calculate_shortest_path_to_goal({position[0],position[1]+1}, steps -1));
        possible_ways.push_back(calculate_shortest_path_to_goal({position[0],position[1]-1}, steps -1));

        int min = -1; // Standardmäßig unmöglich
        for(int i : possible_ways){
            if(i == -1){ // Ignoriert unmögliche Wege
                continue;
            }
            //Falls es ein mögliches Feld gibt, überschreibe unmöglich & finde minimum
            if((min == -1) || (i < min)){
                min = i;
            }
        }
        if(min == -1){ //Wenn 
            return -1;
        }else{
            return 1 + min;
        }
    }else{ // Feld ist kein gültiges Pfadfindefeld
        return -1;
    }
}

//Überprüft, ob an der Stelle {row, column} im Maze eine Wand Tür oder Grenze ist
bool Maze::check_wall(const int& row, const int& column){
    if(inbounds(row,column)){
        switch(data_[row][column]){
            case '#':
                return true;
                break;
            case 'T':
                return true;
                break;
            default:
                return false;
        }
    }else{
        return true;
    }
}

//Überprüft ob Feld innerhalb des Labyrinths liet
bool Maze::inbounds(const int& row, const int& column){
    if(row >= rows_ || row < 0 || column >= cols_ || column < 0){
        return false;
    }else{
        return true;
    }
}

// Überprüft ob der Feldinhalt einem gültigen Feldwert entspricht
bool Maze::valid_field(const char& field){
    bool valid = false;
    for(char validfield : valid_fields){
        if(field == validfield){
            valid = true;
        }
    }
    return valid;
}

//Überprüft, ob ein eingegebenes Maze vailde Werte hat
//Gibt false zurück, wemm die Inhaltsdaten nicht die erwartete Länge haben
//und auch false, wenn ein Feld im Maze eingegeben wurde, was nicht vailde ist
bool Maze::valid_maze(const int& maxRows, const int& maxColumns, const vector<vector<char>>& newMaze){
    if(newMaze.size() != maxRows){
        return false; // Wenn Vector falsche größe hat
    }
    for(vector<char> row : newMaze){
        if(row.size() != maxColumns){
            return false; // Wenn Vector falsche größe
        }
        for(char field : row){
            if(!valid_field(field)){
                return false;   //Wenn Feldinhalt nicht gültig ist
            }
        }
    }
    return true;
}

//Verändert das Feld an Stelle {row, column} im Maze zum übergebenen newField, wenn dies valide ist
void Maze::change_field(const int& row, const int& column, const char& newField){
        if(!valid_field(newField)){
            throw BadMaze{};
        }else if(!inbounds(row,column)){
            throw BadMaze{};
        }
        
        data_[row][column] = newField;
    }


//Gibt Datenvektor von Maze zurück
vector<vector<char>> Maze::data(){
    return data_;
}

//Gibt Zeilen vom Maze zurück
int Maze::get_rows(){
    return rows_;
}

//Gibt Spalten vom Maze zurück
int Maze::get_cols(){
    return cols_;
}