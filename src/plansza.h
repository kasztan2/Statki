//plik nagłówkowy do funkcji planszy i ustawiania
#pragma once
#include <bits/stdc++.h>
#include <curses.h>

#define KOLOR_MORZE 1
#define KOLOR_STATEK 2
#define KOLOR_USTAWIANIE 3
#define KOLOR_TRAFIONY 4
#define KOLOR_PUDLO 5

void print(int x, int y, std::string str, int kolor);
void print(int x, int y, char znak, int kolor);
void print(int x, int y, std::string str);
void print(int x, int y, char znak);
void czyscPlansze(char plansza[][10]);
void rysujPlansze(char plansza[][10]);
void inicjujKolory();
void faza_ustawiania(char plansza[][10]);
void rysujPlanszePrzeciwnika(bool udane_strzaly[][10], bool nieudane_strzaly[][10]);
void rysujTrafieniaBota(int strzaly[][10]);