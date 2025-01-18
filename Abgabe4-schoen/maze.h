#ifndef MAZE_H
#define MAZE_H
#pragma once

#include "std_lib_inc.h"
#include "helper.h"

// Klasse, die das Labyrinth kapselt
class Maze
{
public:
    Maze(unsigned int& maxRows, unsigned int& maxColumns, vector<vector<char>> newMaze){
        if(!checkValidField(rows,columns,newMaze)){
            throw BadMaze{};
        }
        rows = maxRows;
        cols = maxColumns;
        kMaze = newMaze;
    }
    const unsigned int rows; // Anzahl der Zeilen des Labyrinths
    const unsigned int cols; // Anzahl der Spalten des Labyrinths
    static constexpr char validFields[] = "ATK.#Z";

    vector<vector<char>> data(){
        return data_;
    }

    void changeField(unsigned int& row, unsigned int& column, char& newField){
            if(!checkValidChar(newField)){
                throw BadMaze{};
            }else if(row >= maxRow || column >= maxColumn){
                throw BadMaze{};
            }
            
            data_[row][column] = newField;
            return 0;
        }

private:
    vector<vector<char>> data_; // Labyrinth-Daten (erst Zeilen dann Spalten)
};

int calculate_shortest_path_to_goal(Maze& maze, vector<unsigned int>& position, unsigned int& steps);

#endif