#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <random>
#include <time.h>

#include "funkcje_gry.h"
#include "plansza.h"

#define shot_bot strzal

using std::string, std::cout, std::deque, std::to_string, std::pair, std::vector, std::queue;

class Bot3{
    private:
    //char statek = '#';
    //char puste_pole = ' ';
    int tablicawar [10][10];

    bool isemptyshot (int do_rysowania [10][10]){
for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (do_rysowania [i][j]!=1 && do_rysowania [i][j]!=2)
        return false;
    }}
    return true;
}
  bool is4 (int do_rysowania [10][10]){
for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 7; j++) {
            if (do_rysowania[i][j] == 1 && do_rysowania[i][j+1] == 1 && do_rysowania[i][j+2] == 1 && do_rysowania[i][j+3] == 1) {
                return true;
            }
        }
    }
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 10; j++) {
            if (do_rysowania[i][j] == 1 && do_rysowania[i+1][j] == 1 && do_rysowania[i+2][j] == 1 && do_rysowania[i+3][j] == 1) {
                return true;
            }
        }
    }
    return false;
}  

bool is3(int do_rysowania [10][10]){

for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 8; j++) {
            if (do_rysowania[i][j] == 1 && do_rysowania[i][j+1] == 1 && do_rysowania[i][j+2] == 1 ) {
                return true;
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            if (do_rysowania[i][j] == 1 && do_rysowania[i+1][j] == 1 && do_rysowania[i+2][j] == 1 ) {
                return true;
            }
        }
    }
    return false;
}

bool is2(int do_rysowania [10][10]){

for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 9; j++) {
            if (do_rysowania[i][j] == 1 && do_rysowania[i][j+1] == 1 ) {
                return true;
            }
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) {
            if (do_rysowania[i][j] == 1 && do_rysowania[i+1][j] == 1) {
                return true;
            }
        }
    }
    return false;
}


bool is1(char tablica_bot[10][10],int do_rysowania[10][10]){
    for(int i=0;i<10;i++){
        for(int j = 0; j<10;j++) {
            if(tablica_bot[i][j] == '#' && do_rysowania[i][j]!= 1)
        return true;
        }
    }
    return false;
}

    
   int bot (char tablica_bot [10][10],int tablicawar[10][10],int do_rysowania [10][10]){
int miejscestrzal;
int z1;
int z2;
if (isemptyshot(do_rysowania)){
debug("a ");

srand(time(NULL));
miejscestrzal = rand()%8;

int x;
int y;
int k =0;

for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (tablicawar [i][j]!=0 && k<=miejscestrzal){
        x = i;
        y = j;
        k++;
       }
    }
}

return (x*10+y);
}

else if (is4(do_rysowania)){
debug("b ");
  for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (do_rysowania [i][j]== 1 ||do_rysowania [i][j]== 2 ){
        tablicawar [i][j] = -1;
        z1= (10*i+3+j)/10;
        z2= (10*i+3+j)%10;
        if (tablicawar[z1][z2]!=-1 && 10*i+3+j<100){
            tablicawar[z1][z2] = tablicawar [z1][z2] +1;
        }
        z1= (10*i-3+j)/10;
        z2= (10*i-3+j)%10;
        if (tablicawar[z1][z2]!=-1 && 10*i-3+j>=0){
            tablicawar[z1][z2] = tablicawar [z1][z2] +1;
        }
        z1= (10*(i-3)+j)/10;
        z2= (10*(i-3)+j)%10;
        if (tablicawar[z1][z2]!=-1 && 10*(i-3)+j>=0){
            tablicawar[z1][z2] = tablicawar [z1][z2] +1;
        }
        z1= (10*(i+3)+j)/10;
        z2= (10*(i+3)+j)%10;
        if (tablicawar[z1][z2]!=-1 && 10*(i+3)+j<100){
            tablicawar[z1][z2] = tablicawar [z1][z2] +1;
        }
    }}}
   
  int maximum =0;
  int ile = 0;
    for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (tablicawar [i][j]>maximum)
        maximum = tablicawar [i][j];}}

    for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (tablicawar [i][j]==maximum)
        ile++;}}
        

   srand(time(NULL));
miejscestrzal = rand()%ile;
ile =0;


for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (tablicawar [i][j]==maximum && ile<=miejscestrzal){
        z1 = i;
        z2 = j;
        ile++;
       }
    }
}

   return (z1*10+z2);
}

else if(is3(do_rysowania)){
     debug("c ");
  for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (do_rysowania [i][j]== 1 ||tablica_bot [i][j]== 2)
        tablicawar [i][j] = -1;
        z1= (10*i+2+j)/10;
        z2= (10*i+2+j)%10;
        if (tablicawar[z1][z2]!=-1 && 10*i+2+j<100){
            tablicawar[z1][z2] = tablicawar [z1][z2] +1;
        }
        z1= (10*i-2+j)/10;
        z2= (10*i-2+j)%10;
        if (tablicawar[z1][z2]!=-1 && 10*i-2+j>=0){
            tablicawar[z1][z2] = tablicawar [z1][z2] +1;
        }
        z1= (10*(i-2)+j)/10;
        z2= (10*(i-2)+j)%10;
        if (tablicawar[z1][z2]!=-1 && 10*(i-2)+j>=0){
            tablicawar[z1][z2] = tablicawar [z1][z2] +1;
        }
        z1= (10*(i+2)+j)/10;
        z2= (10*(i+2)+j)%10;
        if (tablicawar[z1][z2]!=-1 && 10*(i+2)+j<100){
            tablicawar[z1][z2] = tablicawar [z1][z2] +1;
        }
    }}

  int maximum =0;
  int ile = 0;
    for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (tablicawar [i][j]>maximum)
        maximum = tablicawar [i][j];}}

    for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (tablicawar [i][j]==maximum)
        ile++;}}

   srand(time(NULL));
