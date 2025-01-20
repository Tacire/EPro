#ifndef MAZE_H
#define MAZE_H
#pragma once

#include "std_lib_inc.h"
#include "helper.h"

/**
 * Maze-Klasse,
 * beinhaltet ein gültiges Maze, eine Pfadfindemethode sowie diverse Feldüberprüfungen
 */
class Maze
{
public:
    //Konsten aus denen ein fertiges Labyrinth bestehen darf
    static constexpr char valid_fields[] = "ATK.#Z";

    // Konstruktor, erzeugt Labyrinth basierend auf Parameter
    Maze(const int& maxRows, const int& maxColumns, const vector<vector<char>>& newMaze);

    // minimale Labyrinth Getter & Setter
    vector<vector<char>> data();
    void change_field(const int& row, const int& column, const char& newField);
    int get_rows();
    int get_cols();

    // Kalkuliert von gegebener Position (rekursiv) die Distanz zum Ziel
    int calculate_shortest_path_to_goal(const vector<int>& position, const int& steps = 5);
    bool check_wall(const int& row, const int& column); // Überprüft Feld auf Wand, Tür oder Spielfeldgrenze
    

private:
    const int rows_; // Anzahl der Zeilen des Labyrinths
    const int cols_; // Anzahl der Spalten des Labyrinths
    vector<vector<char>> data_; // Labyrinth-Daten (erst Zeilen dann Spalten)

    //================ Hilfsmethoden für Klassenmethoden ============================
    bool inbounds(const int& row, const int& column);
    bool valid_field(const char& field);
    bool valid_maze(const int& maxRows, const int& maxColumns, const vector<vector<char>>& newMaze);
    //=================================================================================
    
};


#endif