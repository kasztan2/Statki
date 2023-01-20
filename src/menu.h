#ifndef _MENU_H_
#define _MENU_H_

#include <curses.h>
#include <string>
#include <vector>
#include "plansza.h"

#define MAG_BLACK 7
#define CYAN_BLACK 8
#define BLUE_BLACK 9
#define K_ENTER 10

enum Section {
    menu,
    new_game,
    instructions,
    end
};

class Menu {
    WINDOW* _menu;
    std::vector<std::string> _menu_options = { "Nowa gra", "Instrukcje", "Wyjście" };
    std::vector<std::string> _new_game_options = { "Bot 1", "Bot 2", "Bot 3", "Wróć do menu" };
    std::vector<std::string> _instruction_options = { "Wróć do menu" };
    int _selected_option;
    int _prev_selected_option;
    Section _curr_section;

    int get_size();

public:
    Menu(int height, int width);
    ~Menu();
    void update();
    void init(const std::vector<std::string>& options);
    void init_colors();
    void clear();
    void print_menu(const std::vector<std::string>& options);
    void move_up();
    void move_down();
    void get_move();
    void select_option();
    void print_selected_option(const std::string& option, int y, int x);
    void section_exit();
    void section_return();
    void section_new_game();
    void section_instructions();
    void print_ship();
    void start();
};

#endif //_MENU_H_
