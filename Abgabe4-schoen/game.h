#ifndef GAME_H
#define GAME_H
#pragma once

#include "maze.h"
#include "player.h"
#include "bowie.h"
#include "conelly.h"
#include "helper.h"


// Fasst Labyrinth und Spieler zu einem Spiel-Status zusammen
class GameState
{
public:
    //Konstruktor erzeugt Spieler und Labirinth Instanz basierend auf Eingabewerten
    GameState(const int& rows, const int& cols, const vector<vector<char>>& labyrinth_data, const int& player_row, const int& player_col);
    
    //Öffentliche Methoden fürs Interface
    void game_loop(); // Hauptmethode des Spiels
    bool reached_goal(); // True wenn Ziel erreicht
    bool hit_ghost(); // True wenn durch Ghost gestorben
    void display_maze();

private:
    //========== Spieler und Labyrinth Instanzen ==========
    Maze * maze_; // Das Labyrinth
    Player * player_; // Spielfigur

    //=============== GameState-Variablen =================
    bool hit_ghost_; // Wurde ein Geist getroffen?
    bool exit_; // Wurde 'q' gerdückt?
    bool info_mode_; // Ist der Infomode aktiviert?
    vector<Bowie*> bowie_ghosts_;
    vector<Conelly*> conelly_ghosts_;

    //=============== Spieler-Management ===================
    void toggle_info_mode();
    void display_help();
    void process_input(const char input);

    //================ Spiel-Methoden=======================
    vector<vector<char>> create_ghosts(const vector<vector<char>>& unprepared_maze_data);
    void check_ghost_collision();
    bool position_is_walkable(const vector<int>& position);
    vector<int> new_position_by_direction(const vector<int>& player_position, const char& direction);
    void move_player(const char& direction);
    void process_tile_action();
    void move_ghosts();
    bool is_end_condition();
    //======================================================
};

#endif