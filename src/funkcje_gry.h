#pragma once
#include <bits/stdc++.h>
#include <random>

bool kto_zaczyna_gre(); // 1 - gracz, 0 - bot
bool poza_plansza(int y, int x);
int koniec_gry(int ilosc_statkow1[4], int ilosc_statkow2[4]); // 0 - nie // 1 tak gracz1 przegral // 2 tak gracz2 przegral
int strzal_w_pole(int kolumna, int wiersz, char plansza[][10], bool poprzednie_strzaly[][10], int ilosc_statkow[4]); // 0 - pudło, 1 - trafienie, 2 - zatopienie
void losuj_plansze_gracza(char plansza[][10]);
void wczytaj_plansze_gracza();
std::pair<int, int> zapytaj_o_strzal();
void init_tablice();
void start_gry();
void obrysuj_zatoplony_statek(int kolumna, int wiersz, char plansza[][10]);
void losuj_plansze_bota(char plansza2[][10]);

