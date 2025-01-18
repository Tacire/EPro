#include "game.h"


// Togglet den Info Modus an bzw. aus
void toggle_info_mode(GameState& game_state){
    if(game_state.info_mode){
        game_state.info_mode = false;
    }else{
       game_state.info_mode = true; 
    }
}

// Fuehrt Aktionen des Spieler-Feldes aus
// Vorbedingung: Wenn das Feld eine Tuer ist, muss mindestens ein Schluessel zur Verfuegung stehen
GameState process_tile_action(GameState game_state)
{
    const int row = game_state.player.position[0];
    const int col = game_state.player.position[1];

    assert(game_state.maze.data[row][col] != 'T' || game_state.player.no_keys > 0,
        "process_tile_action(...) assumes enough keys are there when approaching a door.");

    if(game_state.maze.data[row][col] == 'K')
    {
        ++game_state.player.no_keys;
        game_state.maze.data[row][col] = '.';
    }
    else if(game_state.maze.data[row][col] == 'T')
    {
        --game_state.player.no_keys;
        game_state.maze.data[row][col] = '.';
    }
    else if(game_state.maze.data[row][col] == 'A')
    {
        game_state.hit_ghost = true;
    }
    return game_state;
}


// Gibt true zurueck gdw. die Position begehbar ist
bool position_is_walkable(vector<int> position, GameState game_state)
{
    const int row = position[0];
    const int col = position[1];

    if(row < 0 || col < 0)
    {
        return false;
    }
    if(row >= game_state.maze.rows || col >= game_state.maze.cols)
    {
        return false;
    }
    if(game_state.maze.data[row][col] == '#')
    {
        return false;
    }
    if(game_state.maze.data[row][col] == 'T' && game_state.player.no_keys == 0)
    {
        return false;
    }
    return true;
}


// Funktion zur Bewegung der SpielerIn
GameState move_player(GameState game_state, char direction)
{
    vector<int> potential_new_position = new_position_by_direction(game_state.player.position, direction);

    if(!position_is_walkable(potential_new_position, game_state))
    {
        throw BadMovement {};
    }

    game_state.player.position = potential_new_position;
    return process_tile_action(game_state);
}


// Gibt true zurueck, wenn das Ziel erreicht wurde
bool reached_goal(GameState game_state)
{
    return game_state.maze.data[game_state.player.position[0]][game_state.player.position[1]] == 'Z';
}


// Gibt true zurueck gdw der Geist getroffen wurde
bool hit_ghost(GameState game_state)
{
    return game_state.hit_ghost;
}


// Gibt true zurueck gdw. das Spiel zuende ist
bool is_end_condition(GameState game_state)
{
    return reached_goal(game_state) || hit_ghost(game_state) || game_state.exit;
}

// Die Hauptschleife des Spiels
GameState game_loop(GameState game_state)
{
    char input;
    while(cin && !is_end_condition(game_state))
    {
        assert(game_state.player.no_keys >= 0,
            "Player has a negative number of keys.");

        display_maze(game_state);

        cin >> input;
        if(cin)
        {
            try
            {
                game_state = process_input(game_state, input);
            }
            catch(BadMovement&)
            {
                cout << "Bewegung nicht moeglich!\n";
            }
            catch(UnknownInput&)
            {
                cout << "Diese Eingabe kenne ich nicht. Gib 'h' ein, um eine Hilfe zu erhalten.\n";
            }
        }
    }

    return game_state;
}