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
        if(ilosc_statkow1[i] > 0){
            gracz1 = false;
        }
        if(ilosc_statkow2[i] > 0){
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
        return 2;

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

bool mozna_ustawic(bool zajete[][10], int y, int x, int wielkosc, bool pion){
    if(pion){
        // chcemy sprawdzic caly prostokat 3x(wielkosc+2) dookola statku czy nie stoja dookola tych pol inne statki (lacznie z rogami wiec +2), jesli mamy sytuacje ze statek stoi przy skraju mapy to nie chcemy wyjsc poza mape
        for(int i = 0; i<wielkosc; i++){
            if(zajete[y+i][x]){
                return false;
            }
        }
        return true;
    }
    else{
        // chcemy sprawdzic caly prostokat 3x(wielkosc+2) dookola statku czy nie stoja dookola tych pol inne statki (lacznie z rogami wiec +2), jesli mamy sytuacje ze statek stoi przy skraju mapy to nie chcemy wyjsc poza mape
        for(int i = 0; i<wielkosc; i++){
            if(zajete[y][x+i]){
                return false;
            }
        }
        return true;
    }
}

void losuj_plansze_bota(char plansza2[][10]){
    srand(time(NULL));
    bool zajete[10][10];
    memset(zajete, false, sizeof(zajete));
    vector<int> wielkosci = {1, 1, 1, 1, 2, 2, 2, 3, 3, 4};
    while(!wielkosci.empty()){
        int wielkosc_statku = wielkosci.back();
        wielkosci.pop_back();
        bool pion = (rand()%2); // 0 poziom 1 pion
        if(pion){
            int y, x;
            do{
                y = rand()%(10-wielkosc_statku);
                x = rand()%(10-wielkosc_statku);
            }while(!mozna_ustawic(zajete, y, x, wielkosc_statku, pion));
            int starti = -1, endi = 1;
            int startj = -1, endj = wielkosc_statku;
            if(y == 9){
                endj--;
            }
            else if(y == 0){
                startj++;
            }
            if(x == 9){
                endi--;
            }
            else if(x == 0){
                starti++;
            }
            for(int i = 0; i<wielkosc_statku; i++){
                zajete[y+i][x] = true;
                plansza2[y+i][x] = '#';
            }
            for(int i = starti; i<=endi; i++){
                for(int j = startj; j<=endj; j++){
                    zajete[y+j][x+i] = true;
                }
            }

        }
        else{
            int y, x;
            do{
                y = rand()%(10-wielkosc_statku);
                x = rand()%(10-wielkosc_statku);
            }while(!mozna_ustawic(zajete, y, x, wielkosc_statku, pion));
            for(int i = 0; i<wielkosc_statku; i++){
                zajete[y][x+i] = true;
                plansza2[y][x+i] = '#';
            }
            int starti = -1, endi = 1;
            int startj = -1, endj = wielkosc_statku;
            if(y == 9){
                endi--;
            }
            else if(y == 0){
                starti++;
            }
            if(x == 9){
                endj--;
            }
            else if(x == 0){
                startj++;
            }
            for(int i = 0; i<wielkosc_statku; i++){
                zajete[y][x+i] = true;
                plansza2[y][x+i] = '#';
            }
            for(int i = starti; i<=endi; i++){
                for(int j = startj; j<=endj; j++){
                    zajete[y+i][x+j] = true;
                }
            }
        }
    }
}

void start_gry(){
    int gracz_startujacy = kto_zaczyna_gre() + 1;
    Bot1 gracz2;
    losuj_plansze_bota(plansza2);
    //TODO: rozpoczecie fazy ustawiania w tym miejscu
    if(gracz_startujacy == 1){
        cout << "Zaczynasz gre. Wpisz pole w ktore chcesz strzelic\n";
    }
    while(koniec_gry(ilosc_statkow1, ilosc_statkow2) == 0){
        if(gracz_startujacy == 1){
            pair<int, int> strzal1 = zapytaj_o_strzal();
            strzal_w_pole(strzal1.first, strzal1.second, plansza2, poprzednie_strzaly2, ilosc_statkow2);
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