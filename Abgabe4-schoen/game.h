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
    Maze maze; // Das Labyrinth
    Player player; // Die SpielerIn
    bool exit; // Wurde 'q' gerdückt?
    bool hit_ghost; // Wurde ein Geist getroffen?
    bool info_mode; // Ist der Infomode aktiviert?
};

GameState process_tile_action(GameState game_state);
bool position_is_walkable(vector<int> position, GameState game_state);
GameState move_player(GameState game_state, char direction);
bool reached_goal(GameState game_state);
bool hit_ghost(GameState game_state);



#endif