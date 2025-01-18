#include "game.h"

GameState::GameState(int& rows, int& cols, vector<vector<char>>& labyrinth_data, int& player_row, int& player_col){
    maze = new Maze(rows,cols,labyrinth_data);
    player = new Player(player_row, player_col);
}

// Togglet den Info Modus an bzw. aus
void GameState::toggle_info_mode(){
    if(info_mode){
        info_mode = false;
    }else{
       info_mode = true; 
    }
}

// Gibt true zurueck gdw. die Position begehbar ist
bool GameState::position_is_walkable(vector<int>& position)
{
    const int row = position[0];
    const int col = position[1];

    if(row < 0 || col < 0)
    {
        return false;
    }
    if(row >= maze->rows || col >= maze->cols)
    {
        return false;
    }
    if(maze->data()[row][col] == '#')
    {
        return false;
    }
    if(maze->data()[row][col] == 'T' && (!player->hasKey()))
    {
        return false;
    }
    return true;
}

// Funktion zur Bewegung der SpielerIn
void GameState::move_player(char& direction)
{
    vector<int> potential_new_position = new_position_by_direction(player->position, direction);

    if(!position_is_walkable(potential_new_position))
    {
        throw BadMovement {};
    }

    player->position = potential_new_position;
    process_tile_action();
}

// Fuehrt Aktionen des Spieler-Feldes aus
// Vorbedingung: Wenn das Feld eine Tuer ist, muss mindestens ein Schluessel zur Verfuegung stehen
void GameState::process_tile_action()
{
    const int row = player->position[0];
    const int col = player->position[1];

    assert(maze->data()[row][col] != 'T' || player->hasKey(),
        "process_tile_action(...) assumes enough keys are there when approaching a door.");

    if(maze->data()[row][col] == 'K')
    {
        player->addKey();
        maze->data()[row][col] = '.';
    }
    else if(maze->data()[row][col] == 'T')
    {
        player->useKey();
        maze->data()[row][col] = '.';
    }
    else if(maze->data()[row][col] == 'A')
    {
        hit_ghost_ = true;
    }
}

// Gibt true zurueck, wenn das Ziel erreicht wurde
bool GameState::reached_goal()
{
    return maze->data()[player->position[0]][player->position[1]] == 'Z';
}


// Gibt true zurueck gdw der Geist getroffen wurde
bool GameState::hit_ghost()
{
    return hit_ghost_;
}

// Gibt true zurueck gdw. das Spiel zuende ist
bool GameState::is_end_condition()
{
    return reached_goal() || hit_ghost() || exit;
}


// Funktion zur Umrechnung eines Kommandos zu einer neuen Position
// Vorbedingung: direction muss aus {w, s, a, d} kommen.
vector<int> GameState::new_position_by_direction(vector<int>& player_position, char& direction)
{
    const int row = player->position[0];
    const int col = player->position[1];

    switch(direction)
    {
        case 'w':
            return {row - 1, col};
        case 's':
            return {row + 1, col};
        case 'a':
            return {row, col - 1};
        case 'd':
            return {row, col + 1};
        default:
            assert(false, "new_position_by_direction: invalid direction, assumes direction is one of {w, s, a, d}.");
            return {};
    }
}

