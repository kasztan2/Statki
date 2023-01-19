UNAME := $(shell uname)

all:

ifeq ($(UNAME), Linux)
	g++ src/main.cpp src/ustawianie.cpp src/plansza.cpp src/funkcje_gry.cpp src/menu.h src/menu.cpp -lncursesw -o statki
endif
ifeq ($(UNAME), Darwin)
	/opt/homebrew/bin/g++-12 src/main.cpp src/ustawianie.cpp src/plansza.cpp src/funkcje_gry.cpp src/menu.h src/menu.cpp -lncursesw -o statki
endif
