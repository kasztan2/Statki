#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <random>
#include <time.h>
#include "funkcje_gry.h"
#include "plansza.h"
using std::string, std::cout, std::deque, std::to_string, std::pair, std::vector, std::queue;

class Bot2{
    private:
    int x;
    int y;
    int pusta;
    int miejsce;

    public:
    int strzal(char planszabot [10][10], bool poprzednie_strzaly[][10], int ilosc_statkow[4], int bot_rysuj[10][10]){


srand(time(NULL));
x = -1;
y = -1;
pusta = -1;


while (true){
miejsce = rand()%100;
x= miejsce/10;
y = miejsce %10;
if (bot_rysuj[x][y] != 1 && bot_rysuj[x][y] != 2 ){
    break;
}
}
        if (planszabot[x][y] == '#'){
        bot_rysuj [x][y] = 1;

        for (int i =0;i<10;i++){
            for(int j=0;j<10;j++){
                if (planszabot[i][j]=='#'&& bot_rysuj[i][j]!= 1){
                    pusta = 0;
                }

            }
        }

        if(pusta != 0){
            ilosc_statkow [0] = 0;
            ilosc_statkow [1] = 0;
            ilosc_statkow [2] = 0;
            ilosc_statkow [3] = 0;

        }


        return 1;   
        }
        else {
            bot_rysuj [x][y] = 2;
            return 0;
        }
    }
};
