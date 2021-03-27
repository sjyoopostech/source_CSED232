/*
 * name     : Seungjae Yoo
 * email    : sjyoo@postech.ac.kr
 * date     : 2017.10.20
 */

#ifndef EDGELIST_H_INCLUDED
#define EDGELIST_H_INCLUDED

// headers & libraries
#include <iostream>
#include <string>
#include "Edge.h"

class EdgeList{
private :
    // basic variables
    Edge* head;
    int size;

public :
    // basic functions
    void add(Edge* _edge);
    int del(std::string _name);
    Edge* pick(std::string _name);
    void show_all_menu();
    void show_most_popular();
    void search_by_mousse(std::string _mousse);

    // newly defined functions
    void set_init();
    int get_size();
};

#endif // EDGELIST_H_INCLUDED
