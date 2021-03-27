/*
 * name     : Seungjae Yoo
 * email    : sjyoo@postech.ac.kr
 * date     : 2017.10.20
 */

// headers & libraries
#include <iostream>
#include <string>
#include "Edge.h"

// set name
void Edge::set_name(std::string _name) {
    this->name = _name;
}

// add mousse
int Edge::add_mousse(std::string _mousse) {
    if (this->mousse_size < 3) { // when mousse is not full
        this->mousse[this->mousse_size] = _mousse;
        this->mousse_size += 1;
        return 0;
    }
    else { // when mousse is full
        return 1;
    }
}

// set extra cost
void Edge::set_extracost(int _extracost) {
    this->extra_cost = _extracost;
}

// increase sell count
void Edge::inc_sellcount() {
    this->sell_count += 1;
}

// set comment
void Edge::set_comment(std::string _comment) {
    this->comment = _comment;
}

// get name
std::string Edge::get_name() {
    return this->name;
}

// get mousse
std::string Edge::get_mousse() {
    std::string mousse_all = "";
    for (int i = 0; i < this->mousse_size; i++) {
        if (i) mousse_all = mousse_all + ","; // when not first mousse
        mousse_all = mousse_all + this->mousse[i]; // add mousse
    }
    return mousse_all;
}

// get extra cost
int Edge::get_extracost() {
    return this->extra_cost;
}

// get sell count
int Edge::get_sellcount() {
    return this->sell_count;
}

// get comment
std::string Edge::get_comment() {
    return this->comment;
}

// set sell count and mousse size
void Edge::set_init() {
    this->sell_count = 0;
    this->mousse_size = 0;
}

// set next edge
void Edge::set_next(Edge* _next) {
    this->next = _next;
}

// get next edge
Edge* Edge::get_next() {
    return this->next;
}

// print edge
void Edge::print_edge() {
    std::cout << "[이름:" << this->get_name() << "][무스:" << this->get_mousse() << "][추가비용:" << this->get_extracost() << "원][소개말:" << this->get_comment() << "]" << std::endl;
}

void Edge::clear_mousse() {
    for (int i = 0; i < this->mousse_size; i++) {
        this->mousse[i] = "";
    }
    this->mousse_size = 0;
}
