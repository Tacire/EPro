// Interface zum Spiel. Initialisiert das Spiel, behandelt Fehler und beendet es.
// Stark reduzierte Version der Vorlage. Funktionen soweit es geht in Klassen ausgelagert

#include "game.h"
#include "helper.h"

//===================Initialisierung===============================

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
vector<vector<char>> read_maze_data(const int& rows, const int& cols)
{
    vector<vector<char>> maze_data(rows);
    char ch;
    for(int i = 0; i < rows * cols; ++i)
    {
        cin >> ch;
        if(!cin) {throw BadMaze {};}
        if(!(ch == '#' || ch == 'T' || ch == 'A' || ch == '.' || ch == 'K' || ch == 'Z'  || ch == 'B'  || ch == 'C'))
        {
            throw BadMaze {};
        }

        maze_data[i / cols].push_back(ch);
    }
    return maze_data;
}

// Initialisiert das Spiel
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

    //Erstellt Instanz eines Spiels. Gibt die Referenz darauf zurück
    GameState* game = new GameState{rows, cols, labyrinth_data, player_row, player_col};
    return game;
}

//==================================================================


// Quasi 1 zu 1 die vorgegebene main. Initiaisiert, startet Spiel und gibt custom Endnachricht aus
int main()
{
    activateAssertions();
    try
    {
        GameState* game_state = initialize();

        game_state->game_loop();

        if(game_state->reached_goal())
        {
            game_state->display_maze(); //Notwendig für automatische Tests
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
