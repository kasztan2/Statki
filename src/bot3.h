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
    
    int tablicawar [10][10]; //tablica wartości strzałów dla bota

    bool isemptyshot (int do_rysowania [10][10]){
for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (do_rysowania [i][j]==1 || do_rysowania [i][j]==2)
        return false;
    }}
    return true;
}
  bool is4 (int do_rysowania [10][10]){
for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 7; j++) {
            if (do_rysowania[i][j] == 1 && do_rysowania[i][j+1] == 1 && do_rysowania[i][j+2] == 1 && do_rysowania[i][j+3] == 1) {
                return false;
            }
        }
    }
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 10; j++) {
            if (do_rysowania[i][j] == 1 && do_rysowania[i+1][j] == 1 && do_rysowania[i+2][j] == 1 && do_rysowania[i+3][j] == 1) {
                return false;
            }
        }
    }
    return true;
}  

bool is3(int do_rysowania [10][10]){

for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 8; j++) {
            if (do_rysowania[i][j] == 1 && do_rysowania[i][j+1] == 1 && do_rysowania[i][j+2] == 1 ) {
                return false;
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            if (do_rysowania[i][j] == 1 && do_rysowania[i+1][j] == 1 && do_rysowania[i+2][j] == 1 ) {
                return false;
            }
        }
    }
    return true;
}

bool is2(int do_rysowania [10][10]){

for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 9; j++) {
            if (do_rysowania[i][j] == 1 && do_rysowania[i][j+1] == 1 ) {
                return false;
            }
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) {
            if (do_rysowania[i][j] == 1 && do_rysowania[i+1][j] == 1) {
                return false;
            }
        }
    }
    return true;
}


bool is1(char tablica_bot[10][10],int do_rysowania[10][10]){
    for(int i=0;i<10;i++){
        for(int j = 0; j<10;j++) {
            if(tablica_bot[i][j] == '#' && do_rysowania[i][j]!= 1)
        return true;
        }
    }
    return false;
} // funkcja sprawdzająca czy plansza ma statki

    
   int bot (char tablica_bot [10][10],int tablicawar[10][10],int do_rysowania [10][10]){
int miejscestrzal;
int z1 = 0;
int z2 =0;
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
       if (tablicawar [i][j] ==maximum && ile<=miejscestrzal){
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
int maximum =-100;
  int ile = 0;


    for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (tablicawar [i][j] >=maximum){
        maximum = tablicawar [i][j];}
        }}

    for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (tablicawar [i][j]==maximum){
        ile++;}}}

   srand(time(NULL));
miejscestrzal = rand()%ile;
ile =0;

