/*
 * name     : Seungjae Yoo
 * email    : sjyoo@postech.ac.kr
 * date     : 2017.10.20
 */

// headers & libraries
#include <iostream>
#include <string>
#include "Dough.h"
#include "DoughList.h"

// add dough
void DoughList::add(Dough* _dough) {
    if (this->size == 0) { // when no dough here
        this->head = _dough;
    }
    else { // when dough exist
        Dough* now = this->head;
        for (int i = 1; i < this->size; i++) { // move to next dough
            now = now->get_next();
        }
        now->set_next(_dough); // connect new dough
    }
    _dough->set_next(NULL); // set new dough next
    this->size += 1; // increase size
}

// delete dough
int DoughList::del(std::string _name) {
    int success = 0;
    if (this->size == 0) return 0; // when no dough here
    Dough* now = this->head; // moving node
    Dough* delnode; // delete node
    if (now->get_name() == _name) { // when head is delete node
        // disconnecting
        this->head = now->get_next();
        now->set_next(NULL);
        success = 1;
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

// pick dough
Dough* DoughList::pick(std::string _name) {
    Dough* now = this->head;
    while (now != NULL) {
        if (now->get_name() == _name) { // when name of now
            return now;
        }
        now = now->get_next(); // go to next node
    }
    return NULL;
}

// show all dough
void DoughList::show_all_menu() {
    Dough* now = this->head;
    for (int i = 0; i < this->size; i++) {
        now->print_dough(); // print dough
        now = now->get_next(); // go to next node
    }
}

// show most popular dough
void DoughList::show_most_popular() {
    Dough* now = this->head;
    Dough* pop = this->head;
    if (now == NULL) { // when there is no menu
        std::cout << "메뉴가 없습니다." << std::endl;
    }
    else {
        for (int i = 0; i < this->size; i++) {
            if (now->get_sellcount() > pop->get_sellcount()) pop = now; // comparing sell count
            now = now->get_next(); // go to next node
        }
        pop->print_dough(); // print dough
    }
}

// search by thickness
void DoughList::search_by_thick(float _low, float _high) {
    int cnt = 0; // counting thickness
    Dough* now = this->head;
    for (int i = 0; i < this->size; i++) {
        if (now->get_thickness() <= _high && now->get_thickness() >= _low) { // when thickness is in range
            now->print_dough(); // print dough
            cnt++;
        }
        now = now->get_next(); // go to next node
    }
    std::cout << "이상 총 " << cnt << "개가 검색되었습니다." << std::endl;
}

// set size and head
void DoughList::set_init() {
    this->size = 0;
    this->head = NULL;
}

// get size
int DoughList::get_size() {
    return this->size;
}
