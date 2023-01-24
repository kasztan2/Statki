#include "plansza.h"
#include "menu.h"
#include "funkcje_gry.h"

int wybor_bota;

int main()
{
    //*MAGIA*, czyli konfiguracja biblioteki ncurses (wyłączenie kursora, kolorki itp.)
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    inicjujKolory();
    curs_set(0);

    Menu menu(30, 120);
    menu.start();
    
    start_gry();

    sprzatanie_przy_wyjsciu();
}