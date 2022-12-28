#include <iostream>
#include <string>
#include <queue>
#include <random>
using std::string, std::cout, std::queue, std::to_string, std::pair;

class Bot1{
    private:
    char statek = '#';
    char puste_pole = ' ';
    bool strzelic[10][10];
    bool trafiony[10][10];
    queue<pair<int, int>> kolejka_strzalow;
    pair<int, int> kierunki[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool poza_plansza(int y, int x){
        if(y >= 10 || y < 0 || x >= 10 || x < 0){
            return true;
        }
        return false;
    }
    string wspolrzedneNaString(int kolumna, int wiersz){
        return char(kolumna) + to_string(wiersz);
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
    string strzal(){
        if(!kolejka_strzalow.empty()){
            pair<int, int> para_z_kolejki = kolejka_strzalow.front();
            string miejsce_strzalu = wspolrzedneNaString(para_z_kolejki.first, para_z_kolejki.second);
            kolejka_strzalow.pop();
            strzelic[para_z_kolejki.first][para_z_kolejki.second] = false;
            return miejsce_strzalu;
        }
        int kolumna, wiersz;
        do{
            kolumna = rand()%10 + 65;
            wiersz = rand()%10;
        }while(!strzelic[wiersz][kolumna]);
        string pole_strzal = wspolrzedneNaString(kolumna, wiersz);
        strzelic[wiersz][kolumna] = false;
        return pole_strzal;
    }
    void decyzja(int kolumna, int wiersz){ //funkcja decydujaca co robic na podstawie czy bot trafil czy nie
        bool trafienie = false;
        bool zatopienie = false;
        if(trafienie){
            bool czy_wczesniej_trafione_obok = false;
            for(auto para : kierunki){
                int x = kolumna-65+para.second;
                int y = wiersz+para.first;
                // zalozmy ze y = 3 x = 4
                // kierunek: -1 0
                // czyli na y=2 x = 4 bylo trafienie
                // chcemy dodac y=1 x = 4 i y=4 x = 4, bo nie wiemy jak dalej idzie statek
                // jesli kierunek 1 0 to chcemy dodac to samo, wiec mamy y+para.first i y - 2*para.first, jesli w planszy
                // mozemy smiało dodac do obu poniewaz jedna ze zmiennych w kierunku jest 0 wiec nie wplynie na druga zmienna, a zalatwimy tym oba przypadki
                if(!poza_plansza(y, x) && trafiony[y][x]){
                    czy_wczesniej_trafione_obok = true;
                    if(!poza_plansza(y+para.first, x+para.second)){
                        kolejka_strzalow.push({y+para.first, x+para.second});
                    }
                    if(!poza_plansza(y-2*para.first, x-2*para.second)){
                        kolejka_strzalow.push({y-2*para.first, x-2*para.second});
                    }
                }
            }
            if(!czy_wczesniej_trafione_obok){
                for(auto para : kierunki){
                    if(!poza_plansza(wiersz+para.second, kolumna-65+para.first)){
                        kolejka_strzalow.push({wiersz+para.second, kolumna-65+para.first});
                    }
                }
            }
        }
        // jak nie trafimy to nie robimy nic
        if(zatopienie){
            //TODO: bfs przechodzimy po trafieniach i dodajemy wszystkie wspolrzedne dookola trafien jako false w strzelic, aby bot nigdy wiecej do nich nie strzelil.
            int pass;
        }

    }
};


int main(){
    Bot1 test;
}