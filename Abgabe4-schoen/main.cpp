#include "game.h"
#include "helper.h"


// Liest ein integer von der Eingabe.
// Vorbedingung: cin ist in Ordnung
int read_int()
{
    int integer;
    cin >> integer;
    if(!cin) {throw BadMaze{};}
    return integer;
}

// Liest die Labyrinth-Daten ein.
// Vorbedingung: cin ist ok.
vector<vector<char>> read_maze_data(int& rows, int& cols)
{
    vector<vector<char>> maze_data(rows);
    char ch;
    for(int i = 0; i < rows * cols; ++i)
    {
        cin >> ch;
        if(!cin) {throw BadMaze {};}
        if(!(ch == '#' || ch == 'T' || ch == 'A' || ch == '.' || ch == 'K' || ch == 'Z'))
        {
            throw BadMaze {};
        }

        maze_data[i / cols].push_back(ch);
    }
    return maze_data;
}

// Initialisiert das Labyrinth-Objekt
GameState* initialize()
{
    int rows = read_int();
    int cols = read_int();

    if(rows < 1 || cols < 1 || rows > 20 || cols > 20)
    {
        throw BadMaze {};
    }

    vector<vector<char>> labyrinth_data = read_maze_data(rows, cols);

    int player_row = read_int();
    int player_col = read_int();

    if(player_row < 0 || player_row >= rows || player_col < 0 || player_col >= cols)
    {
        throw BadMaze {};
    }

    if(labyrinth_data[player_row][player_col] != '.')
    {
        throw BadMaze {};
    }

    GameState* game = new GameState{rows, cols, labyrinth_data, player_row, player_col};
    return game;
}

// Gibt eine kurze Hilfe aus
void display_help()
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

// Reagiert auf das eingegebene Kommando und gibt an die jeweilige Funktion
// ab, die sich um genau dieses Kommando kuemmert.
void process_input(GameState* game_state, char input)
{
    switch(input)
    {
        case 'w':
        case 's':
        case 'a':
        case 'd':
            game_state->move_player(input);
            return;
        case 'i':
            game_state->toggle_info_mode();
            return;
        case 'h':
        case 'H':
            display_help();
            return;
        case 'q':
            game_state->exit = true;
            return;
        default:
            throw UnknownInput{};
    }
    return;
}


// Funktion zur Anzeige des Spielfeldes
void display_maze(GameState* game_state)
{
    const int player_row = game_state->player->position[0];
    const int player_col = game_state->player->position[1];

    //cout << "\033[H\033[J"; // ANSI Escape Code zum Loeschen des Bildschirms
    for(int i = 0; i < game_state->maze->rows; i++)
    {
        for(int j = 0; j < game_state->maze->cols; j++)
        {
            if(i == player_row && j == player_col)
            {
                cout << 'S';
            }
            else
            {
                cout << game_state->maze->data()[i][j];
            }
            cout << " ";
        }
        // Printet Infomode nach der ersten Zeile falls aktiviert
        if(game_state->info_mode && (i == 0)){
            if(game_state->maze->calculate_shortest_path_to_goal(game_state->player->position) != -1){
                cout << game_state->maze->calculate_shortest_path_to_goal(game_state->player->position) << " Schritte bis zum Ziel";
            }
        };
        cout << '\n';
    }
}


// Die Hauptschleife des Spiels
void game_loop(GameState* game_state)
{
    char input;
    while(cin && !game_state->is_end_condition())
    {
  /**      assert(game_state.player.hasKey >= 0,
            "Player has a negative number of keys.");
    */
        display_maze(game_state);

        cin >> input;
        if(cin)
        {
            try
            {
                process_input(game_state, input);
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



int main()
{
    activateAssertions();
    try
    {
        GameState* game_state = initialize();

        game_loop(game_state);

        if(game_state->reached_goal())
        {
            display_maze(game_state);
            cout << "Ziel erreicht! Herzlichen Glueckwunsch!\n";
        }
        else if(game_state->hit_ghost())
        {
            cout << "Sie haben einen Geist getroffen! Game Over!\n";
        }
        else
        {
            cout << "Schoenen Tag noch!\n";
        }
        return 0;
    }
    catch(BadMaze&)
    {
        cout << "Fehler beim Einlesen des Labyrinths.\n";
        return 1;
    }
    catch(...)
    {
        cout << "Unbekannter Fehler!\n";
        return 1;
    }
}
