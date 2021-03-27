/*
 * name     : Seungjae Yoo
 * email    : sjyoo@postech.ac.kr
 * date     : 2017.10.20
 */

#ifndef DOUGHLIST_H_INCLUDED
#define DOUGHLIST_H_INCLUDED

// headers & libraries
#include <iostream>
#include <string>
#include "Dough.h"

class DoughList{
private :
    // basic variables
    Dough* head;
    int size;

public :
    // basic functions
    void add(Dough* _dough);
    int del(std::string _name);
    Dough* pick(std::string _name);
    void show_all_menu();
    void show_most_popular();
    void search_by_thick(float _low, float _high);

    // newly defined functions
    void set_init();
    int get_size();
};

#endif // DOUGHLIST_H_INCLUDED
