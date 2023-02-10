#include "../include/bot.hpp"

Bot::Bot() : direction(0), posX(0), posY(0){
    cout << "Bot created at " << this << endl;
}

void Bot::move(int x, int y){

    if((x == 1 || -1) && (y == 1 || -1)){
        posX += x;
        posY += y;

        cout << "Position of the Bot X: " << posX << ", Y: " << posY << endl;
    }
    else{
        cout << "No allowed movement!" << endl;
    }
}

int Bot::explore(vector<vector<int>> field){

    while(1){

        // check if the field is free in what the Bot is in:
        if(field[posX][posY] == 0){
            // Map in this place = 0;
        }
        else{
            // Map in this Place = 1;
        }

        // Move
    }
}