for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       if (tablicawar [i][j]==maximum && ile<miejscestrzal){
        z1 = i;
        z2 = j;
        ile++;
       }
    }
}

       
debug(to_string(z1)+ " "+ to_string(z2));
 tablicawar [z1][z2] = -1;

   return (z1*10+z2);
}
}
    
    public:
    
    
  Bot3() {
    for (int i=0;i<10;i++){
    for (int j =0;j<10;j++){
       tablicawar [i][j]=0; // inicjalizacja tablicy wartości strzałów bota na zera
    }
}
tablicawar [1][1] = 1; // jedno z początkowych miejsc do strzału bota 
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
int dostan = bot(tablica_bot,tablicawar,do_rysowania); // otrzymane miejsca do strzału

x = dostan/10;
y = dostan%10;

if (x>=0 && y>=0 && x<10 && y<10){
if (tablica_bot [x][y]== '#'){
    do_rysowania[x][y] = 1;

    if (tablica_bot[x+1][y] != '#'&& tablica_bot[x-1][y]!= '#' && tablica_bot[x][y+1] != '#' && tablica_bot[x][y-1]!= '#'){
        if (x+1<10){do_rysowania [x+1][y] = 2; tablicawar [x+1][y] = -1;  } //dodaje tutaj zmiane tablicy wartosci
        if (x-1 >=0){do_rysowania [x-1][y] = 2; tablicawar [x-1][y] = -1;}
        if (y+1<10){do_rysowania [x][y+1] = 2; tablicawar [x][y+1] = -1;}
        if (y-1 >=0){do_rysowania [x][y-1] =2; tablicawar [x][y-1] = -1;} 
        if((x+1)<10 && (y+1)<10){do_rysowania [x+1][y+1] = 2; tablicawar [x+1][y+1] = -1;}
        if((x-1)>=0 && (y-1)>=0){do_rysowania [x-1][y-1] = 2; tablicawar [x-1][y-1] = -1;}
        if((x-1)>=0 && (y+1)<10){do_rysowania [x-1][y+1] = 2; tablicawar [x-1][y+1] = -1;}
        if((x+1)<10 && (y-1)>=0){do_rysowania [x+1][y-1] = 2; tablicawar [x+1][y-1] = -1;} //to trzeba usunąć - bot ma tego nie rysowac 
}


    else if (do_rysowania[x-1][y]==1 || do_rysowania[x][y-1]==1 || do_rysowania[x][y+1]==1 || do_rysowania[x-1][y+1] ==1){ 

            if (do_rysowania[x-1][y]==1 && x-1 >=0){
              if (do_rysowania[x-2][y]==1 && x-2 >=0){
                if (do_rysowania[x-3][y]==1 && x-3 >=0){ 
                     if (x-4 >=0){do_rysowania [x-4][y] = 2; tablicawar [x-4][y] = -1;}
                     }
                else { if (x-3 >=0){do_rysowania [x-3][y] = 2; tablicawar [x-3][y] = -1;}}
            }
             else { if (x-2 >=0){do_rysowania [x-2][y] = 2; tablicawar [x-2][y] = -1;}}
            }
        
            if (do_rysowania[x][y+1]==1 && y+1 <10){
              if (do_rysowania[x][y+2]==1 && y+2 <10){
                if (do_rysowania[x][y+3]==1 && y+3 <10){ 
                     if (y+4 <10){do_rysowania [x][y+4] = 2; tablicawar [x][y+4] = -1;}
                     }
                else { if (y+3 <10 ){do_rysowania [x][y+3] = 2; tablicawar [x][y+3] = -1;}}
            }
             else { if (y+2 <10){do_rysowania [x][y+2] = 2; tablicawar [x][y+2] = -1;}}
            }


            if (do_rysowania[x+1][y]==1 && x+1 <10){
              if (do_rysowania[x+2][y]==1 && x+2 <10){
                if (do_rysowania[x+3][y]==1 && x+3 <10){ 
                     if (x+4 <10){do_rysowania [x+4][y] = 2; tablicawar [x+4][y] = -1;}
                     }
                else { if (x+3 <10){do_rysowania [x+3][y] = 2; tablicawar [x+3][y] = -1;}}
            }
             else { if (x+2 <10){do_rysowania [x+2][y] = 2; tablicawar [x+2][y] = -1;}}
            }

        
            if (do_rysowania[x][y-1]==1 && y-1 >=0){
              if (do_rysowania[x][y-2]==1 && y-2 >=0){
                if (do_rysowania[x][y-3]==1 && y-3 >=10){ 
                     if (y-4 >=0){do_rysowania [x][y-4] = 2; tablicawar [x][y-4] = -1;}
                     }
                else { if (y-3 >=0 ){do_rysowania [x][y-3] = 2; tablicawar [x][y-3] = -1;}}
            }
             else { if (y-2 >=10){do_rysowania [x][y-2] = 2; tablicawar [x][y-2] = -1;}}
            }
     
        if((x+1)<10 && (y+1)<10){do_rysowania [x+1][y+1] = 2; tablicawar [x+1][y+1] = -1;}
        if((x-1)>=0 && (y-1)>=0){do_rysowania [x-1][y-1] = 2; tablicawar [x-1][y-1] = -1;}
        if((x-1)>=0 && (y+1)<10){do_rysowania [x-1][y+1] = 2; tablicawar [x-1][y+1] = -1;}
        if((x+1)<10 && (y-1)>=0){do_rysowania [x+1][y-1] = 2; tablicawar [x+1][y-1] = -1;} 




        if (tablicawar[x+1][y] != -1){
          if ((do_rysowania[x-2][y] == 1 && do_rysowania[x-3][y] == 1) || (do_rysowania[x-2][y] == 1 && tablica_bot[x-3][y] != '#')|| tablica_bot[x-2][y] != '#'){
            tablicawar[x+1][y] = -1;
          } }
            
         if (tablicawar[x-1][y] != -1){
          if ((do_rysowania[x+2][y] == 1 && do_rysowania[x+3][y] == 1) || (do_rysowania[x+2][y] == 1 && tablica_bot[x+3][y] != '#')|| tablica_bot[x+2][y] != '#'){
            tablicawar[x-1][y] = -1;
          } }

         if (tablicawar[x][y+1] != -1){
          if ((do_rysowania[x][y-2] == 1 && do_rysowania[x][y-3] == 1) || (do_rysowania[x][y-2] == 1 && tablica_bot[x][y-3] != '#')|| tablica_bot[x][y-2] != '#'){
            tablicawar[x][y+1] = -1;
          } }

        if (tablicawar[x][y-1] != -1){
          if ((do_rysowania[x][y+2] == 1 && do_rysowania[x][y+3] == 1) || (do_rysowania[x][y+2] == 1 && tablica_bot[x][y+3] != '#')|| tablica_bot[x][y+2] != '#'){
            tablicawar[x][y-1] = -1;
          } }

    }  //sytuacja kiedy statek jest zatopiony + rysowanie jest do usunięcia


    else {   

        if((x+1)<10 && (y+1)<10){do_rysowania [x+1][y+1] = 2; tablicawar [x+1][y+1] = -1;}
        if((x-1)>=0 && (y-1)>=0){do_rysowania [x-1][y-1] = 2; tablicawar [x-1][y-1] = -1;}
        if((x-1)>=0 && (y+1)<10){do_rysowania [x-1][y+1] = 2; tablicawar [x-1][y+1] = -1;}
        if((x+1)<10 && (y-1)>=0){do_rysowania [x+1][y-1] = 2; tablicawar [x+1][y-1] = -1;} //to trzeba usunąć - bot ma tego nie rysowac 


        if (x+1<10 && tablicawar [x+1][y]!=-1){tablicawar [x+1][y] =(tablicawar [x+1][y]+1)*2;}
        if (x-1 >=0 && tablicawar [x-1][y]!= -1){tablicawar [x-1][y] =(tablicawar [x-1][y]+1)*2;}
        if (y+1<10 && tablicawar [x][y+1]!= -1){tablicawar [x][y+1] =(tablicawar [x][y+1]+1)*2;}
        if (y-1 >=0 && tablicawar [x][y-1]!= -1){tablicawar [x][y-1] =(tablicawar [x][y-1]+1)*2;} //zwiększenie wartości pól do strzału wokół niezatopionego statku

        }




if (is1(tablica_bot,do_rysowania) ==false){
    ilosc_statkow [0] = 0;
    ilosc_statkow [1] = 0;
    ilosc_statkow [2] = 0;
    ilosc_statkow [3] = 0; //koniec gry dla bota gdy plansza jest pusta
}



return 1; // bot trafił więc powtarza turę
}


do_rysowania[x][y] = 2; 
return 0; //bot nie trafił
}

return -1; // tutaj nigdy nie dojdzie bot jeżeli kod działa prawidłowo
}
  
          
};
