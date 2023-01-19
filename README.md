# Gra w statki

## Instalacja
Zainstaluj `ncurses` oraz `coreutils`. Na Debianie/Ubuntu:
```bash
sudo apt install libncurses5-dev libncursesw5-dev coreutils
```  
[Instrukcje dla innych dystrybucji](https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora)

MacOS:
Potrzebny jest gcc (aby #include <bits/stdc++.h> działał). Bazowo na macOS jest zainstalowany Clang, wiec trzeba doinstalowac gcc za pomocą komendy 
```brew install gcc
```
Nastepnie w pliku Makefile zmień g++ na "/opt/homebrew/bin/g++-12"   

Następnie zbuduj program komendą
```bash
make
```
  
Teraz odpal plik `statki`.
