#ifndef MAZE_H
#define MAZE_H
#pragma once

#include "std_lib_inc.h"
#include "helper.h"

// Klasse, die das Labyrinth kapselt
class Maze
{
public:
    Maze(const int& maxRows, const int& maxColumns, const vector<vector<char>>& newMaze);
    
    int calculate_shortest_path_to_goal(const vector<int> position, const int steps = 5);
    void changeField(const int row, const int column, const char newField);
    bool validField(const char& field);
    bool validMaze(const int& maxRows, const int& maxColumns, const vector<vector<char>>& newMaze);
    vector<vector<char>> data();

        
    int rows; // Anzahl der Zeilen des Labyrinths
    int cols; // Anzahl der Spalten des Labyrinths
    static constexpr char validFields[] = "ATK.#Z";

private:
    vector<vector<char>> data_; // Labyrinth-Daten (erst Zeilen dann Spalten)
};


#endif