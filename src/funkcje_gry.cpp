#include <bits/stdc++.h>
#include <queue>
#include <random>
#include "plansza.h"
#include "bot1.h"
#include "menu.h"
using std::queue, std::pair, std::vector, std::cout, std::cin, std::string, std::swap;

bool poprzednie_strzaly_trafione1[10][10];
bool poprzednie_strzaly_trafione2[10][10];

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

bool poza_plansza(int y, int x){
    if(y >= 10 || y < 0 || x >= 10 || x < 0){
        return true;
    }
    return false;
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

int strzal_w_pole(int y, int x, char plansza[][10], bool poprzednie_strzaly_trafione[][10], int ilosc_statkow[4]){
    if(plansza[y][x] == '#'){
        if(plansza==plansza2)poprzednie_udane_strzaly1[y][x]=true;
        for(int i = 0; i<10; i++){
            for(int j = 0; j<10; j++){
                swap(plansza[i][j], plansza[j][i]);
            }
        }
        poprzednie_strzaly_trafione[y][x] = true;
        queue<pair<int, int>> q;
        q.push({y, x});
        bool visited[10][10];
        memset(visited, false, sizeof(visited));
        vector<pair<int, int>> statek_id;
        int licznik2 = -1;
        while(!q.empty()){
            licznik2++;
            pair<int, int> wartosc_z_kolejki = q.front();
            q.pop();
            int new_y = wartosc_z_kolejki.first;
            int new_x = wartosc_z_kolejki.second;
            visited[new_y][new_x] = true;
            int licznik = 0;
            for(auto u : kierunki){
                licznik++;
                if(!poza_plansza(new_y+u.first, new_x+u.second) && plansza[new_y+u.first][new_x+u.second] == '#' && !visited[new_y+u.first][new_x+u.second]){
                    q.push({new_y+u.first, new_x+u.second});
                    statek_id.push_back({new_y+u.first, new_x+u.second});
                }
            }
        }
        for(int i = 0; i<10; i++){
            for(int j = 0; j<10; j++){
                swap(plansza[i][j], plansza[j][i]);
            }
        }
        int ilosc = 0;
        for(auto para : statek_id){
            if(poprzednie_strzaly_trafione[para.first][para.second]){
                ilosc++;
            }
        }
        if(ilosc == statek_id.size()){
            ilosc_statkow[ilosc]-=1;
            return 2;
        }
        return 1;

    }
    else{
        if(plansza==plansza2)poprzednie_nieudane_strzaly1[y][x]=true;
        return 0;
    }
}

pair<int, int> zapytaj_o_strzal(){
    static int k, x=0, y=0;
    rysujPlanszePrzeciwnika(poprzednie_udane_strzaly1, poprzednie_nieudane_strzaly1);
    int kolor;
    if(poprzednie_udane_strzaly1[x][y])kolor=KOLOR_USTAWIANIE_NA_CZERWONYM;
    else if(poprzednie_nieudane_strzaly1[x][y])kolor=KOLOR_USTAWIANIE_NA_ZOLTYM;
    else kolor=KOLOR_USTAWIANIE_NA_NIEBIESKIM;
    attron(A_BLINK | COLOR_PAIR(kolor));
    mvaddstr(y+2, 25+2*x+1, "██");
    attroff(A_BLINK | COLOR_PAIR(kolor));
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
        else if(k==' '||k==10)//zaakceptuj
        {
            //TODO sprawdzenie, czy użytkownik nie strzela w pole, w które już strzelił
            break;
        }
        rysujPlanszePrzeciwnika(poprzednie_udane_strzaly1, poprzednie_nieudane_strzaly1);

        if(poprzednie_udane_strzaly1[x][y])kolor=KOLOR_USTAWIANIE_NA_CZERWONYM;
        else if(poprzednie_nieudane_strzaly1[x][y])kolor=KOLOR_USTAWIANIE_NA_ZOLTYM;
        else kolor=KOLOR_USTAWIANIE_NA_NIEBIESKIM;
        attron(A_BLINK | COLOR_PAIR(kolor));
        mvaddstr(y+2, 25+2*x+1, "██");
        attroff(A_BLINK | COLOR_PAIR(kolor));
    }
    print(25+2*x, y+1, "  ");
    int kolumna=x, wiersz=y;
    //print(0, 0, std::to_string(rand()));
    return {kolumna, wiersz};
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

void init_tablice(){
    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            poprzednie_strzaly_trafione1[i][j] = false;
            poprzednie_strzaly_trafione2[i][j] = false;
        }
    }
}

void start_gry(){
    init_tablice();
    int gracz_startujacy = kto_zaczyna_gre() + 1;
    //std::variant<Bot1, string> gracz2;
    //TO BE vector<std::variant<Bot1, Bot2, Bot3>> gracz2;
    //Bot1 bot1;
    //Bot2 bot2;
    //Bot3 bot3;
    //gracz2=bot1;
    Bot gracz2;

    losuj_plansze_bota(plansza2);

    //zainicjuj planszę i ją wyświetl
    czyscPlansze(plansza1);
    rysujPlansze(plansza1);

    //faza ustawiania
    faza_ustawiania(plansza1);
    rysujPlansze(plansza1);
    refresh();

    bool tura_bota = true;
    if(gracz_startujacy == 1 || 0==0){
        //cout << "Zaczynasz gre. Wpisz pole w ktore chcesz strzelic\n";
        //print(0, 0, "Zaczynasz gre");
        //sleep(3);
        tura_bota = false;
        print(0, 0, "Wybierz pole w ktore chcesz strzelić");
    }
    while(koniec_gry(ilosc_statkow1, ilosc_statkow2) == 0){
        // print(0, 12, "                 ");
        if(tura_bota){
            int wynik = gracz2.strzal(plansza1, poprzednie_strzaly_trafione1, ilosc_statkow1, rysowanie_strzalow_bota);
            if(wynik == 0){
                tura_bota = false;
            }
            rysujTrafieniaBota(rysowanie_strzalow_bota);
        }
        else{
            pair<int, int> strzal1 = zapytaj_o_strzal();
            int trafil_gracz = strzal_w_pole(strzal1.first, strzal1.second, plansza2, poprzednie_strzaly_trafione2, ilosc_statkow2);
            if(trafil_gracz == 2){
                print(0, 12, "Zatopiłeś statek!  ");
            }
            if(trafil_gracz == 1){
                print(0, 12, "Trafiles w statek! ");
            }
            if(trafil_gracz == 0){
                tura_bota = true;
                print(0, 12, "Pudło!             ");
            }
            print(0, 13, "Pozostałe statki:");
            print(0, 14, "Jednomasztowce: ");
            print(20, 14, to_string(ilosc_statkow2[0]));
            print(0, 15, "Dwumasztowce: ");
            print(20, 15, to_string(ilosc_statkow2[1]));
            print(0, 16, "Trójmasztowce: ");
            print(20, 16, to_string(ilosc_statkow2[2]));
            print(0, 17, "Czteromasztowce: ");
            print(20, 17, to_string(ilosc_statkow2[3]));
            rysujTrafieniaBota(rysowanie_strzalow_bota);
        }
    }
    int przegrany = koniec_gry(ilosc_statkow1, ilosc_statkow2);
    clear();
    if(przegrany == 1){
        print(60, 0, "Przegrałeś!");
    }
    else{
        print(60, 0, "Wygrałeś!");
    }
    print(40, 1, "Naciśnij dowolny przycisk, aby zakończyć program...");
    getch();


}
