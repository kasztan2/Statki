#include <iostream>
#include <string>
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

void komenda_ustaw(){
    int pass;
}

void komenda_usun(){
    int pass;
}
// Niech X oznacza miejsce w ktorym stoi statek
// . to puste miejsce
// # to miejsca w ktorych nie mozna postawic statku
void faza_ustawiania(){
    char mapa[10][10];
    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            mapa[i][j] = '.';
        }
    }
    std::cout << "Zaczyna się część gry w której ustawiasz swoje statki na planszy!\n";
    int statki_pozostale[4] = {4, 3, 2, 1};
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
            std::string id;
            std::cin >> id;
            std::cout << komenda << " " << id << "\n";
            komenda_ustaw();
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
