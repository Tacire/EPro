#include "maze.h"


// Gibt die benoetigte Schritte bis zum Ziel an
// nach vorgegebenen Agorithmus
int steps_til_goal(GameState game_state, vector<int> position, int steps){
    if(!position_is_walkable(position, game_state)){
        return -1;
    }else if(game_state.maze.data[position[0]][position[1]] == 'T'){
        return -1;
    }else if(game_state.maze.data[position[0]][position[1]] == 'Z'){
        return 0;
    }else if(steps == 0){
        return -1;
    }else{
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
    }
    return -1;
}
