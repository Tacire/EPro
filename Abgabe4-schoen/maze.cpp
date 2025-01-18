#include "maze.h"

// Gibt die benoetigte Schritte bis zum Ziel an
// nach vorgegebenen Agorithmus
int calculate_shortest_path_to_goal(Maze& maze, vector<unsigned int>& position, unsigned int& steps){
    if(position[0] < maze.rows && position[1] < maze.cols ){
        char field = game_state.maze.data[position[0]][position[1]];
    }else{
        return -1; // Out of Bounds
    }

    if(field == 'Z'){ // Ziel erreicht
        return 0;
    }else if(steps == 0){ // Schrittlimit erreicht
        return -1;
    }else if(field == '.' || field == 'K' || field == 'A'){ // Wenn das Feld valid ist wird rekursiv weitergesucht
        vector <int> possible_ways;
        possible_ways.push_back(steps_til_goal(game_state, {position[0]+1,position[1]}, steps -1));
        possible_ways.push_back(steps_til_goal(game_state, {position[0]-1,position[1]}, steps -1));
        possible_ways.push_back(steps_til_goal(game_state, {position[0],position[1]+1}, steps -1));
        possible_ways.push_back(steps_til_goal(game_state, {position[0],position[1]-1}, steps -1));

        int min = -1;
        for(int i : possible_ways){
            if(i == -1){
                continue;
            }

            if((min == -1) || (i < min)){
                min = i;
            }
        }
        if(min == -1){
            return -1;
        }else{
            return 1 + min;
        }
    }else{ // Feld ist kein gültiges Pfadfindefeld
        return -1;
    }
}

