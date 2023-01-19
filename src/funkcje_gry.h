#pragma once
#include <bits/stdc++.h>
#include <random>

bool kto_zaczyna_gre(); // 1 - gracz, 0 - bot
int koniec_gry(int ilosc_statkow[4]); // 0 - nie // 1 tak gracz1 przegral // 2 tak gracz2 przegral
int strzal_w_pole(int kolumna, int wiersz, char plansza[][10], bool poprzednie_strzaly[][10], int ilosc_statkow[4]); // 0 - pudło, 1 - trafienie, 2 - zatopienie
void wczytaj_plansze_gracza();
std::pair<int, int> zapytaj_o_strzal();
void start_gry();

