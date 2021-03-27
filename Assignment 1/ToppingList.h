/*
 * name     : Seungjae Yoo
 * email    : sjyoo@postech.ac.kr
 * date     : 2017.10.20
 */

#ifndef TOPPINGLIST_H_INCLUDED
#define TOPPINGLIST_H_INCLUDED

// headers & libraries
#include <iostream>
#include <string>
#include "Topping.h"

class ToppingList{
private :
    // basic variables
    Topping* head;
    int size;

public :
    // basic functions
    void add(Topping* _topping);
    int del(std::string _name);
    Topping* pick(std::string _name);
    void show_all_menu();
    void show_most_popular();
    void search_by_ingred(std::string _ingredient);
    void search_by_price(int _low, int _high);

    // newly defined functions
    void set_init();
    int get_size();
};

#endif // TOPPINGLIST_H_INCLUDED
