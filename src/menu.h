#ifndef _MENU_H_
#define _MENU_H_

#include <curses.h>
#include <string>
#include <vector>

#define MAG_BLACK 4
#define CYAN_BLACK 5
#define BLUE_BLACK 6
#define K_ENTER 10

class Menu {
    WINDOW* _menu;
    std::vector<std::string> _options = { "Nowa gra", "Opcje", "Instrukcje", "Wyjscie" };
    int _selected_option;
    bool _exit;
    bool _new_game;

public:
    Menu(int height, int width);
    ~Menu();
    void update();
    void init();
    void init_colors();
    void clear();
    void print_menu();
    void move_up();
    void move_down();
    void get_move();
    void select_option();
    void print_selected_option(const std::string& option, int y, int x);
    void section_exit();
    void section_return();
    void section_options();
    void section_new_game();
    void section_instructions();
    void print_ship();
};

#endif //_MENU_H_
