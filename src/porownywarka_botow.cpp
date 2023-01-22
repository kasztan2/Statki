#include <iostream>
#include "funkcje_gry.h"
#include "plansza.h"
#include "bot1.h"
#include "bot2.h"
#include "bot3.h"
#include "menu.h"

int zagraj_gre(Bot1 gracz1, Bot1 gracz2){ // zwraca kto wygral gre - 1 czy 2 gracz.
    bool gracz1_tura = kto_zaczyna_gre();
    char plansza1[10][10];
    char plansza2[10][10];
    bool poprzednie_strzaly_trafione1[10][10];
    bool poprzednie_strzaly_trafione2[10][10];
    bool uzupelnienie_funkcji[10][10]; // nie bede zmienial funkcji, wrzuce jakas tablice, raczej nie bedziemy rysowac jak boty graja ze soba na porownywarce
    int ilosc_statkow1[4] = {4, 3, 2, 1};
    int ilosc_statkow2[4] = {4, 3, 2, 1};
    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            poprzednie_strzaly_trafione1[i][j] = false;
            poprzednie_strzaly_trafione2[i][j] = false;
            plansza1[i][j] = ' ';
            plansza2[i][j] = ' ';
        }
    }
    losuj_plansze_bota(plansza1);
    losuj_plansze_bota(plansza2);
    while(koniec_gry(ilosc_statkow1, ilosc_statkow2) == 0){
        if(gracz1_tura){
            int wynik = gracz1.strzal(plansza1, poprzednie_strzaly_trafione1, ilosc_statkow1, uzupelnienie_funkcji);
            if(wynik == 0){
                gracz1_tura = 0;
            }
        }
        else{
            int wynik = gracz2.strzal(plansza2, poprzednie_strzaly_trafione2, ilosc_statkow2, uzupelnienie_funkcji);
            if(wynik == 0){
                gracz1_tura = 1;
            }
        }
    }
    int przegrany = koniec_gry(ilosc_statkow1, ilosc_statkow2);
    if(przegrany == 1){
        return 2;
    }
    return 1;

}
