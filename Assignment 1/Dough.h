/*
 * name     : Seungjae Yoo
 * email    : sjyoo@postech.ac.kr
 * date     : 2017.10.20
 */

#ifndef DOUGH_H_INCLUDED
#define DOUGH_H_INCLUDED

// headers & libraries
#include <iostream>
#include <string>

class Dough {
private :
    // basic variables
    std::string name;
    float thickness;
    int extra_cost;
    int sell_count;
    std::string comment;

    // newly defined variables
    Dough* next;

public :
    // basic set function
    void set_name(std::string _name);
    void set_thickness(float _thickness);
    void set_extracost(int _extracost);
    void inc_sellcount();
    void set_comment(std::string _comment);

    // basic get function
    std::string get_name();
    float get_thickness();
    int get_extracost();
    int get_sellcount();
    std::string get_comment();

    // newly defined function
    void set_init();
    void set_next(Dough* _next);
    Dough* get_next();
    void print_dough();
};

#endif // DOUGH_H_INCLUDED
