#include <bits/stdc++.h>
#include <queue>
#include <random>
#include "plansza.h"
#include "bot1.cpp"
using std::queue, std::pair, std::vector, std::cout, std::cin, std::string, std::swap;

bool poprzednie_strzaly1[10][10];
bool poprzednie_strzaly2[10][10];
char plansza1[10][10];
char plansza2[10][10];
int ilosc_statkow1[4] = {4, 3, 2, 1};
int ilosc_statkow2[4] = {4, 3, 2, 1};
vector<pair<int, int>> kierunki = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
bool kto_zaczyna_gre(){
    srand(time(NULL));
    int liczba_losowa = rand();
    if(liczba_losowa%2==1){
        return 1;
    }
    return 0;
}

int koniec_gry(int ilosc_statkow1[4], int ilosc_statkow2[4]){ 
    bool gracz1 = true; 
    bool gracz2 = true;
    for(int i = 0; i<4; i++){
        if(ilosc_statkow1[0] > 0){
            gracz1 = false;
        }
        if(ilosc_statkow2[0] > 0){
            gracz2 = false;
        }
    }
    if(gracz1){
        return 1;
    }
    if(gracz2){
        return 2;
    }
    return 0;
    
}

int strzal_w_pole(int kolumna, int wiersz, char plansza[][10], bool poprzednie_strzaly[][10], int ilosc_statkow[4]){
    if(plansza[kolumna][wiersz] == '#'){
        queue<pair<int, int>> q;
        q.push({kolumna, wiersz});
        bool visited[10][10];
        memset(visited, 0, sizeof(visited));
        int byl_jakis_obok_trafiony = 0;
        while(!q.empty()){
            pair<int, int> para = q.front();
            q.pop();
            int kol = para.first;
            int wier = para.second;
            for(auto u : kierunki){
                if(plansza[kol+u.first][wier+u.second] == '#' && poprzednie_strzaly[kol+u.first][wier+u.second]){
                    q.push({kol+u.first, wier+u.second});
                    byl_jakis_obok_trafiony++;
                }
                if(plansza[kol+u.first][wier+u.second] == '#' && !poprzednie_strzaly[kol+u.first][wier+u.second]){
                    poprzednie_strzaly[kolumna][wiersz] = true;
                    return 1; // jest trafienie, a obok stoi dalej jakis statek ktory nie zostal zatopiony
                }
            }
        }
        ilosc_statkow[byl_jakis_obok_trafiony+1]--;
        poprzednie_strzaly[kolumna][wiersz] = true;

    }
    else{
        return 0;
    }
}

pair<int, int> zapytaj_o_strzal(){
    
    string pole;
    do{
        cin >> pole;
    }while((int(pole[0]) > 90 || int(pole[0] > 57) && int(pole[0]) < 65 || int(pole[0]) < 48) || (int(pole[1]) > 90 || int(pole[1] > 57) && int(pole[1]) < 65 || int(pole[1]) < 48));
    
    if( int(pole[1]) >= 65 && int(pole[1]) <= 90 ){
        swap(pole[0], pole[1]);
    }
    int kolumna = int(pole[0])-65;
    int wiersz = int(pole[1])-48;
    return {kolumna, wiersz};
}

void wczytaj_plansze_gracza(){
    int pass; // TODO aby wczytac plansze ktora ustawi gracz do zmiennej plansza1
}

void start_gry(){
    int gracz_startujacy = kto_zaczyna_gre() + 1;
    Bot1 gracz2;
    if(gracz_startujacy == 1){
        cout << "Zaczynasz gre. Wpisz pole w ktore chcesz strzelic\n";
    }
    while(koniec_gry(ilosc_statkow1, ilosc_statkow2) == 0){
        if(gracz_startujacy == 1){
            pair<int, int> strzal1 = zapytaj_o_strzal();
            // TODO: 
            // 1. wylosowanie planszy bota i ustawienie jej jako plansza2
            gracz2.strzal(plansza1, poprzednie_strzaly1, ilosc_statkow1); 
        }
    }
    int przegrany = koniec_gry(ilosc_statkow1, ilosc_statkow2);
    if(przegrany == 1){
        cout << "Przegrałeś!\n";
    }
    else{
        cout << "Wygrałeś!\n";
    }


}