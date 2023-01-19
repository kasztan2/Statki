//faza ustawiania
#include "plansza.h"

//sprawdź czy otoczenie pola jest wolne (statki nie mogą się stykać)
bool okOtoczeniePola(char plansza[][10], int x, int y)
{
    if(plansza[x][y]!=' ')return false;
    if(x>0)
    {
        if(y>0&&plansza[x-1][y-1]!=' ')return false;
        if(y<9&&plansza[x-1][y+1]!=' ')return false;
        if(plansza[x-1][y]!=' ')return false;
    }
    if(x<9)
    {
        if(y>0&&plansza[x+1][y-1]!=' ')return false;
        if(y<9&&plansza[x+1][y+1]!=' ')return false;
        if(plansza[x+1][y]!=' ')return false;
    }
    if(y>0&&plansza[x][y-1]!=' ')return false;
    if(y<9&&plansza[x][y+1]!=' ')return false;

    return true;
}

bool ustawStatek(char plansza[][10], int x, int y, bool kierunek, int rozmiar)
{
    //sprawdzanie czy statek może być ustawiony w tej pozycji
    if(kierunek==0)
    {
        for(int i=x; i<x+rozmiar; ++i)
        {
            if(!okOtoczeniePola(plansza, i, y))return false;
        }
    }
    else
    {
        for(int i=y; i<y+rozmiar; ++i)
        {
            if(!okOtoczeniePola(plansza, x, i))return false;
        }
    }


    //umieszczanie statku na planszy
    if(kierunek==0)
    {
        for(int i=x; i<x+rozmiar; ++i)
        {
            plansza[i][y]='#';
        }
    }
    else
    {
        for(int i=y; i<y+rozmiar; ++i)
        {
            plansza[x][i]='#';
        }
    }
    return true;
}

void faza_ustawiania(char plansza[][10])
{
    print(25, 7, "Oznaczenia:");
    print(25, 8, "  ", KOLOR_MORZE);
    print(27, 8, " puste pole");
    print(25, 9, "██", KOLOR_STATEK);
    print(27, 9, " ustawiony statek");
    print(25, 10, "██", KOLOR_USTAWIANIE);
    print(27, 10, " statek w trakcie ustawiania");

    std::vector<int> statki={1, 1, 1, 1, 2, 2, 2, 3, 3, 4};
    while(!statki.empty())
    {
        int rozmiar=statki.back();
        statki.pop_back();
        bool kierunek=0;// 0 - poziomo, 1 - pionowo
        int x=0, y=0;//koordynaty gdzie lewy górny róg to (0, 0)
        int k;

        //wyświetl statek do ustawienia, na początku w defaultowej pozycji
        for(int i=x; i<x+rozmiar; ++i)print(2*i, y+1, "██", KOLOR_USTAWIANIE);
        
        while(1)
        {
            k=getch();
            if(k=='A')//do góry
            {
                if(y>0)--y;
            }
            else if(k=='B')//do dołu
            {
                if(kierunek==0&&y<9)++y;
                else if(kierunek==1&&y<10-rozmiar)++y;
            }
            else if(k=='D')//w lewo
            {
                if(x>0)--x;
            }
            else if(k=='C')//w prawo
            {
                if(kierunek==0&&x<10-rozmiar)++x;
                else if(kierunek==1&&x<9)++x;
            }
            else if(k=='r')//obróć statek
            {
                if((kierunek==0&&y<=10-rozmiar)||(kierunek==1&&x<=10-rozmiar))kierunek=!kierunek;
            }
            else if(k==' ')//zaakceptuj pozycję statku i spróbuj go ustawić
            {
                if(ustawStatek(plansza, x, y, kierunek, rozmiar))
                {
                    //jeśli udało się ustawić statek to rysuj planszę i przejdź do ustawiania następnego statku
                    rysujPlansze(plansza);
                    break;
                }
            }

            rysujPlansze(plansza);

            //rysowanie statku do ustawienia
            if(kierunek==0)
            {
                for(int i=x; i<x+rozmiar; ++i)
                {
                    print(2*i, y+1, "██", KOLOR_USTAWIANIE);
                }
            }
            else
            {
                for(int i=y; i<y+rozmiar; ++i)
                {
                    print(2*x, i+1, "██", KOLOR_USTAWIANIE);
                }
            }
        }
    }
    //czyszczenie oznaczeń
    for(int i=7; i<=11; ++i)print(25, i, "                                 ");
}
