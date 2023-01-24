UNAME := $(shell uname)

all:

ifeq ($(UNAME), Linux)
	g++ -std=c++17 src/main.cpp src/ustawianie.cpp src/plansza.cpp src/funkcje_gry.cpp src/menu.cpp src/porownywarka_botow.cpp -lncursesw -o statki
endif
ifeq ($(UNAME), Darwin)
	/opt/homebrew/bin/g++-12 -std=c++17 src/main.cpp src/ustawianie.cpp src/plansza.cpp src/funkcje_gry.cpp src/menu.cpp src/porownywarka_botow.cpp -lncurses -o statki
endif
