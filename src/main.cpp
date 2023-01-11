#include "plansza.h"
#include "menu.h"

char planszaU[10][10];

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
    menu.init();

    //zainicjuj planszę i ją wyświetl
    czyscPlansze(planszaU);
    rysujPlansze(planszaU);

    //faza ustawiania
    faza_ustawiania(planszaU);
    rysujPlansze(planszaU);
    refresh();
    sleep(2);//! do usunięcia, ~placeholder

    //wróć kursorze i cała reszto!
    echo();
    nocbreak();
    curs_set(1);
    system("stty sane");
    printf("\n");
}