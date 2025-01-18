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
    void toggle_info_mode();
    void process_tile_action();
    bool position_is_walkable(vector<int>& position);
    void move_player(char& direction);
    bool reached_goal();
    bool hit_ghost();
    bool is_end_condition();
    vector<int> new_position_by_direction(vector<int>& player_position, char& direction);
    
    Maze *maze; // Das Labyrinth
    Player *player; // Die 
    bool exit; // Wurde 'q' gerdückt?
    bool info_mode; // Ist der Infomode aktiviert?

private:
    bool hit_ghost_; // Wurde ein Geist getroffen?
};

#endif