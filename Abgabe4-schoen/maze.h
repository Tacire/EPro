#ifndef MAZE_H
#define MAZE_H
#pragma once

#include "std_lib_inc.h"
#include "helper.h"

// Klasse, die das Labyrinth kapselt
class Maze
{
public:
    Maze(int& maxRows, int& maxColumns, vector<vector<char>>& newMaze);
    
    int calculate_shortest_path_to_goal(vector<int> position, int steps = 5);
    void changeField(int& row, int& column, char& newField);
    bool validField(char& field);
    bool validMaze(int& maxRows, int& maxColumns, vector<vector<char>>& newMaze);
    vector<vector<char>> data();

        
    int rows; // Anzahl der Zeilen des Labyrinths
    int cols; // Anzahl der Spalten des Labyrinths
    static constexpr char validFields[] = "ATK.#Z";

private:
    vector<vector<char>> data_; // Labyrinth-Daten (erst Zeilen dann Spalten)
};


#endif