/*
 * name     : Seungjae Yoo
 * email    : sjyoo@postech.ac.kr
 * date     : 2017.10.20
 */

// headers & libraries
#include <iostream>
#include <string>
#include "Edge.h"
#include "EdgeList.h"

// add edge
void EdgeList::add(Edge* _edge) {
    if (this->size == 0) { // when no edge here
        this->head = _edge;
    }
    else { // when edge exist
        Edge* now = this->head;
        for (int i = 1; i < this->size; i++) { // move to next edge
            now = now->get_next();
        }
        now->set_next(_edge); // connect new edge
    }
    _edge->set_next(NULL); // set new edge next
    this->size += 1; // increase size
}

// delete edge
int EdgeList::del(std::string _name) {
    int success = 0;
    if (this->size == 0) return 0; // when no edge here
    Edge* now = this->head; // moving node
    Edge* delnode; // delete node
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

// pick edge
Edge* EdgeList::pick(std::string _name) {
    Edge* now = this->head;
    while (now != NULL) {
        if (now->get_name() == _name) { // when name of now
            return now;
        }
        now = now->get_next(); // go to next node
    }
    return NULL;
}

// show all edge
void EdgeList::show_all_menu() {
    Edge* now = this->head;
    for (int i = 0; i < this->size; i++) {
        now->print_edge(); // print edge
        now = now->get_next(); // go to next node
    }
}

// show most popular edge
void EdgeList::show_most_popular() {
    Edge* now = this->head;
    Edge* pop = this->head;
    if (now == NULL) { // when there is no menu
        std::cout << "메뉴가 없습니다." << std::endl;
    }
    else {
        for (int i = 0; i < this->size; i++) {
            if (now->get_sellcount() > pop->get_sellcount()) pop = now; // comparing sell count
            now = now->get_next(); // go to next node
        }
        pop->print_edge(); // print edge
    }
}

// search mousse
void EdgeList::search_by_mousse(std::string _mousse) {
    int cnt = 0; // counting mousse
    Edge* now = this->head;
    for (int i = 0; i < this->size; i++) {
        if (now->get_mousse().find(_mousse) != std::string::npos) { // when mousse is exist
            now->print_edge(); // print edge
            cnt++;
        }
        now = now->get_next(); // go to next node
    }
    std::cout << "이상 총 " << cnt << "개가 검색되었습니다." << std::endl;
}

// set size and head
void EdgeList::set_init() {
    this->size = 0;
    this->head = NULL;
}

// get size
int EdgeList::get_size() {
    return this->size;
}
