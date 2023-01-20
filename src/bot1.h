#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <random>
#include "funkcje_gry.h"
#include "plansza.h"
using std::string, std::cout, std::queue, std::to_string, std::pair;

class Bot1{
    private:
    char statek = '#';
    char puste_pole = ' ';
    bool strzelic[10][10];
    bool trafiony[10][10];
    queue<pair<int, int>> kolejka_strzalow;
    pair<int, int> kierunki[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    pair<int, int> kierunki8[8] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
    bool poza_plansza(int y, int x){
        if(y >= 10 || y < 0 || x >= 10 || x < 0){
            return true;
        }
        return false;
    }
    string wspolrzedneNaString(int kolumna, int wiersz){
        return to_string(kolumna) + to_string(wiersz);
    }
    void decyzja(int kolumna, int wiersz, char plansza[][10], bool poprzednie_strzaly[][10], int ilosc_statkow[4], int trafienia_wczesniejsze_do_rysowania[][10]){ //funkcja decydujaca co robic na podstawie czy bot trafil czy nie
        print(0, 15, "           "+std::to_string(kolumna)+", "+std::to_string(wiersz)+"     ");
        refresh();
        bool trafienie = false; 
        bool zatopienie = false;
        int werdykt = strzal_w_pole(kolumna, wiersz, plansza, poprzednie_strzaly, ilosc_statkow);
        if(werdykt == 1){
            trafienia_wczesniejsze_do_rysowania[kolumna][wiersz]=1;
            trafienie = true;
        }
        else if(werdykt == 2){
            trafienia_wczesniejsze_do_rysowania[kolumna][wiersz]=1;
            zatopienie = true;
        }
        else trafienia_wczesniejsze_do_rysowania[kolumna][wiersz]=2;
        // zalozmy ze mamy czesc takiej planszy:
        // ...#...
        // ...#...
        // ...#...
        // niech kolumna i wiersz wskazuja na hash srodkowy i zalozmy ze w hash najwyzej juz trafilismy w jakims strzale wczesniej
        // sprawdzmy wiec najpierw czy dookola [kolumna][wiersz] jest jakis punkt ktory byl trafiony
        // jesli byl trafiony (jest to u nas punkt nad nami), to do kolejki chcemy dodac tylko punkt pod nami, bo punkt nad nami jest juz trafiony, a punkty na lewo i prawo na pewno nie beda miec statku, bo mialby wtedy ksztalt L 
        if(trafienie){
            trafiony[kolumna][wiersz] = true;
            bool czy_wczesniej_trafione_obok = false;
            for(auto para : kierunki){
                int x = kolumna+para.second;
                int y = wiersz+para.first;
                if(!poza_plansza(y, x) && trafiony[y][x]){
                    czy_wczesniej_trafione_obok = true;
                    if(!poza_plansza(y-2*para.first, x-2*para.second) && strzelic[y-2*para.first][x-2*para.second]){
                        kolejka_strzalow.push({y-2*para.first, x-2*para.second}); //nie musimy rozszerzać w drugą stronę, bo mamy na pewno tamten punkt dodany przez punkt trafiony obok
                    }
                    for(auto para2 : kierunki){
                        if(para.first != 0){
                            if(para2.first == 0){ //naszym celem jest usuniecie statkow ktore stworza L (skoro byl trafiony np. punkt pod nami, to na pewno nie chcemy strzelic w punkt ktory jest po prawej i lewej od tego pod nami, bo wtedy statek by mial ksztalt L). wiec jesli para.first != 0 to znaczy ze poszlo y w gore o 1 lub dol, wiec nasza para2.first musi byc rowna 0 zeby nie isc y gora dol tylko x.
                            // jesli dodamy tylko strzelic = false, to przy funkcji strzal() wyjmie nam z kolejki ten punkt jesli jest falszywy (1szy if w funkcji strzal())
                                strzelic[y][x+para2.second] = false;
                                strzelic[wiersz][kolumna+para2.second] = false; //zaznaczmy od razu kolo obecnego trafienia
                            }       
                        }
                        else{
                            if(para2.first != 0){
                                strzelic[y+para2.first][x] = false;
                                strzelic[wiersz+para2.first][kolumna] = false; //zaznaczmy od razu kolo obecnego trafienia
                            }
                        }
                    }
                    break; //wiemy ze punkt np nad nami byl juz trafiony, wiec jedyny punkt ktory musimy dodac to ten pod nami ktory juz dodalismy wiec mozemy przerwac petle
                }
            }
            if(!czy_wczesniej_trafione_obok){ //jesli w nic dookola nie trafilismy i teraz trafilismy to statek moze kontynuoowac w dowolna strone
                for(auto para : kierunki){
                    if(!poza_plansza(wiersz+para.second, kolumna+para.first)){
                        kolejka_strzalow.push({wiersz+para.second, kolumna+para.first});
                    }
                }
            }
        }
        // jak nie trafimy to nie robimy nic
        if(zatopienie){
            //bfs przechodzimy po trafieniach i dodajemy wszystkie wspolrzedne dookola trafien jako false w strzelic, aby bot nigdy wiecej do nich nie strzelil.
            queue<pair<int, int>> bfs;
            bfs.push({kolumna, wiersz});
            bool visited[10][10];
            for(int i = 0; i<10; i++){
                for(int j = 0; j<10; j++){
                    visited[i][j] = false;
                }
            }
            while(!bfs.empty()){
                int y = bfs.front().first;
                int x = bfs.front().second;
                bfs.pop();
                if(visited[y][x])continue;
                visited[y][x] = true;
                for(auto para : kierunki8){
                    if(poza_plansza(y+para.first, x+para.second)){
                        continue;
                    }
                    strzelic[y+para.first][x+para.second] = false;
                    if(trafiony[y+para.first][x+para.second] && !visited[y+para.first][x+para.first]){
                        bfs.push({y+para.first, x+para.second});
                    }
                }
            }
        }

    }
    public: 
    Bot1(){
        srand(time(NULL));
        for(int i = 0; i<10; i++){
            for(int j = 0; j<10; j++){
                strzelic[i][j] = true;
            }
        }
    }
    void strzal(char plansza[][10], bool poprzednie_strzaly[][10], int ilosc_statkow[4], int trafienia_wczesniejsze_do_rysowania[][10]){
        while(!kolejka_strzalow.empty()&&!strzelic[kolejka_strzalow.front().first][kolejka_strzalow.front().second]){
            kolejka_strzalow.pop();
        }
        if(!kolejka_strzalow.empty()){
            pair<int, int> para_z_kolejki = kolejka_strzalow.front();
            string miejsce_strzalu = wspolrzedneNaString(para_z_kolejki.first, para_z_kolejki.second);
            kolejka_strzalow.pop();
            strzelic[para_z_kolejki.first][para_z_kolejki.second] = false;
            decyzja(para_z_kolejki.first, para_z_kolejki.second, plansza, poprzednie_strzaly, ilosc_statkow, trafienia_wczesniejsze_do_rysowania);
            return;
        }
        int kolumna, wiersz;
        do{
            kolumna = rand()%10;
            wiersz = rand()%10;
            debug(to_string(kolumna));//? wizualizacja nieskończonej pętli
        }while(!strzelic[wiersz][kolumna]);//! TU JEST BŁĄD, leci w nieskończoność ten while
        strzelic[wiersz][kolumna] = false;
        decyzja(kolumna, wiersz, plansza, poprzednie_strzaly, ilosc_statkow, trafienia_wczesniejsze_do_rysowania);
        return;
    }
};