# Gra w statki

## Instalacja
### Linux
Zainstaluj potrzebne pakiety.
#### Debian/Ubuntu[^1]
```bash
sudo apt install libncurses5-dev libncursesw5-dev coreutils make
```
[^1]: sprawdzone na `Ubuntu 22.10`
#### Fedora
```bash
sudo dnf install ncurses-devel
```

---

Następnie zbuduj program komendą
```bash
make
```


### MacOS[^2]
Potrzebny jest `gcc` (aby `#include <bits/stdc++.h>` działał). Bazowo na macOS jest zainstalowany Clang, więc trzeba doinstalować `gcc` za pomocą komendy 
```
brew install gcc
```
Dodatkowo potrzebne jest zainstalowanie biblioteki ncurses. 
```
brew install ncurses
```

Następnie zbuduj program komendą
```bash
make
```
[^2]: sprawdzone na `macOS 13.1`

## Uruchamianie

Uruchom plik `statki`.
**Uwaga:** okno terminala musi być wymiarów co najmniej `120x30`.
