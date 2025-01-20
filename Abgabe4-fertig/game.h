#ifndef GAME_H
#define GAME_H
#pragma once

#include "maze.h"
#include "player.h"
#include "bowie.h"
#include "conelly.h"
#include "helper.h"

/**
 * Klasse des Spielablaufs. Handelt die gesammte Spiellogik,
 * Erstellt lokale Instanzen der Spielelemente, verwaltet Ein & Ausgabe
 */
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
    //========== Spieler, Geister und Labyrinth Instanzen ==========
    Maze * maze_; // Das Labyrinth
    Player * player_; // Spielfigur
    vector<Bowie*> bowie_ghosts_;  // Liste an Bowie Instanzen
    vector<Conelly*> conelly_ghosts_; // Liste an Conelly Instanzen

    //=============== GameState-Variablen =================
    bool hit_ghost_; // Wurde ein Geist getroffen?
    bool exit_; // Wurde 'q' gerdückt?
    bool info_mode_; // Ist der Infomode aktiviert?

    //=============== Spieler-Management ===================
    void toggle_info_mode();
    void display_help();
    void process_input(const char& input);
    vector<vector<char>> create_ghosts(const vector<vector<char>>& unprepared_maze_data);

    //================ Spiel-Methoden=======================
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