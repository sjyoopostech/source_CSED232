/*
 * name     : Seungjae Yoo
 * email    : sjyoo@postech.ac.kr
 * date     : 2017.10.20
 */

#ifndef TOPPING_H_INCLUDED
#define TOPPING_H_INCLUDED

// headers & libraries
#include <iostream>
#include <string>

class Topping {
private :
    // basic variables
    std::string name;
    std::string ingredient[10];
    int price;
    int sell_count;
    std::string comment;

    // newly defined variables
    Topping* next;
    int ingredient_size;

public :
    // basic set function
    void set_name(std::string _name);
    int add_ingredient(std::string _ingredient);
    void set_price(int _price);
    void inc_sellcount();
    void set_comment(std::string _comment);

    // basic get function
    std::string get_name();
    std::string get_ingredient();
    int get_price();
    int get_sellcount();
    std::string get_comment();

    // newly defined function
    void set_init();
    void set_next(Topping* _next);
    Topping* get_next();
    void print_topping();
    void clear_ingredient();
};

#endif // TOPPING_H_INCLUDED
