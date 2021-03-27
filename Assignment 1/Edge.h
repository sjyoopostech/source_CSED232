/*
 * name     : Seungjae Yoo
 * email    : sjyoo@postech.ac.kr
 * date     : 2017.10.20
 */

#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

// headers & libraries
#include <iostream>
#include <string>

class Edge {
private :
    // basic variables
    std::string name;
    std::string mousse[3];
    int extra_cost;
    int sell_count;
    std::string comment;

    // newly defined variables
    Edge* next;
    int mousse_size;

public :
    // basic set function
    void set_name(std::string _name);
    int add_mousse(std::string _mousse);
    void set_extracost(int _extracost);
    void inc_sellcount();
    void set_comment(std::string _comment);

    // basic get function
    std::string get_name();
    std::string get_mousse();
    int get_extracost();
    int get_sellcount();
    std::string get_comment();

    // newly defined function
    void set_init();
    void set_next(Edge* _next);
    Edge* get_next();
    void print_edge();
    void clear_mousse();
};

#endif // EDGE_H_INCLUDED
