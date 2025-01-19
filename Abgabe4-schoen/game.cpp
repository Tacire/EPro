#include "game.h"

GameState::GameState(const int& rows, const int& cols, const vector<vector<char>>& labyrinth_data, const int& player_row, const int& player_col){
    
    vector<vector<char>> prepared_labyrinth = create_ghosts(labyrinth_data);
    maze_ = new Maze(rows,cols,prepared_labyrinth);
    player_ = new Player(player_row, player_col);
    info_mode_ = false;
    exit_ = false;
    hit_ghost_ = false;
}

// Füllt Liste der existierenden Bowie und Conelly Geister (erstellt "Geister"-Instanzen).
// Löscht diese aus der Labyrinth Karte und gibt die neue Karte zurück
vector<vector<char>> GameState::create_ghosts(const vector<vector<char>>& labyrinth_data){
    vector<vector<char>> updated_maze_data;

    const int no_rows = labyrinth_data.size();
    for(int i = 0; i < no_rows; i++)
    {
        int no_columns = labyrinth_data[i].size();
        vector<char> rows = {};
        for(int j = 0; j < no_columns; j++){
            char field = labyrinth_data[i][j];
            if(field == 'B'){
                bowie_ghosts_.push_back(new Bowie(i,j));
                field = '.';
            }else if(field == 'C'){
                conelly_ghosts_.push_back(new Conelly(i,j));
                field = '.';
            }
            rows.push_back(field);
        }
        if(!rows.empty()){
            updated_maze_data.push_back(rows);
        }
    }
    return updated_maze_data;
};

// Togglet den Info Modus an bzw. aus
void GameState::toggle_info_mode(){
    if(info_mode_){
        info_mode_ = false;
    }else{
       info_mode_ = true; 
    }
}

// Gibt true zurueck gdw. die Position begehbar ist
bool GameState::position_is_walkable(const vector<int>& position)
{
    const int row = position[0];
    const int col = position[1];

    if(row < 0 || col < 0)
    {
        return false;
    }
    if(row >= maze_->get_rows() || col >= maze_->get_cols())
    {
        return false;
    }
    if(maze_->data()[row][col] == '#')
    {
        return false;
    }
    if(maze_->data()[row][col] == 'T' && (!player_->has_key()))
    {
        return false;
    }
    return true;
}

// Funktion zur Bewegung der SpielerIn
void GameState::move_player(const char& direction)
{
    vector<int> potential_new_position = new_position_by_direction(player_->get_position(), direction);

    if(!position_is_walkable(potential_new_position))
    {
        throw BadMovement {};
    }

    player_->set_position(potential_new_position);
    process_tile_action();
}

// Fuehrt Aktionen des Spieler-Feldes aus
// Vorbedingung: Wenn das Feld eine Tuer ist, muss mindestens ein Schluessel zur Verfuegung stehen
void GameState::process_tile_action()
{
    check_ghost_collision();
    
    const int row = player_->get_position()[0];
    const int col = player_->get_position()[1];

    assert(maze_->data()[row][col] != 'T' || player_->has_key(), // Fehler wenn auf Türfeld und keine Schlüssel
        "process_tile_action(...) assumes enough keys are there when approaching a door.");

    if(maze_->data()[row][col] == 'K') // Schlüssel
    {
        player_->add_key();
        maze_->change_field(row,col,'.');
    }
    else if(maze_->data()[row][col] == 'T') // Tür
    {
        player_->use_key();
        maze_->change_field(row,col,'.');
    }
    else if(maze_->data()[row][col] == 'A') // Standard Geist
    {
        hit_ghost_ = true;
    }
}

//Überprüft ob Spieler auf der Position eines dynamischen Geistes ist
void GameState::check_ghost_collision(){
    vector<int> player_pos = player_->get_position();
    
    //Überprüft alle Bowie Geister
    for(ghost : bowie_ghosts_){
        if(ghost->position == player_pos){
            hit_ghost = true;
            return;
        }
    }
    //Überprüft alle Conelly Geister
    for(ghost : conelly_ghosts_){
        if(ghost->position == player_pos){
            hit_ghost = true;
            return;
        }
    }

}

// Gibt true zurueck, wenn das Ziel erreicht wurde
bool GameState::reached_goal()
{
    return maze_->data()[player_->get_position()[0]][player_->get_position()[1]] == 'Z';
}


// Gibt true zurueck gdw der Geist getroffen wurde
bool GameState::hit_ghost()
{
    return hit_ghost_;
}

// Gibt true zurueck gdw. das Spiel zuende ist
bool GameState::is_end_condition()
{
    return reached_goal() || hit_ghost() || exit_;
}


// Funktion zur Umrechnung eines Kommandos zu einer neuen Position
// Vorbedingung: direction muss aus {w, s, a, d} kommen.
vector<int> GameState::new_position_by_direction(const vector<int>& player_position, const char& direction)
{
    const int row = player_->get_position()[0];
    const int col = player_->get_position()[1];

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
void GameState::process_input(const char input)
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
            exit_ = true;
            return;
        default:
            throw UnknownInput{};
    }
    return;
}


// Funktion zur Anzeige des Spielfeldes
void GameState::display_maze()
{
    const int player__row = player_->get_position()[0];
    const int player__col = player_->get_position()[1];

    //cout << "\033[H\033[J"; // ANSI Escape Code zum Loeschen des Bildschirms
    for(int i = 0; i < maze_->get_rows(); i++)
    {
        for(int j = 0; j < maze_->get_cols(); j++)
        {
            if(i == player__row && j == player__col)
            {
                cout << 'S';
            }
            else
            {
                cout << maze_->data()[i][j];
            }
            cout << " ";
        }
        // Printet Infomode nach der ersten Zeile falls aktiviert
        if(info_mode_ && (i == 0)){
            int distance = maze_->calculate_shortest_path_to_goal(player_->get_position());
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
  /**      assert(game_state.player_.hasKey >= 0,
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
