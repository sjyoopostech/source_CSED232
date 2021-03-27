/*
 * name     : Seungjae Yoo
 * email    : sjyoo@postech.ac.kr
 * date     : 2017.10.20
 */

// headers & libraries
#include <iostream>
#include <string>
#include "Topping.h"
#include "ToppingList.h"

// add topping
void ToppingList::add(Topping* _topping) {
    if (this->size == 0) { // when no topping here
        this->head = _topping;
    }
    else { // when topping exist
        Topping* now = this->head;
        for (int i = 1; i < this->size; i++) { // move to next topping
            now = now->get_next();
        }
        now->set_next(_topping); // connect new topping
    }
    _topping->set_next(NULL); // set new topping next
    this->size += 1; // increase size
}

// delete topping
int ToppingList::del(std::string _name) {
    int success = 0;
    if (this->size == 0) return 0; // when no topping here
    Topping* now = this->head; // moving node
    Topping* delnode; // delete node
    if (now->get_name() == _name) { // when head is delete node
        // disconnecting
        this->head = now->get_next();
        success = 1;
        now->set_next(NULL);
        this->size -= 1;
    }
    while (now->get_next() != NULL && !success) { // when head is not delete node
        if (now->get_next()->get_name() == _name) { // when now next is delete node
            // disconnecting
            delnode = now->get_next();
            now->set_next(delnode->get_next());
            delnode->set_next(NULL);
            success = 1;
            this->size -= 1;
            break;
        }
        now = now->get_next(); // go to next node
        if (now == NULL) break; // when reach end
    }
    return success;
}

// pick topping
Topping* ToppingList::pick(std::string _name) {
    Topping* now = this->head;
    while (now != NULL) {
        if (now->get_name() == _name) { // when name of now
            return now;
        }
        now = now->get_next(); // go to next node
    }
    return NULL;
}

// show all topping
void ToppingList::show_all_menu() {
    Topping* now = this->head;
    for (int i = 0; i < this->size; i++) {
        now->print_topping(); // print topping
        now = now->get_next(); // go to next node
    }
}

// show most popular topping
void ToppingList::show_most_popular() {
    Topping* now = this->head;
    Topping* pop = this->head;
    if (now == NULL) { // when there is no menu
        std::cout << "메뉴가 없습니다." << std::endl;
    }
    else {
        for (int i = 0; i < this->size; i++) {
            if (now->get_sellcount() > pop->get_sellcount()) pop = now; // comparing sell count
            now = now->get_next(); // go to next node
        }
        pop->print_topping(); // print topping
    }
}

// search by ingredient
void ToppingList::search_by_ingred(std::string _ingredient) {
    int cnt = 0; // counting topping
    Topping* now = this->head;
    for (int i = 0; i < this->size; i++) {
        if (now->get_ingredient().find(_ingredient) != std::string::npos) { // when ingredient is exist
            now->print_topping(); // print topping
            cnt++;
        }
        now = now->get_next(); // go to next node
    }
    std::cout << "이상 총 " << cnt << "개가 검색되었습니다." << std::endl;
}

// search by price
void ToppingList::search_by_price(int _low, int _high) {
    int cnt = 0; // counting topping
    Topping* now = this->head;
    for (int i = 0; i < this->size; i++) {
        if (now->get_price() <= _high && now->get_price() >= _low) { // when price is in range
            now->print_topping(); // print topping
            cnt++;
        }
        now = now->get_next(); // go to next node
    }
    std::cout << "이상 총 " << cnt << "개가 검색되었습니다." << std::endl;
}

// set size and head
void ToppingList::set_init() {
    this->size = 0;
    this->head = NULL;
}

// get size
int ToppingList::get_size() {
    return this->size;
}
