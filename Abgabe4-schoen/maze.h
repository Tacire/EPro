#ifndef MAZE_H
#define MAZE_H
#pragma once

#include "std_lib_inc.h"
#include "helper.h"

// Klasse, die das Labyrinth kapselt
class Maze
{
public:
    Maze(unsigned int& maxRows, unsigned int& maxColumns, vector<vector<char>>& newMaze);
    unsigned int rows; // Anzahl der Zeilen des Labyrinths
    unsigned int cols; // Anzahl der Spalten des Labyrinths

    int calculate_shortest_path_to_goal(vector<int> position, unsigned int steps);

    vector<vector<char>> data();

    void changeField(unsigned int& row, unsigned int& column, char& newField);
    bool validField(char& field);
    bool validMaze(unsigned int& maxRows, unsigned int& maxColumns, vector<vector<char>>& newMaze);
    static constexpr char validFields[] = "ATK.#Z";

private:
    vector<vector<char>> data_; // Labyrinth-Daten (erst Zeilen dann Spalten)
};


#endif