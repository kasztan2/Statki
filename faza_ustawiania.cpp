#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
// #TODO:
// przeniesienie do klasy
// mechanizm ustawiania
// mechanizm usuwania
// mechanizm cofania - wrzucanie na stos ostatnich komend i zamienianie ich z "ustaw" na "usun" i z "usun" na "ustaw"

//STRUKTURY DANYCH
std::stack<std::pair<std::string, std::vector<std::string>>> ostatnie_operacje;
char mapa[10][10];
std::pair<int, int> kierunki[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int statki_pozostale[4] = {4, 3, 2, 1};

//FUNKCJE
bool pola_obok(std::string pole1, std::string pole2){
    if(abs( int(pole1[0]) - int(pole2[0])) == 1 && pole1[1] == pole2[1]){
        return true;
    }
    else if(abs(pole1[1] - pole2[1]) == 1 && pole1[0] == pole2[0]){
        return true;
    }
    return false;
}

bool poza_plansza(int y, int x){
    if(y >= 10 || y < 0 || x >= 10 || x < 10){
        return true;
    }
    return false;
}

std::vector<std::string> id_miejsc_wejscie(){
    std::string pomoc_komenda;
    std::getline(std::cin, pomoc_komenda);
    std::vector<std::string> id_miejsc;
    std::string ostatnie_id = "";
    for(int i = 1; i<pomoc_komenda.length(); i++){ // od 1 bo na miejscu 1 jest spacja
        if(pomoc_komenda[i] == ' '){
            id_miejsc.push_back(ostatnie_id);
            ostatnie_id = "";
        }
        else{
            ostatnie_id += pomoc_komenda[i];
        }
    }
    id_miejsc.push_back(ostatnie_id);
    std::sort(id_miejsc.begin(), id_miejsc.end());
    return id_miejsc;
}

void wypisz_plansze(char mapa[10][10]){
    std::cout<<("  ");
    for(int i = 0; i<10; i++){
        std::cout << char(65+i);
    }
    std::cout << "\n";
    for(int i = 0; i<10; i++){
        if(i == 9){ // 10 ma 2 cyfry zamiast jednej przez co mapa troche sie rozjezdza
            std::cout << i+1;
        }
        else{
            std::cout << i+1 << " ";
        }
        for(int j = 0; j<10; j++){
            std::cout << mapa[i][j];
        }
        std::cout<<"\n";
    }
}

void komenda_pozostale_statki(int *statki_pozostale){
    std::cout<<"Do narysowania pozostało " << statki_pozostale[0] <<  " jednomasztowców," << statki_pozostale[1] << " dwumasztowców, " <<  statki_pozostale[2] << " trójmasztowców, " <<  statki_pozostale[3] << " czteromasztowców\n";
}

void komenda_help(){
    std::cout << "Wpisz komendę 'ustaw {id}' aby wstawić w miejsce {id} część statku. Dla przykładu 'ustaw C5'.\n";
    std::cout << "Wpisz komendę 'usun {id}' aby wstawić w miejsce {id} część statku. Dla przykładu 'usun A7'.\n";
    std::cout << "Wpisz komendę 'pozostale' aby dostać informację o pozostałej ilości statków do ustawienia.\n";
}

void komenda_ustaw(std::vector<std::string> & id_miejsc){
    std::vector<std::vector<int>> zmiany_obecne(10, std::vector<int>(10, 0));
    std::vector<std::pair<int, int>> zmien_na_X(id_miejsc.size());
    std::vector<std::pair<int, int>> zmian_na_Kratke(id_miejsc.size()); //dwie tablice aby zapamietac ktore miejsca zmienic, czemu? bo ktos moze wpisac A7 A8 B8 i mamy jakis statek L
    //!WAZNE: moze byc jakis problem ze statkami o bokach L, to jest do naprawy
    //!WAZNE: Zrobic osobna funkcje ktora sprawdza czy wejscie jest prawidlowe tj.:
    // Brak statków typu L
    // Brak statków długości większej niz 4 
    // Ilość statków o długości np. 1 nie będzie za duża po obecnym wejściu. Czyli np. mamy już zapisane 3 statki o długości 1 i teraz użytkownik chce dodać 2 nowe statki o długości 1 - będzie ich wtedy 5 a to za dużo.
    // Jakieś statki nie zostaną przedłużone. (Zabronić czy nie?)
    for(auto miejsce : id_miejsc){ //sprawdzanie czy mozna ustawic w kazde miejsce ktore zostaly podane
        int kolumna = int(miejsce[0]) - 65; //litera A to 0 kolumna, B to 1 itd..
        int wiersz = int(miejsce[1]) - 49; //cyfra 1 to 0 wiersz, 2 to 1 wiersz itd..
        if(mapa[kolumna][wiersz] == '#' || mapa[kolumna][wiersz] == 'X'){
            std::cout << "W miejscu " << miejsce << " nie mozna umieścić statku ponieważ jest zajęte lub jakiś statek stoi obok. Wpisz poprawne miejsce!\n";
            zmiany_obecne.clear();
            zmiany_obecne.shrink_to_fit();
            zmien_na_X.clear();
            zmien_na_X.shrink_to_fit();
            zmian_na_Kratke.clear();
            zmian_na_Kratke.shrink_to_fit();
            return;
        }
        zmien_na_X.push_back({kolumna, wiersz});
        zmiany_obecne[kolumna][wiersz] = 1;
        for(auto para : kierunki){
            if(!poza_plansza(kolumna+para.first,wiersz+para.second)){
                zmian_na_Kratke.push_back({kolumna+para.first, wiersz+para.second});
            }
        }
    }
    for(auto para : zmien_na_X){
        mapa[para.first][para.second] = 'X';
    }
    for(auto para : zmian_na_Kratke){
        mapa[para.first][para.second] = '#';
    }
    //bfs sprawdzajacy wielkosci statkow na podstawie tablicy zmiany_obecne. 
    std::vector<std::vector<bool>> odwiedzone(10, std::vector<bool>(10, false));
    std::vector<int> rozmiary_statkow;
    for(auto para : zmien_na_X){
        if(odwiedzone[para.first][para.second]){
            continue;
        }
        int wielkosc = 0;
        std::queue<std::pair<int, int>> punkty;
        punkty.push({para.first, para.second});
        while(!punkty.empty()){
            std::pair<int, int> obecny_punkt = punkty.front();
            punkty.pop();
            odwiedzone[obecny_punkt.first][obecny_punkt.second] = true;
            wielkosc++;
            for(auto para : kierunki){
                int newfirst = obecny_punkt.first+para.first;
                int newsecond = obecny_punkt.second+para.second;
                if(!poza_plansza(newfirst, newsecond) && mapa[newfirst][newsecond] == 'X'){
                    punkty.push({newfirst, newsecond});
                }
            }
        }
        rozmiary_statkow.push_back(wielkosc);
    }
    // --------------------
    for(int i : rozmiary_statkow){
        std::cout << i << "\n";
        statki_pozostale[i-1]--;
    }
    odwiedzone.clear();
    odwiedzone.shrink_to_fit();
    rozmiary_statkow.clear();
    rozmiary_statkow.shrink_to_fit();
    zmien_na_X.clear();
    zmien_na_X.shrink_to_fit();
    zmian_na_Kratke.clear();
    zmian_na_Kratke.shrink_to_fit();
    zmiany_obecne.clear();
    zmiany_obecne.shrink_to_fit();

}

void komenda_usun(){
    int pass;
}
// Niech X oznacza miejsce w ktorym stoi statek
// . to puste miejsce
// # to miejsca w ktorych nie mozna postawic statku
void faza_ustawiania(){
    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            mapa[i][j] = '.';
        }
    }
    std::cout << "Zaczyna się część gry w której ustawiasz swoje statki na planszy!\n";
    komenda_pozostale_statki(statki_pozostale);
    wypisz_plansze(mapa);
    komenda_help();
    while(statki_pozostale[3]+statki_pozostale[2]+statki_pozostale[1]+statki_pozostale[0] > 0){
        std::string komenda;
        std::cin >> komenda;
        if(komenda == "help"){
            komenda_help();
        }
        else if(komenda == "ustaw"){
            std::vector<std::string> wejscie = id_miejsc_wejscie();
            //uwzglednic przypadek gdy ktos wpisuje dwa statki w jednej komendzie np. A4 i F8, najlepiej rozdzielic to na dwie wywolania funkcji komenda_ustaw()
            komenda_ustaw(wejscie);
        }
        else if(komenda == "usun"){
            std::string id;
            std::cin >> id;
            std::cout << komenda << " " << id << "\n";
            komenda_usun();
        }
        else if(komenda == "pozostale"){
            komenda_pozostale_statki(statki_pozostale);
        }
        else{
            std::cout << "Nierozpoznana komenda. Wpisz 'help', aby uzyskać pomoc.\n";
        }

    }
}

int main(){
    faza_ustawiania();
}
