#ifndef GAME_H
#define GAME_H
#pragma once

#include "maze.h"
#include "player.h"
#include "helper.h"


// Fasst Labyrinth und Spieler zu einem Spiel-Status zusammen
class GameState
{
public:
    GameState(int& rows, int& cols, vector<vector<char>>& labyrinth_data, int& player_row, int& player_col);
    
    //Öffentliche Methoden fürs Interface
    void game_loop();
    bool reached_goal();
    bool hit_ghost();

private:
    Maze *maze; // Das Labyrinth
    Player *player; // Die 

    bool hit_ghost_; // Wurde ein Geist getroffen?
    bool exit; // Wurde 'q' gerdückt?
    bool info_mode; // Ist der Infomode aktiviert?

    // Spieler-Management
    void toggle_info_mode();
    void display_help();
    void process_input(char input);
    void display_maze();

    // Spiel-Methoden
    bool position_is_walkable(vector<int>& position);
    vector<int> new_position_by_direction(vector<int>& player_position, char& direction);
    void move_player(char& direction);
    void process_tile_action();
    bool is_end_condition();

};

#endif