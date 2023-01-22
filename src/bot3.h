#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <random>
#include "funkcje_gry.h"
#include "plansza.h"
using std::string, std::cout, std::deque, std::to_string, std::pair, std::vector, std::queue;

class Bot1{
    private:
    char statek = '#';
    char puste_pole = ' ';
    bool moge_strzelic[10][10];
    bool trafiony[10][10];
    vector<pair<int, int>> pola_do_strzalow;
    deque<pair<int, int>> kolejka_strzalow;
    pair<int, int> kierunki[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    pair<int, int> kierunki8[8] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
    bool poza_plansza(int y, int x){
        if(y >= 10 || y < 0 || x >= 10 || x < 0){
            return true;
        }
        return false;
    }
    void decyzja(int wiersz, int kolumna, char plansza[][10], bool poprzednie_strzaly[][10], int ilosc_statkow[4], int trafienia_wczesniejsze_do_rysowania[][10]){ //funkcja decydujaca co robic na podstawie czy bot trafil czy nie
        moge_strzelic[wiersz][kolumna] = false;
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
            trafiony[wiersz][kolumna] = true;
            // bool czy_wczesniej_trafione_obok = false;
            for(auto para : kierunki){
                int x = kolumna+para.second;
                int y = wiersz+para.first;
                if(!poza_plansza(y, x)){
                    kolejka_strzalow.push_front({y, x});
                }
            }
                //     czy_wczesniej_trafione_obok = true;
                //     if(!poza_plansza(y-2*para.first, x-2*para.second) && moge_strzelic[y-2*para.first][x-2*para.second]){
                //         kolejka_strzalow.push_front({y-2*para.first, x-2*para.second}); //nie musimy rozszerzać w drugą stronę, bo mamy na pewno tamten punkt dodany przez punkt trafiony obok
                //     }
                    //.....
                    //.TX#.
                    //.....
                    // for(auto para2 : kierunki){
                    //     if(para.first != 0){
                    //         if(para2.first == 0){ //naszym celem jest usuniecie statkow ktore stworza L (skoro byl trafiony np. punkt pod nami, to na pewno nie chcemy moge_strzelic w punkt ktory jest po prawej i lewej od tego pod nami, bo wtedy statek by mial ksztalt L). wiec jesli para.first != 0 to znaczy ze poszlo y w gore o 1 lub dol, wiec nasza para2.first musi byc rowna 0 zeby nie isc y gora dol tylko x.
                    //         // jesli dodamy tylko moge_strzelic = false, to przy funkcji strzal() wyjmie nam z kolejki ten punkt jesli jest falszywy (1szy if w funkcji strzal())
                    //             moge_strzelic[y][x+para2.second] = false;
                    //             moge_strzelic[y][x-para2.second] = false;
                    //             moge_strzelic[wiersz][kolumna+para2.second] = false; //zaznaczmy od razu kolo obecnego trafienia
                    //             moge_strzelic[wiersz][kolumna-para2.second] = false;
                    //         }       
                    //     }
                    //     else{
                    //         if(para2.first != 0){
                    //             moge_strzelic[y+para2.first][x] = false;
                    //             moge_strzelic[y-para2.first][x] = false;
                    //             moge_strzelic[wiersz+para2.first][kolumna] = false; //zaznaczmy od razu kolo obecnego trafienia
                    //             moge_strzelic[wiersz-para2.first][kolumna] = false;
                    //         }
                    //     }
                    // }
                    // break; //wiemy ze punkt np nad nami byl juz trafiony, wiec jedyny punkt ktory musimy dodac to ten pod nami ktory juz dodalismy wiec mozemy przerwac petle
            //     }
            // }
            // if(!czy_wczesniej_trafione_obok){ //jesli w nic dookola nie trafilismy i teraz trafilismy to statek moze kontynuoowac w dowolna strone
            //     for(auto para : kierunki){
            //         if(!poza_plansza(wiersz+para.second, kolumna+para.first)){
            //             kolejka_strzalow.push_front({wiersz+para.second, kolumna+para.first});
            //         }
            //     }
            // }
        }
        // jak nie trafimy to nie robimy nic
        // if(zatopienie){
        //     trafiony[wiersz][kolumna] = true;
        //     //bfs przechodzimy po trafieniach i dodajemy wszystkie wspolrzedne dookola trafien jako false w moge_strzelic, aby bot nigdy wiecej do nich nie strzelil.
        //     queue<pair<int, int>> bfs;
        //     bfs.push({wiersz, kolumna});
        //     bool visited[10][10];
        //     for(int i = 0; i<10; i++){
        //         for(int j = 0; j<10; j++){
        //             visited[i][j] = false;
        //         }
        //     }
        //     vector<pair<int, int>> statek_id;
        //     while(!bfs.empty()){
        //         int y = bfs.front().first;
        //         int x = bfs.front().second;
        //         statek_id.push_back({y, x});
        //         bfs.pop();
        //         moge_strzelic[y][x] = false;
        //         if(visited[y][x])continue;
        //         visited[y][x] = true;
        //         for(auto para : kierunki8){
        //             if(poza_plansza(y+para.first, x+para.second)){
        //                 continue;
        //             }
        //             if(trafiony[y+para.first][x+para.second] && !visited[y+para.first][x+para.second]){
        //                 bfs.push({y+para.first, x+para.second});
        //             }
        //         }
        //     }
        //     for(pair<int, int> para : statek_id){
        //         int y = para.first;
        //         int x = para.second;
        //         int i = 0;
        //         for(auto p : kierunki8){
        //             if(!poza_plansza(y+p.first, x+p.second)){
        //                 moge_strzelic[y+p.first][x+p.second] = false;
        //                 i++;
        //             }
        //         }
        //     }
        // }
    }
    public: 
    Bot1(){
        srand(time(NULL));
        for(int i = 0; i<10; i++){
            for(int j = 0; j<10; j++){
                trafiony[i][j] = false;
                moge_strzelic[i][j] = true;
                pair<int, int> para = {i, j};
                pola_do_strzalow.push_back(para);
            }
        }
        std::random_shuffle(pola_do_strzalow.begin(), pola_do_strzalow.end());
        while(!pola_do_strzalow.empty()){
            kolejka_strzalow.push_back(pola_do_strzalow.back());
            pola_do_strzalow.pop_back();
        }
        pola_do_strzalow.shrink_to_fit();
    }
    void strzal(char plansza[][10], bool poprzednie_strzaly[][10], int ilosc_statkow[4], int trafienia_wczesniejsze_do_rysowania[][10]){
        while(!kolejka_strzalow.empty() && !moge_strzelic[kolejka_strzalow.front().first][kolejka_strzalow.front().second]){
            kolejka_strzalow.pop_front();
        }
        if(!kolejka_strzalow.empty()){
            pair<int, int> para_z_kolejki = kolejka_strzalow.front();
            kolejka_strzalow.pop_front();
            moge_strzelic[para_z_kolejki.first][para_z_kolejki.second] = false;
            decyzja(para_z_kolejki.first, para_z_kolejki.second, plansza, poprzednie_strzaly, ilosc_statkow, trafienia_wczesniejsze_do_rysowania);
            return;
        }
        //nigdy nie powinien dojsc do tego miejsca, bo to bedzie znaczyc ze kolejka jest pusta, czyli strzelil w kazde mozliwe pole, wiec gra powinna byc juz zakonczona.
        cout << "blad\n";
        return;
    }
};