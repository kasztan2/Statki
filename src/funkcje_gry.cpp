#include <bits/stdc++.h>
#include <queue>
#include <random>
#include "plansza.h"
#include "bot1.h"
#include "menu.h"
using std::queue, std::pair, std::vector, std::cout, std::cin, std::string, std::swap;

bool poprzednie_strzaly1[10][10];
bool poprzednie_strzaly2[10][10];

//pod rysowanie
bool poprzednie_nieudane_strzaly1[10][10];
bool poprzednie_udane_strzaly1[10][10];
int rysowanie_strzalow_bota[10][10];

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
    //if(kolumna>60)kolumna-=0;
    print(0, 0, "strzal_w_pole");
    if(plansza[kolumna][wiersz] == '#'){
        print(0, 0, "trafienie");
        if(plansza==plansza2)poprzednie_udane_strzaly1[kolumna][wiersz]=true;
        print(0, 0, "def");
        queue<pair<int, int>> q;
        q.push({kolumna, wiersz});
        bool visited[10][10];
        memset(visited, 0, sizeof(visited));
        int byl_jakis_obok_trafiony = 0;
        while(!q.empty()){
            pair<int, int> para = q.front();
            visited[para.first][para.second] = true;
            q.pop();
            int kol = para.first;
            int wier = para.second;
            for(auto u : kierunki){
                if(plansza[kol+u.first][wier+u.second] == '#' && poprzednie_strzaly[kol+u.first][wier+u.second] && !visited[kol+u.first][wier+u.second]){
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
        print(0, 0, "pudlo");
        if(plansza==plansza2)poprzednie_nieudane_strzaly1[kolumna][wiersz]=true;
        return 0;
    }
}

pair<int, int> zapytaj_o_strzal(){
    int k, x=0, y=0;
    rysujPlanszePrzeciwnika(poprzednie_udane_strzaly1, poprzednie_nieudane_strzaly1);
    print(25+2*x, y+1, "██", KOLOR_USTAWIANIE);
    while(1)
    {
        k=getch();
        if(k>='A'&&k<='D')print(25+2*x, y+1, "  ");
        if(k=='A')//do góry
        {
            if(y>0)--y;
        }
        else if(k=='B')//do dołu
        {
            if(y<9)++y;
        }
        else if(k=='D')//w lewo
        {
            if(x>0)--x;
        }
        else if(k=='C')//w prawo
        {
            if(x<9)++x;
        }
        else if(k==' ')//zaakceptuj
        {
            //TODO sprawdzenie, czy użytkownik nie strzela w pole, w które już strzelił
            break;
        }
        rysujPlanszePrzeciwnika(poprzednie_udane_strzaly1, poprzednie_nieudane_strzaly1);
        print(25+2*x, y+1, "██", KOLOR_USTAWIANIE);
    }
    print(25+2*x, y+1, "  ");
    int kolumna=x, wiersz=y;
    //print(0, 0, std::to_string(rand()));
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
    //std::variant<Bot1, string> gracz2;
    //TO BE vector<std::variant<Bot1, Bot2, Bot3>> gracz2;
    //Bot1 bot1;
    //Bot2 bot2;
    //Bot3 bot3;
    //gracz2=bot1;
    Bot1 gracz2;

    losuj_plansze_bota(plansza2);

    //zainicjuj planszę i ją wyświetl
    czyscPlansze(plansza1);
    rysujPlansze(plansza1);

    //faza ustawiania
    faza_ustawiania(plansza1);
    rysujPlansze(plansza1);
    refresh();

    if(gracz_startujacy == 1 || 0==0){
        //cout << "Zaczynasz gre. Wpisz pole w ktore chcesz strzelic\n";
        //print(0, 0, "Zaczynasz gre");
        //sleep(3);
        print(0, 0, "Wybierz pole w ktore chcesz strzelić");
    }
    while(koniec_gry(ilosc_statkow1, ilosc_statkow2) == 0){
        if(gracz_startujacy == 1){
            
            pair<int, int> strzal1 = zapytaj_o_strzal();
            strzal_w_pole(strzal1.first, strzal1.second, plansza2, poprzednie_strzaly2, ilosc_statkow2);
            gracz2.strzal(plansza1, poprzednie_strzaly1, ilosc_statkow1, rysowanie_strzalow_bota);
            rysujTrafieniaBota(rysowanie_strzalow_bota);
        }
        else
        {
            gracz2.strzal(plansza1, poprzednie_strzaly1, ilosc_statkow1, rysowanie_strzalow_bota);
            rysujTrafieniaBota(rysowanie_strzalow_bota);
            pair<int, int> strzal1 = zapytaj_o_strzal();
            strzal_w_pole(strzal1.first, strzal1.second, plansza2, poprzednie_strzaly2, ilosc_statkow2);
        }
    }
    print(0, 0, "Gra zakończona!");
    int przegrany = koniec_gry(ilosc_statkow1, ilosc_statkow2);
    if(przegrany == 1){
        //cout << "Przegrałeś!\n";
        print(0, 0, "Przegrałeś!");
    }
    else{
        //cout << "Wygrałeś!\n";
        print(0, 0, "Wygrałeś!");
    }


}