miejscestrzal = rand()%ile;
ile =0;

for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (tablicawar [i][j]==maximum && ile<=miejscestrzal){
        z1 = i;
        z2 = j;
        ile++;
       }
    }
}
   return (z1*10+z2);
}
else if (is2(do_rysowania)){
    debug("d ");
   for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (do_rysowania [i][j]== 1||do_rysowania [i][j]== 2)
        tablicawar [i][j] = -1;
        z1= (10*i+1+j)/10;
        z2= (10*i+1+j)%10;
        if (tablicawar[z1][z2]!=-1 && 10*i+1+j<100){
            tablicawar[z1][z2] = tablicawar [z1][z2] +1;
        }
        z1= (10*i-1+j)/10;
        z2= (10*i-1+j)%10;
        if (tablicawar[z1][z2]!=-1 && 10*i-2+j>=0){
            tablicawar[z1][z2] = tablicawar [z1][z2] +1;
        }
        z1= (10*(i-1)+j)/10;
        z2= (10*(i-1)+j)%10;
        if (tablicawar[z1][z2]!=-1 && 10*(i-2)+j>=0){
            tablicawar[z1][z2] = tablicawar [z1][z2] +1;
        }
        z1= (10*(i+1)+j)/10;
        z2= (10*(i+1)+j)%10;
        if (tablicawar[z1][z2]!=-1 && 10*(i+2)+j<100){
            tablicawar[z1][z2] = tablicawar [z1][z2] +1;
        }
    }}

  int maximum =0;
  int ile = 0;
    for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (tablicawar [i][j]>maximum)
        maximum = tablicawar [i][j];}}

    for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (tablicawar [i][j]==maximum)
        ile++;}}

   srand(time(NULL));
miejscestrzal = rand()%ile;
ile =0;

for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (tablicawar [i][j]==maximum && ile<=miejscestrzal){
        z1 = i;
        z2 = j;
        ile++;
       }
    }
}
   return (z1*10+z2);
}
else {
    debug("e ");
int maximum =0;
  int ile = 0;
    for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (tablicawar [i][j]>maximum)
        maximum = tablicawar [i][j];}}

    for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (tablicawar [i][j]==maximum)
        ile++;}}

   srand(time(NULL));
miejscestrzal = rand()%ile;
ile =0;

for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (tablicawar [i][j]==maximum && ile<=miejscestrzal){
        z1 = i;
        z2 = j;
        ile++;
       }
    }
}
   return (z1*10+z2);
}
}
    
    public:
    
    
  Bot3() {
    for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       tablicawar [i][j]=0;
    }
}
tablicawar [1][1] = 1;
tablicawar [2][0] = 1;
tablicawar [3][2] = 1;
tablicawar [4][7] = 1;
tablicawar [5][9] = 1;
tablicawar [6][8] = 1;
tablicawar [8][3] = 1;
tablicawar [9][5] = 1;  
}
    
    
  int shot_bot (char tablica_bot [10][10], bool poprzednie_strzaly[][10], int ilosc_statkow[4], int do_rysowania[10][10]){
int x;
int y;
int dostan = bot(tablica_bot,tablicawar,do_rysowania);

x = dostan/10;
y = dostan%10;

if (x>=0 && y>=0 && x<10 && y<10){
if (tablica_bot [x][y]== '#'){
    do_rysowania[x][y] = 1;

    if (tablica_bot[x+1][y] != '#'&& tablica_bot[x-1][y]!= '#' && tablica_bot[x][y+1] != '#' && tablica_bot[x][y-1]!= '#'){
        if (x+1<10){do_rysowania [x+1][y] = 2;}
        if (x-1 >=0){do_rysowania [x-1][y] = 2;}
        if (y+1<10){do_rysowania [x][y+1] = 2;}
        if (y-1 >=0){do_rysowania [x][y-1] =2;}
        if((x+1)<10 && (y+1)<10){
        do_rysowania [x+1][y+1] = 2;}

      if((x-1)>0 && (y-1)>0){
        do_rysowania [x-1][y-1] = 2;}

       if((x-1)>0 && (y+1)<10){
        do_rysowania [x-1][y+1] = 2;}

              if((x+1)<10 && (y-1)>0){
        do_rysowania [x+1][y-1] = 2;}
}

  else {   if((x+1)<10 && (y+1)<10){
        do_rysowania [x+1][y+1] = 2;}

      if((x-1)>0 && (y-1)>0){
        do_rysowania[x-1][y-1] = 2;}

       if((x-1)>0 && (y+1)<10){
        do_rysowania [x-1][y+1] = 2;}

              if((x+1)<10 && (y-1)>0){
        do_rysowania [x+1][y-1] = 2;}

        if (x+1<10 && tablicawar [x+1][y]!=-1){tablicawar [x+1][y] =(tablicawar [x+1][y]+1)*2;}
        if (x-1 >=0 && tablicawar [x-1][y]!= -1){tablicawar [x-1][y] =(tablicawar [x-1][y]+1)*2;}
        if (y+1<10 && tablicawar [x][y+1]!= -1){tablicawar [x][y+1] =(tablicawar [x][y+1]+1)*2;}
        if (y-1 >=0 && tablicawar [x][y-1]!= -1){tablicawar [x][y-1] =(tablicawar [x][y-1]+1)*2;}
        }




if (is1(tablica_bot,do_rysowania) ==false){
    ilosc_statkow [0] = 0;
    ilosc_statkow [1] = 0;
    ilosc_statkow [2] = 0;
    ilosc_statkow [3] = 0;
}



return 1;
}


do_rysowania[x][y] = 2;
return 0;
}
return -1;
}
  
          
};
