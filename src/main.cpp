#include "plansza.h"
#include "menu.h"
#include "funkcje_gry.h"

int main()
{
    //*MAGIA*, czyli konfiguracja biblioteki ncurses (wyłączenie kursora, kolorki itp.)
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    inicjujKolory();
    curs_set(0);

    //Menu menu(30, 120);
    //menu.start();
    
    start_gry();

    //wróć kursorze i cała reszto!
    echo();
    nocbreak();
    curs_set(1);
    system("stty sane");
    printf("\n");
}