#include "menu.h"
#include <fstream>
#include <istream>

Menu::Menu(int height, int width)
{
    _menu = newwin(height, width, LINES / 2 - height / 2, COLS / 2 - width / 2);
    _selected_option = 0;
    _new_game = false;
    _exit = false;
    start_color();
    init_colors();
    keypad(_menu, true);
}

Menu::~Menu()
{
    delwin(_menu);
}

void Menu::update()
{
    refresh();
    wrefresh(_menu);
}

void Menu::clear()
{
    wclear(_menu);
    update();
}

void Menu::init()
{
    print_menu();
    print_ship();
    update();

    while (true) {
        get_move();
        if (_exit || _new_game) {
            clear();
            break;
        }

        clear();
        print_menu();
        print_ship();
    }
}

void Menu::print_menu()
{
    int y = _menu->_maxy / 2 + _options.size();
    int half_col = 1 + _menu->_maxx / 2;

    for (int i = 0; i < _options.size(); ++i) {
        int x = half_col - _options[i].length() / 2;
        if (_selected_option == i) {
            print_selected_option(_options[i], y, x);
        } else {
            wattron(_menu, A_DIM);
            mvwprintw(_menu, y, x, "%s", _options[i].c_str());
            wattroff(_menu, A_DIM);
        }
        y += 2;
    }
    update();
}

void Menu::move_up()
{
    --_selected_option;
    if (_selected_option <= -1) {
        _selected_option = _options.size() - 1;
    }
}

void Menu::move_down()
{
    ++_selected_option;
    if (_selected_option >= _options.size()) {
        _selected_option = 0;
    }
}

void Menu::init_colors()
{
    init_pair(MAG_BLACK, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CYAN_BLACK, COLOR_CYAN, COLOR_BLACK);
    init_pair(BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
}

void Menu::get_move()
{
    switch (wgetch(_menu)) {
    case KEY_UP:
    case 'w':
        move_up();
        break;

    case KEY_DOWN:
    case 's':
        move_down();
        break;

    case K_ENTER:
    case ' ':
        select_option();
        break;

    default:
        break;
    }
}

void Menu::select_option()
{
    switch (_selected_option) {
    case 0:
        section_new_game();
        break;

    case 1:
        section_options();
        break;

    case 2:
        section_instructions();
        break;

    default:
        section_exit();
        break;
    }
}

void Menu::print_selected_option(const std::string& option, int y, int x)
{
    wattron(_menu, A_BLINK | COLOR_PAIR(MAG_BLACK));
    mvwprintw(_menu, y, x - 3, "->");
    wattroff(_menu, A_BLINK | COLOR_PAIR(MAG_BLACK));

    mvwprintw(_menu, y, x, "%s", option.c_str());

    wattron(_menu, A_BLINK | COLOR_PAIR(MAG_BLACK));
    mvwprintw(_menu, y, _menu->_curx + 1, "<-");
    wattroff(_menu, A_BLINK | COLOR_PAIR(MAG_BLACK));
}

// TODO
void Menu::section_return()
{
    clear();
    init();
}

void Menu::section_exit()
{
    _exit = true;
}

// TODO
void Menu::section_new_game()
{
    _new_game = true;
    clear();
}

// TODO
void Menu::section_instructions()
{
    clear();
}

// TODO
void Menu::section_options()
{
    clear();
}

void Menu::print_ship()
{
    std::string line;
    std::ifstream file("statki_napis.txt");

    int y = _menu->_maxy / 8;
    if (file.is_open()) {
        wattron(_menu, COLOR_PAIR(BLUE_BLACK));
        while (getline(file, line)) {
            mvwprintw(_menu, y, _menu->_maxx / 2 - line.length() / 2, "%s", line.c_str());
            ++y;
        }
        file.close();
        wattroff(_menu, COLOR_PAIR(BLUE_BLACK));
    }
}
