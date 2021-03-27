/*
 * name     : Seungjae Yoo
 * email    : sjyoo@postech.ac.kr
 * date     : 2017.10.20
 */

// headers & libraries
#include <iostream>
#include <string>
#include "Dough.h"

// set name
void Dough::set_name(std::string _name) {
    this->name = _name;
}

// set thickness
void Dough::set_thickness(float _thickness) {
    this->thickness = _thickness;
}

// set extra cost
void Dough::set_extracost(int _extracost) {
    this->extra_cost = _extracost;
}

// increase sell count
void Dough::inc_sellcount() {
    this->sell_count += 1;
}

// set comment
void Dough::set_comment(std::string _comment) {
    this->comment = _comment;
}

// get name
std::string Dough::get_name() {
    return this->name;
}

// get thickness
float Dough::get_thickness() {
    return this->thickness;
}

// get extra cost
int Dough::get_extracost() {
    return this->extra_cost;
}

// get sell count
int Dough::get_sellcount() {
    return this->sell_count;
}

// get comment
std::string Dough::get_comment() {
    return this->comment;
}

// set sell count
void Dough::set_init() {
    this->sell_count = 0;
}

// set next dough
void Dough::set_next(Dough* _next) {
    this->next = _next;
}

// get next dough
Dough* Dough::get_next() {
    return this->next;
}

// print dough
void Dough::print_dough() {
    std::cout << "[이름:" << this->get_name() << "][두께:" << this->get_thickness() << "mm][추가비용:" << this->get_extracost() << "원][소개말:" << this->get_comment() << "]" << std::endl;
}
