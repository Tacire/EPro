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


// Reagiert auf das eingegebene Kommando und gibt an die jeweilige Funktion
// ab, die sich um genau dieses Kommando kuemmert.
void GameState::process_input(char input)
{
    switch(input)
    {
        case 'w':
        case 's':
        case 'a':
        case 'd':
            move_player(input);
            return;
        case 'i':
            toggle_info_mode();
            return;
        case 'h':
        case 'H':
            display_help();
            return;
        case 'q':
            exit = true;
            return;
        default:
            throw UnknownInput{};
    }
    return;
}


// Funktion zur Anzeige des Spielfeldes
void GameState::display_maze()
{
    const int player_row = player->position[0];
    const int player_col = player->position[1];

    //cout << "\033[H\033[J"; // ANSI Escape Code zum Loeschen des Bildschirms
    for(int i = 0; i < maze->rows; i++)
    {
        for(int j = 0; j < maze->cols; j++)
        {
            if(i == player_row && j == player_col)
            {
                cout << 'S';
            }
            else
            {
                cout << maze->data()[i][j];
            }
            cout << " ";
        }
        // Printet Infomode nach der ersten Zeile falls aktiviert
        if(info_mode && (i == 0)){
            int distance = maze->calculate_shortest_path_to_goal(player->position);
            if(distance != -1){ // Für den Fall Unendlich (d.h distanz zu groß bzw. unmöglich)
                if(distance == 1){ //Gramatikalischer Sonderfall, relevant für automatische Tests
                    cout << distance << " Schritt bis zum Ziel";
                }else{
                    cout << distance << " Schritte bis zum Ziel";
                }
            }
        };
        cout << '\n';
    }
}


// Die Hauptschleife des Spiels
void GameState::game_loop()
{
    char input;
    while(cin && !is_end_condition())
    {
  /**      assert(game_state.player.hasKey >= 0,
            "Player has a negative number of keys.");
    */
        display_maze();

        cin >> input;
        if(cin)
        {
            try
            {
                process_input(input);
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
}

// Gibt eine kurze Hilfe aus
void GameState::display_help()
{
    cout << "Willkommen zum Labyrinth-Spiel!\n";
    cout << "Ziel des Spiels: Finden Sie den Weg vom Startpunkt (S) zum Ziel (Z).\n";
    cout << "Spielfeld-Erklaerung:\n";
    cout << "S - Startpunkt: Hier beginnt die SpielerIn.\n";
    cout << "Z - Ziel: Erreichen Sie diesen Punkt, um das Spiel zu gewinnen.\n";
    cout << "# - Wand: Diese Felder sind nicht begehbar.\n";
    cout << "K - Schluessel: Hier können Sie einen Schluessel aufsammeln, um eine Tuer zu oeffnen.\n";
    cout << "T - Tuer: Unbegehbares Feld, ausser, Sie haben einen Schluessel. Beim Durchschreiten wird ein Schluessel verbraucht.\n";
    cout << "A - Geist: Ein Geist im Labyrinth. Stehen die SpielerIn auf dem selben Feld, verlieren Sie das Spiel!\n";
    cout << ". - Leeres Feld: Diese Felder koennen betreten werden.\n";
    cout << "\nSteuerung:\n";
    cout << "w - Nach oben bewegen\n";
    cout << "a - Nach links bewegen\n";
    cout << "s - Nach unten bewegen\n";
    cout << "d - Nach rechts bewegen\n";
    cout << "q - Spiel beenden\n";
    cout << "Nach jeder Befehlseingabe muss die Eingabetaste (Enter) gedrueckt werden, um sich zu bewegen.\n";
    cout << "\nViel Erfolg im Labyrinth!\n";
}
