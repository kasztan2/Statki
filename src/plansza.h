//plik nagłówkowy do funkcji planszy i ustawiania
#pragma once
#include <bits/stdc++.h>
#include <curses.h>

#define KOLOR_MORZE 1
#define KOLOR_STATEK 2
#define KOLOR_USTAWIANIE 3

void print(int x, int y, std::string str, int kolor);
void print(int x, int y, char znak, int kolor);
void print(int x, int y, std::string str);
void print(int x, int y, char znak);
void czyscPlansze(char plansza[][10]);
void rysujPlansze(char plansza[][10]);
void inicjujKolory();
void faza_ustawiania(char plansza[][10]);