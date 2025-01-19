#include "maze.h"

Maze::Maze(const int& maxRows, const int& maxColumns, const vector<vector<char>>& newMaze){
    //Checkt ob das Init-Maze gültig ist
    if(!validMaze(maxRows,maxColumns,newMaze)){
        throw BadMaze{}; // Wenn Maze fasche größe
    }

    rows = maxRows;
    cols = maxColumns;
    data_ = newMaze;
}

// Gibt die benoetigte Schritte bis zum Ziel an
// nach vorgegebenen Agorithmus
int Maze::calculate_shortest_path_to_goal(const vector<int> position, const int steps){
    if(position[0] >= rows || position[0] < 0 || position[1] >= cols || position[1] < 0){
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

        int min = -1;
        for(int i : possible_ways){
            if(i == -1){
                continue;
            }

            if((min == -1) || (i < min)){
                min = i;
            }
        }
        if(min == -1){
            return -1;
        }else{
            return 1 + min;
        }
    }else{ // Feld ist kein gültiges Pfadfindefeld
        return -1;
    }
}

// Überprüft ob der Feldinhalt einem gültigen Feldwert entspricht
bool Maze::validField(const char& field){
    bool valid = false;
    for(char validfield : validFields){
        if(field == validfield){
            valid = true;
        }
    }
    return valid;
}
bool Maze::validMaze(const int& maxRows, const int& maxColumns, const vector<vector<char>>& newMaze){
    if(newMaze.size() != maxRows){
        return false; // Wenn Vector falsche größe hat
    }
    for(vector<char> row : newMaze){
        if(row.size() != maxColumns){
            return false; // Wenn Vector falsche größe
        }
        for(char field : row){
            if(!validField(field)){
                return false;   //Wenn Feldinhalt nicht gültig ist
            }
        }
    }
    return true;
}


void Maze::changeField(const int row, const int column, const char newField){
        if(!validField(newField)){
            throw BadMaze{};
        }else if(row >= rows || column >= cols){
            throw BadMaze{};
        }
        
        data_[row][column] = newField;
    }



vector<vector<char>> Maze::data(){
    return data_;
}
