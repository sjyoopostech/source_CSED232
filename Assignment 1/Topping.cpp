/*
 * name     : Seungjae Yoo
 * email    : sjyoo@postech.ac.kr
 * date     : 2017.10.20
 */

// headers & libraries
#include <iostream>
#include <string>
#include "Topping.h"

// set name
void Topping::set_name(std::string _name) {
    this->name = _name;
}

// add ingredient
int Topping::add_ingredient(std::string _ingredient) {
    if (this->ingredient_size < 10) { // when ingredient is not full
        this->ingredient[this->ingredient_size] = _ingredient;
        this->ingredient_size += 1;
        return 0;
    }
    else { // when ingredient is full
        return 1;
    }
}

// set price
void Topping::set_price(int _price) {
    this->price = _price;
}

// increase sell count
void Topping::inc_sellcount() {
    this->sell_count += 1;
}

// set comment
void Topping::set_comment(std::string _comment) {
    this->comment = _comment;
}

// get name
std::string Topping::get_name() {
    return this->name;
}

// get ingredient
std::string Topping::get_ingredient() {
    std::string ingredient_all = "";
    for (int i = 0; i < this->ingredient_size; i++) {
        if (i) ingredient_all = ingredient_all + ","; // when not first ingredient
        ingredient_all = ingredient_all + this->ingredient[i]; // add ingredient
    }
    return ingredient_all;
}

// get price
int Topping::get_price() {
    return this->price;
}

// get sell count
int Topping::get_sellcount() {
    return this->sell_count;
}

// get comment
std::string Topping::get_comment() {
    return this->comment;
}

// set sell count and ingredient size
void Topping::set_init() {
    this->sell_count = 0;
    this->ingredient_size = 0;
}

// set next topping
void Topping::set_next(Topping* _next) {
    this->next = _next;
}

// get next topping
Topping* Topping::get_next() {
    return this->next;
}

// print topping
void Topping::print_topping() {
    std::cout << "[이름:" << this->get_name() << "][재료:" << this->get_ingredient() << "][가격:" << this->get_price() << "원][소개말:" << this->get_comment() << "]" << std::endl;
}

void Topping::clear_ingredient() {
    for (int i = 0; i < this->ingredient_size; i++) {
        this->ingredient[i] = "";
    }
    this->ingredient_size = 0;
}
