#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "std_lib_inc.h"

// Klasse, die eine SpielerIn kapselt
class Player {
    public:
        Player(unsigned int startRow, unsigned int startColumn){
            position = {startRow,startColumn};
            no_keys = 0;
        }
        Player(unsigned int startRow, unsigned int startColumn, unsigned int numberOfKeys){
            position = {startRow,startColumn};
            no_keys = numberOfKeys;
        }
        bool hasKey(){
            if(no_keys>0){
                return true;
            }
            return false;
        }
        void addKey(){
            no_keys++;
        }
        bool useKey(){
            if(no_keys>0){
                no_keys--;
                return true;
            }
            return false;
        }
        vector<unsigned int> position; // Aktuelle Position der SpielerIn im Labyrinth
    private:
        unsigned int no_keys; // Anzahl der Schlüssel der SpielerIn
};

#endif