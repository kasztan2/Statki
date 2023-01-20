//funkcje dotyczące planszy
#include <bits/stdc++.h>
#include <curses.h>
#include "plansza.h"

void print(int x, int y, std::string str, int kolor=0)
{
    ++x;++y;
    const char *c=str.c_str();
    attron(COLOR_PAIR(kolor));
    mvaddstr(y, x, c);
    attroff(COLOR_PAIR(kolor));
}

void print(int x, int y, char znak, int kolor=0)
{
    ++x;++y;
    attron(COLOR_PAIR(kolor));
    mvaddch(y, x, znak);
    attroff(COLOR_PAIR(kolor));
}

void print(int x, int y, std::string str)
{
    print(x, y, str, 0);
}

void print(int x, int y, char znak)
{
    print(x, y, znak, 0);
}

void czyscPlansze(char plansza[][10])
{
    for(int i=0; i<10; ++i)
    {
        for(int j=0; j<10; ++j)plansza[i][j]=' ';
    }
}

void rysujPlansze(char plansza[][10])
{
    for(int i=0; i<10; ++i)
    {
        for(int j=0; j<10; ++j)
        {
            if(plansza[i][j]==' ')
            {
                print(2*i, j+1, "  ", KOLOR_MORZE);
            }
            else if(plansza[i][j]=='#')
            {
                print(2*i, j+1, "██", KOLOR_STATEK);
            }
        }
    }
}

void rysujPlanszePrzeciwnika(bool udane_strzaly[][10], bool nieudane_strzaly[][10])
{
    for(int i=0; i<10; ++i)
    {
        for(int j=0; j<10; ++j)
        {
            if(udane_strzaly[i][j])
            {
                print(25+2*i, j+1, "██", KOLOR_TRAFIONY);
            }
            else if(nieudane_strzaly[i][j])
            {
                print(25+2*i, j+1, "██", KOLOR_PUDLO);
            }
            else
            {
                print(25+2*i, j+1, "  ", KOLOR_MORZE);
            }
        }
    }
}

void rysujTrafieniaBota(int strzaly[][10])
{
    for(int i=0; i<10; ++i)
    {
        for(int j=0; j<10; ++j)
        {
            if(strzaly[i][j]==1)
            {
                print(2*i, j+1, "██", KOLOR_TRAFIONY);
            }
            else if(strzaly[i][j]==2)
            {
                print(2*i, j+1, "██", KOLOR_PUDLO);
            }
            else
            {
                //print(2*i, j+1, "██", KOLOR_STATEK);
            }
        }
    }
}

void sprzatanie_przy_wyjsciu()
{
    //wróć kursorze i cała reszto!
    echo();
    nocbreak();
    curs_set(1);
    system("stty sane");
    printf("\n");
}

void inicjujKolory()
{
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(KOLOR_MORZE, COLOR_BLACK, COLOR_BLUE);
    init_pair(KOLOR_STATEK, COLOR_GREEN, COLOR_BLACK);
    init_pair(KOLOR_USTAWIANIE, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(KOLOR_TRAFIONY, COLOR_RED, COLOR_RED);
    init_pair(KOLOR_PUDLO, COLOR_YELLOW, COLOR_YELLOW);
}


//! TEMP
void debug(std::string s)
{
    print(0, 0, s, 0);
    refresh();
}
//! KONIEC TEMP