/*
 * name     : Seungjae Yoo
 * email    : sjyoo@postech.ac.kr
 * date     : 2017.10.20
 */

// libraries
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

// headers
#include "Topping.h"
#include "Dough.h"
#include "Edge.h"
#include "ToppingList.h"
#include "DoughList.h"
#include "EdgeList.h"

using namespace std;

// functions
string rmspace(string line);
int is_int_float(string line, int f);
void init(ToppingList* tlist, DoughList* dlist, EdgeList* elist);
void print_order();
void choice_0(ToppingList* tlist, DoughList* dlist, EdgeList* elist);
void choice_1(ToppingList* tlist, DoughList* dlist, EdgeList* elist);
void choice_2(ToppingList* tlist, DoughList* dlist, EdgeList* elist);
void choice_3(ToppingList* tlist, DoughList* dlist, EdgeList* elist);
void choice_4(ToppingList* tlist, DoughList* dlist, EdgeList* elist);
void choice_5(ToppingList* tlist, DoughList* dlist, EdgeList* elist);
void choice_7(ToppingList* tlist, DoughList* dlist, EdgeList* elist);

// main function
int main() {

    int choice; // variable that determining choice
    string line; // variable that receive input

    // make lists
    ToppingList* tlist = new ToppingList;
    DoughList* dlist = new DoughList;
    EdgeList* elist = new EdgeList;

    // initialize and read file
    init(tlist, dlist, elist);

    // receiving order
    while (1) {

        // print main menu
        print_order();

        // get choice
        while (1) {
            cout << ">>";
            cin >> line;
            if (line.length() > 1 || line.length() == 0) {
                cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
                continue;
            }
            if (line.at(0) > 0x37 || line.at(0) < 0x30) {
                cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
                continue;
            }
            else break;
        }
        choice = atoi(line.c_str());

        // execute function by choice
        switch(choice) {
        case 0:
            choice_0(tlist, dlist, elist);
            break;
        case 1:
            choice_1(tlist, dlist, elist);
            break;
        case 2:
            choice_2(tlist, dlist, elist);
            break;
        case 3:
            choice_3(tlist, dlist, elist);
            break;
        case 4:
            choice_4(tlist, dlist, elist);
            break;
        case 5:
            choice_5(tlist, dlist, elist);
            break;
        case 6:
            exit(0);
            break;
        case 7:
            choice_7(tlist, dlist, elist);
            break;
        }
    }
    return 0;
}

// removing space bars
string rmspace(string line) {
    int i, j = 0;
    for (i = 0; i < line.length(); i++) {
        if (line.at(i) == ' ') continue; // when this is space bar
        line.at(j) = line.at(i); // when this is not space bar
        j++;
    }
    line.resize(j); // resizing string
    return line;
}

// determining int or float (f=0:float, f=1:int)
int is_int_float(string line, int f) {
    int i = 0;
    for (i = 0; i < line.length(); i++) {
        if (line.at(i) == '.') f++;
        else if (line.at(i) < 0x30 || line.at(i) > 0x39){
            return 0;
        }
    }
    if (f > 1) return 0;
    return 1;
}

// print main menu
void print_order() {
    cout << "=============" << endl;
    cout << "0: ��� �޴� ����" << endl;
    cout << "1: �ֹ��ϱ�" << endl;
    cout << "2: �޴� �߰�" << endl;
    cout << "3: �޴� ����" << endl;
    cout << "4: �޴� �˻�" << endl;
    cout << "5: �α�޴� ��õ" << endl;
    cout << "6: ���α׷� ����" << endl;
    cout << "7: �޴� ����" << endl;
    cout << "=============" << endl;
}

// read file and ready for sale
void init(ToppingList* tlist, DoughList* dlist, EdgeList* elist) {

    // setting initial list values
    tlist->set_init();
    dlist->set_init();
    elist->set_init();

    int status = 0; // variable that determining class
    string line, subline; // variables that storing string
    int s, e, _s, _e; // variables that indexing start and end

    // open file
    ifstream in;
    in.open("init_menu.txt");

    // succeed to open file
    if (in.is_open()) {

        // get a line
        while (getline(in, line, '\n')) {
            // topping menu
            if (status == 0 && line == "-����") {
                status++;
                continue;
            }

            // dough menu
            else if (status == 1 && line == "-����") {
                status++;
                continue;
            }

            // edge menu
            else if (status == 2 && line == "-����") {
                status++;
                continue;
            }

            // topping
            if (status == 1) {

                // initial setting
                Topping* now = new Topping;
                now->set_init();

                // name
                s = 0;
                e = line.find('\t', s);
                subline = line.substr(s, e-s);
                subline = rmspace(subline);
                now->set_name(subline);

                // ingredient
                s = e+1;
                e = line.find('\t', s);
                subline = line.substr(s, e-s);
                subline = rmspace(subline);
                _s = 0;
                while (1) { // dividing by comma
                    _e = subline.find(',', _s);
                    if (_e == -1) {
                        if (subline.substr(_s).length() == 0) break; // when there's no ingredient
                        if (now->add_ingredient(subline.substr(_s))) { // last ingredient
                            cout << "��ᰡ �ʹ� �����ϴ�." << endl;
                            exit(0);
                        }
                        break;
                    }
                    if (now->add_ingredient(subline.substr(_s, _e-_s))){ // ingredient which is not last
                        cout << "��ᰡ �ʹ� �����ϴ�." << endl;
                        exit(0);
                    }
                    _s = _e+1;
                }

                // price
                s = e+1;
                e = line.find('\t', s);
                subline = line.substr(s, e-s);
                now->set_price(atoi(subline.c_str()));

                // comment
                s = e+1;
                subline = line.substr(s);
                now->set_comment(subline);

                // add
                tlist->add(now);
            }

            // dough
            else if (status == 2) {

                // initial setting
                Dough* now = new Dough;
                now->set_init();

                // name
                s = 0;
                e = line.find('\t', s);
                subline = line.substr(s, e-s);
                subline = rmspace(subline);
                now->set_name(subline);

                // thickness
                s = e+1;
                e = line.find('\t', s);
                subline = line.substr(s, e-s);
                now->set_thickness(atof(subline.c_str()));

                // extra cost
                s = e+1;
                e = line.find('\t', s);
                subline = line.substr(s, e-s);
                now->set_extracost(atoi(subline.c_str()));

                // comment
                s = e+1;
                subline = line.substr(s);
                now->set_comment(subline);

                // add
                dlist->add(now);

            }

            // edge
            else if (status == 3) {

                // initial setting
                Edge* now = new Edge;
                now->set_init();

                // name
                s = 0;
                e = line.find('\t', s);
                subline = line.substr(s, e-s);
                subline = rmspace(subline);
                now->set_name(subline);

                // mousse
                s = e+1;
                e = line.find('\t', s);
                subline = line.substr(s, e-s);
                subline = rmspace(subline);
                _s = 0;
                while (1) { // dividing comma
                    _e = subline.find(',', _s);
                    if (_e == -1) {
                        if (subline.substr(_s).length() == 0) break; // when there's no mousse
                        if (now->add_mousse(subline.substr(_s))) { // last mousse
                            cout << "������ �ʹ� �����ϴ�." << endl;
                            exit(0);
                        }
                        break;
                    }
                    if (now->add_mousse(subline.substr(_s, _e-_s))) { // mousse which is not last
                        cout << "������ �ʹ� �����ϴ�." << endl;
                        exit(0);
                    }
                    _s = _e+1;
                }

                // extra cost
                s = e+1;
                e = line.find('\t', s);
                subline = line.substr(s, e-s);
                now->set_extracost(atoi(subline.c_str()));

                // comment
                s = e+1;
                subline = line.substr(s);
                now->set_comment(subline);

                // add
                elist->add(now);
            }
        }
    }

    // fail to open file
    else {
        cout << "������ �� �� �����ϴ�." << endl;
        exit(0);
    }

    // closing file
    in.close();
}

// show all menu
void choice_0(ToppingList* tlist, DoughList* dlist, EdgeList* elist) {

    // topping
    cout << "-TOPPING<" << tlist->get_size() << ">" << endl;
    tlist->show_all_menu();

    // dough
    cout << "-DOUGH<" << dlist->get_size() << ">" << endl;
    dlist->show_all_menu();

    // edge
    cout << "-EDGE<" << elist->get_size() << ">" << endl;
    elist->show_all_menu();
}

// order
void choice_1(ToppingList* tlist, DoughList* dlist, EdgeList* elist) {

    string t_name, d_name, e_name; // variables that storing name
    Topping* t; // variable that storing selected topping
    Dough* d; // variable that storing selected topping
    Edge* e; // variable that storing selected topping

    // topping
    cout << "-TOPPING<" << tlist->get_size() << ">" << endl;
    tlist->show_all_menu();
    cout << "���Ͻô� ���� �̸��� �Է��ϼ���." << endl;
    while (1) { // get name
        cout << ">>";
        cin >> t_name;
        t = tlist->pick(t_name);
        if (t != NULL) break;
        cout << "���Ͻô� ������ �����ϴ�. �ٽ� �Է��� �ּ���." << endl;
    }

    // dough
    cout << "-DOUGH<" << dlist->get_size() << ">" << endl;
    dlist->show_all_menu();
    cout << "���Ͻô� ���� �̸��� �Է��ϼ���." << endl;
    while (1) { // get name
        cout << ">>";
        cin >> d_name;
        d = dlist->pick(d_name);
        if (d != NULL) break;
        cout << "���Ͻô� ���찡 �����ϴ�. �ٽ� �Է��� �ּ���." << endl;
    }

    // edge
    cout << "-EDGE<" << elist->get_size() << ">" << endl;
    elist->show_all_menu();
    cout << "���Ͻô� ���� �̸��� �Է��ϼ���." << endl;
    while (1) { // get name
        cout << ">>";
        cin >> e_name;
        e = elist->pick(e_name);
        if (e != NULL) break;
        cout << "���Ͻô� ������ �����ϴ�. �ٽ� �Է��� �ּ���." << endl;
    }

    // show received order
    cout << "�ֹ��Ͻ� ���ڴ� \"" << d_name << " " << e_name << " " << t_name << "\" �Դϴ�." << endl;
    cout << "������ \"" << t->get_price() + d->get_extracost() + e->get_extracost() << "\"�� �Դϴ�." << endl;

    // increasing sell count
    t->inc_sellcount();
    d->inc_sellcount();
    e->inc_sellcount();
}

// add menu
void choice_2(ToppingList* tlist, DoughList* dlist, EdgeList* elist) {

    int type; // variable that determining type
    string line; // variable that receiving input

    // get type
    cout << "�߰��ϰ��� �ϴ� �޴��� ������ �����ϼ���." << endl;
    cout << "1: ����" << endl;
    cout << "2: ����" << endl;
    cout << "3: ����" << endl;
    while (1) { // determine valid type
        cout << ">>";
        cin >> line;
        if (line.length() > 1 || line.length() == 0) { // when length is not 1
            cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
            continue;
        }
        if (line.at(0) > 0x33 || line.at(0) < 0x31) { // when input is more than 3 or less than 1
            cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
            continue;
        }
        else break;
    }
    type = atoi(line.c_str());

    // topping
    if (type == 1) {

        // initial setting
        Topping* now = new Topping;
        now->set_init();

        // variables that elements of topping
        string name, ingredient, comment;
        int price;

        // name
        cout << "�̸�" << endl;
        while (1) { // get name
            cout << ">>";
            cin >> name;
            name = rmspace(name);
            if (tlist->pick(name) == NULL) break;
            cout << "�ش� ������ �̹� �ֽ��ϴ�. �ٽ� �Է��� �ּ���." << endl;
        }
        now->set_name(name);

        // ingredient
        cout << "���" << endl;
        cout << ">>";
        getline(cin, ingredient, '\n');
        getline(cin, ingredient, '\n');
        ingredient = rmspace(ingredient);
        int s = 0;
        int e;
        while (1) { // add ingredient
            e = ingredient.find(',', s);
            if (e == -1) {
                if (ingredient.substr(s).length() == 0) break; // when there's no ingredient
                if (now->add_ingredient(ingredient.substr(s))) { // last ingredient
                    cout << "��ᰡ �ʹ� �����ϴ�." << endl;
                    exit(0);
                }
                break;
            }
            if (now->add_ingredient(ingredient.substr(s, e-s))) { // ingredient which is not last
                cout << "��ᰡ �ʹ� �����ϴ�." << endl;
                exit(0);
            }
            s = e+1;
        }

        // price
        cout << "����" << endl;
        cout << ">>";
        cin >> line;
        while (!is_int_float(line, 1)) { // determine string is int
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
            cout << ">>";
            cin >> line;
        }
        price = atoi(line.c_str());
        now->set_price(price);

        // comment
        cout << "�Ұ���" << endl;
        cout << ">>";
        getline(cin, comment, '\n');
        getline(cin, comment, '\n');
        now->set_comment(comment);

        // add
        tlist->add(now);
    }
    else if (type == 2) {

        // initial setting
        Dough* now = new Dough;
        now->set_init();

        // variables that elements of dough
        string name, comment;
        float thickness;
        int extracost;

        // name
        cout << "�̸�" << endl;
        while (1) { // get name
            cout << ">>";
            cin >> name;
            name = rmspace(name);
            if (dlist->pick(name) == NULL) break;
            cout << "�ش� ���찡 �̹� �ֽ��ϴ�. �ٽ� �Է��� �ּ���." << endl;
        }
        now->set_name(name);

        // thickness
        cout << "�β�" << endl;
        cout << ">>";
        cin >> line;
        while (!is_int_float(line, 0)) { // determine string is float
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
            cout << ">>";
            cin >> line;
        }
        thickness = atof(line.c_str());
        now->set_thickness(thickness);

        // extra cost
        cout << "�߰����" << endl;
        cout << ">>";
        cin >> line;
        while (!is_int_float(line, 1)) { // determine string is int
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
            cout << ">>";
            cin >> line;
        }
        extracost = atoi(line.c_str());
        now->set_extracost(extracost);

        // comment
        cout << "�Ұ���" << endl;
        cout << ">>";
        getline(cin, comment, '\n');
        getline(cin, comment, '\n');
        now->set_comment(comment);

        // add
        dlist->add(now);
    }
    else if (type == 3) {

        // initial setting
        Edge* now = new Edge;
        now->set_init();

        // variables that elements of edge
        string name, mousse, comment;
        int extracost;

        // name
        cout << "�̸�" << endl;
        while (1) { // get name
            cout << ">>";
            cin >> name;
            name = rmspace(name);
            if (elist->pick(name) == NULL) break;
            cout << "�ش� ������ �̹� �ֽ��ϴ�. �ٽ� �Է��� �ּ���." << endl;
        }
        now->set_name(name);

        // mousse
        cout << "����" << endl;
        cout << ">>";
        getline(cin, mousse, '\n');
        getline(cin, mousse, '\n');
        mousse = rmspace(mousse);
        int s = 0;
        int e;
        while (1) { // add mousse
            e = mousse.find(',', s);
            if (e == -1) {
                if (mousse.substr(s).length() == 0) break; // when there's no ingredient
                if (now->add_mousse(mousse.substr(s))) { // last mousse
                    cout << "������ �ʹ� �����ϴ�." << endl;
                    exit(0);
                }
                break;
            }
            if (now->add_mousse(mousse.substr(s, e-s))) { // mousse which is not last
                cout << "������ �ʹ� �����ϴ�." << endl;
                exit(0);
            }
            s = e+1;
        }

        // extra cost
        cout << "�߰����" << endl;
        cout << ">>";
        cin >> line;
        while (!is_int_float(line, 1)) { // determine string is int
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
            cout << ">>";
            cin >> line;
        }
        extracost = atoi(line.c_str());
        now->set_extracost(extracost);

        // comment
        cout << "�Ұ���" << endl;
        cout << ">>";
        getline(cin, comment, '\n');
        getline(cin, comment, '\n');
        now->set_comment(comment);

        elist->add(now);
    }
}

// delete menu
void choice_3(ToppingList* tlist, DoughList* dlist, EdgeList* elist) {

    int type; // variable that determining type
    string name; // variable that storing name

    // get type
    cout << "�����ϰ��� �ϴ� �޴��� ������ �����ϼ���." << endl;
    cout << "1: ����" << endl;
    cout << "2: ����" << endl;
    cout << "3: ����" << endl;
    while (1) { // determine valid type
        cout << ">>";
        cin >> name;
        if (name.length() > 1 || name.length() == 0) { // when length is not 1
            cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
            continue;
        }
        if (name.at(0) > 0x33 || name.at(0) < 0x31) { // when input is more than 3 or less than 1
            cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
            continue;
        }
        else break;
    }
    type = atoi(name.c_str());

    // topping
    if (type == 1) {

        // show all menu
        cout << "-TOPPING<" << tlist->get_size() << ">" << endl;
        tlist->show_all_menu();

        // delete menu
        cout << "�����ϰ��� �ϴ� �޴��� �̸��� �Է��ϼ���." << endl;
        cout << ">>";
        cin >> name;
        if (tlist->del(name)) { // when there is menu
            cout << "�޴� ������ �Ϸ�Ǿ����ϴ�." << endl;
        }
        else { // when there isn't menu
            cout << "�ش� �޴��� �����ϴ�." << endl;
            exit(0);
        }
    }

    // dough
    else if (type == 2) {

        // show all menu
        cout << "-DOUGH<" << dlist->get_size() << ">" << endl;
        dlist->show_all_menu();

        // delete menu
        cout << "�����ϰ��� �ϴ� �޴��� �̸��� �Է��ϼ���." << endl;
        cout << ">>";
        cin >> name;
        if (dlist->del(name)) { // when there is menu
            cout << "�޴� ������ �Ϸ�Ǿ����ϴ�." << endl;
        }
        else { // when there isn't menu
            cout << "�ش� �޴��� �����ϴ�." << endl;
            exit(0);
        }
    }

    // edge
    else if (type == 3) {

        // show all menu
        cout << "-EDGE<" << elist->get_size() << ">" << endl;
        elist->show_all_menu();

        // delete menu
        cout << "�����ϰ��� �ϴ� �޴��� �̸��� �Է��ϼ���." << endl;
        cout << ">>";
        cin >> name;
        if (elist->del(name)) { // when there is menu
            cout << "�޴� ������ �Ϸ�Ǿ����ϴ�." << endl;
        }
        else { // when there isn't menu
            cout << "�ش� �޴��� �����ϴ�." << endl;
            exit(0);
        }
    }
}

// search menu
void choice_4(ToppingList* tlist, DoughList* dlist, EdgeList* elist) {

    int type; // variable that determining type
    string line; // variable that receiving input

    // get type
    cout << "�˻��ϰ��� �ϴ� �޴��� ������ �����ϼ���." << endl;
    cout << "1: ����" << endl;
    cout << "2: ����" << endl;
    cout << "3: ����" << endl;
    while (1) { // determine valid type
        cout << ">>";
        cin >> line;
        if (line.length() > 1 || line.length() == 0) { // when length is not 1
            cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
            continue;
        }
        if (line.at(0) > 0x33 || line.at(0) < 0x31) { // when input is more than 3 or less than 1
            cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
            continue;
        }
        else break;
    }
    type = atoi(line.c_str());

    // topping
    if (type == 1) {

        // get type
        cout << "�˻� ������ �����ϼ���." << endl;
        cout << "1: ���� �˻�" << endl;
        cout << "2: �������� �˻�" << endl;
        while (1) { // determine valid type
            cout << ">>";
            cin >> line;
            if (line.length() > 1 || line.length() == 0) { // when length is not 1
                cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
                continue;
            }
            if (line.at(0) > 0x32 || line.at(0) < 0x31) { // when input is more than 2 or less than 1
                cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
                continue;
            }
            else break;
        }
        type = atoi(line.c_str());

        // ingredient
        if (type == 1) {

            string ingredient;

            cout << "��� �̸��� �Է����ּ���." << endl;
            cout << ">>";
            cin >> ingredient;

            // search
            tlist->search_by_ingred(ingredient);
        }

        // price
        else if (type == 2) {

            int low_price, high_price;

            // low price
            cout << "���� ���� �� ������ �Է����ּ���." << endl;
            cout << ">>";
            cin >> line;
            while (!is_int_float(line, 1)) { // determine string is int
                cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
                cout << ">>";
                cin >> line;
            }
            low_price = atoi(line.c_str());

            // high price
            cout << "���� ���� �� ������ �Է����ּ���." << endl;
            cout << ">>";
            cin >> line;
            while (!is_int_float(line, 1)) { // determine string is int
                cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
                cout << ">>";
                cin >> line;
            }
            high_price = atoi(line.c_str());

            // search
            tlist->search_by_price(low_price, high_price);
        }
    }

    // dough
    else if (type == 2) {

        // get type
        cout << "�˻� ������ �����ϼ���." << endl;
        cout << "1: �β��� �˻�" << endl;
        while (1) { // determine valid type
            cout << ">>";
            cin >> line;
            if (line.length() > 1 || line.length() == 0) { // when length is not 1
                cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
                continue;
            }
            if (line.at(0) != 0x31) { // when input is not '1'
                cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
                continue;
            }
            else break;
        }
        type = atoi(line.c_str());

        // thickness
        if (type == 1) {

            float low_thick, high_thick;

            // low thickness
            cout << "�β� ���� �� ������ �Է����ּ���." << endl;
            cout << ">>";
            cin >> line;
            while (!is_int_float(line, 0)) { // determine string is float
                cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
                cout << ">>";
                cin >> line;
            }
            low_thick = atof(line.c_str());

            // high thickness
            cout << "�β� ���� �� ������ �Է����ּ���." << endl;
            cout << ">>";
            cin >> line;
            while (!is_int_float(line, 0)) { // determine string is float
                cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
                cout << ">>";
                cin >> line;
            }
            high_thick = atof(line.c_str());

            // search
            dlist->search_by_thick(low_thick, high_thick);
        }
    }
    else if (type == 3) {

        // get type
        cout << "�˻� ������ �����ϼ���." << endl;
        cout << "1: ������ �˻�" << endl;
        while (1) { // determine valid type
            cout << ">>";
            cin >> line;
            if (line.length() > 1 || line.length() == 0) { // when length is not 1
                cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
                continue;
            }
            if (line.at(0) != 0x31) { // when input is not '1'
                cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
                continue;
            }
            else break;
        }
        type = atoi(line.c_str());

        // mousse
        if (type == 1) {

            string mousse;

            cout << "���� �̸��� �Է����ּ���." << endl;
            cout << ">>";
            cin >> mousse;

            // search
            elist->search_by_mousse(mousse);
        }
    }
}

// show popular menu
void choice_5(ToppingList* tlist, DoughList* dlist, EdgeList* elist) {

    // topping
    cout << "-TOPPING �α�޴�" << endl;
    tlist->show_most_popular();

    // dough
    cout << "-DOUGH �α�޴�" << endl;
    dlist->show_most_popular();

    // edge
    cout << "-EDGE �α�޴�" << endl;
    elist->show_most_popular();
}

// change menu
void choice_7(ToppingList* tlist, DoughList* dlist, EdgeList* elist) {

    int type; // variable that determining type
    string name; // variable that storing name
    string line; // variable that receives input

    // get type
    cout << "�����ϰ��� �ϴ� �޴��� ������ �����ϼ���." << endl;
    cout << "1: ����" << endl;
    cout << "2: ����" << endl;
    cout << "3: ����" << endl;
    while (1) { // determine valid type
        cout << ">>";
        cin >> line;
        if (line.length() > 1 || line.length() == 0) { // when length is not 1
            cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
            continue;
        }
        if (line.at(0) > 0x33 || line.at(0) < 0x31) { // when input is more than 3 or less than 1
            cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
            continue;
        }
        else break;
    }
    type = atoi(line.c_str());

    // topping
    if (type == 1) {

        // get topping
        Topping* now;
        cout << "-TOPPING<" << tlist->get_size() << ">" << endl;
        tlist->show_all_menu();
        cout << "�����Ͻ� ���� �̸��� �Է��ϼ���." << endl;
        while (1) { // get name
            cout << ">>";
            cin >> name;
            now = tlist->pick(name);
            if (now != NULL) break;
            cout << "�ش� ������ �����ϴ�. �ٽ� �Է��� �ּ���." << endl;
        }

        // get type
        cout << "�����ϰ��� �ϴ� ������ �����ϼ���." << endl;
        cout << "1: �̸�" << endl;
        cout << "2: ���" << endl;
        cout << "3: ����" << endl;
        cout << "4: �Ұ���" << endl;
        while (1) { // determine valid type
            cout << ">>";
            cin >> line;
            if (line.length() > 1 || line.length() == 0) { // when length is not 1
                cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
                continue;
            }
            if (line.at(0) > 0x34 || line.at(0) < 0x31) { // when input is more than 4 or less than 1
                cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
                continue;
            }
            else break;
        }
        type = atoi(line.c_str());

        // name
        if (type == 1) {
            string name;
            cout << "���ο� �̸�" << endl;
            cout << ">>";
            cin >> name;
            name = rmspace(name);
            now->set_name(name);
        }

        // ingredient
        else if (type == 2) {
            string ingredient;
            now->clear_ingredient();
            cout << "���ο� ���" << endl;
            cout << ">>";
            getline(cin, ingredient, '\n');
            getline(cin, ingredient, '\n');
            ingredient = rmspace(ingredient);
            int s = 0;
            int e;
            while (1) { // add ingredient
                e = ingredient.find(',', s);
                if (e == -1) {
                    if (ingredient.substr(s).length() == 0) break; // when there's no ingredient
                    if (now->add_ingredient(ingredient.substr(s))) { // last ingredient
                        cout << "��ᰡ �ʹ� �����ϴ�." << endl;
                        exit(0);
                    }
                    break;
                }
                if (now->add_ingredient(ingredient.substr(s, e-s))) { // ingredient which is not last
                    cout << "��ᰡ �ʹ� �����ϴ�." << endl;
                    exit(0);
                }
                s = e+1;
            }
        }

        // price
        else if (type == 3) {
            int price;
            cout << "���ο� ����" << endl;
            cout << ">>";
            cin >> line;
            while (!is_int_float(line, 1)) { // determine string is int
                cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
                cout << ">>";
                cin >> line;
            }
            price = atoi(line.c_str());
            now->set_price(price);
        }

        // comment
        else if (type == 4) {
            string comment;
            cout << "���ο� �Ұ���" << endl;
            cout << ">>";
            getline(cin, comment, '\n');
            getline(cin, comment, '\n');
            now->set_comment(comment);
        }
    }

    // dough
    else if (type == 2) {

        // get dough
        Dough* now;
        cout << "-DOUGH<" << dlist->get_size() << ">" << endl;
        dlist->show_all_menu();
        cout << "�����Ͻ� ���� �̸��� �Է��ϼ���." << endl;
        while (1) { // get name
            cout << ">>";
            cin >> name;
            now = dlist->pick(name);
            if (now != NULL) break;
            cout << "�ش� ���찡 �����ϴ�. �ٽ� �Է��� �ּ���." << endl;
        }

        // get type
        cout << "�����ϰ��� �ϴ� ������ �����ϼ���." << endl;
        cout << "1: �̸�" << endl;
        cout << "2: �β�" << endl;
        cout << "3: �߰����" << endl;
        cout << "4: �Ұ���" << endl;
        while (1) { // determine valid type
            cout << ">>";
            cin >> line;
            if (line.length() > 1 || line.length() == 0) { // when length is not 1
                cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
                continue;
            }
            if (line.at(0) > 0x34 || line.at(0) < 0x31) { // when input is more than 4 or less than 1
                cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
                continue;
            }
            else break;
        }
        type = atoi(line.c_str());

        // name
        if (type == 1) {
            string name;
            cout << "���ο� �̸�" << endl;
            cout << ">>";
            cin >> name;
            name = rmspace(name);
            now->set_name(name);
        }

        // thickness
        else if (type == 2) {
            float thickness;
            cout << "���ο� �β�" << endl;
            cout << ">>";
            cin >> line;
            while (!is_int_float(line, 0)) { // determine string is float
                cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
                cout << ">>";
                cin >> line;
            }
            thickness = atof(line.c_str());
            now->set_thickness(thickness);
        }

        // extra cost
        else if (type == 3) {
            int extracost;
            cout << "���ο� �߰����" << endl;
            cout << ">>";
            cin >> line;
            while (!is_int_float(line, 1)) { // determine string is int
                cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
                cout << ">>";
                cin >> line;
            }
            extracost = atoi(line.c_str());
            now->set_extracost(extracost);
        }

        // comment
        else if (type == 4) {
            string comment;
            cout << "���ο� �Ұ���" << endl;
            cout << ">>";
            getline(cin, comment, '\n');
            getline(cin, comment, '\n');
            now->set_comment(comment);
        }
    }

    // edge
    else if (type == 3) {

        // get edge
        Edge* now;
        cout << "-EDGE<" << elist->get_size() << ">" << endl;
        elist->show_all_menu();
        cout << "�����Ͻ� ���� �̸��� �Է��ϼ���." << endl;
        while (1) { // get name
            cout << ">>";
            cin >> name;
            now = elist->pick(name);
            if (now != NULL) break;
            cout << "�ش� ������ �����ϴ�. �ٽ� �Է��� �ּ���." << endl;
        }

        // get type
        cout << "�����ϰ��� �ϴ� ������ �����ϼ���." << endl;
        cout << "1: �̸�" << endl;
        cout << "2: ����" << endl;
        cout << "3: �߰����" << endl;
        cout << "4: �Ұ���" << endl;
        while (1) { // determine valid type
            cout << ">>";
            cin >> line;
            if (line.length() > 1 || line.length() == 0) { // when length is not 1
                cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
                continue;
            }
            if (line.at(0) > 0x34 || line.at(0) < 0x31) { // when input is more than 4 or less than 1
                cout << "�߸��� ����Դϴ�. �ٽ� �Է����ּ���." << endl;
                continue;
            }
            else break;
        }
        type = atoi(line.c_str());

        // name
        if (type == 1) {
            string name;
            cout << "���ο� �̸�" << endl;
            cout << ">>";
            cin >> name;
            name = rmspace(name);
            now->set_name(name);
        }

        // mousse
        else if (type == 2) {
            string mousse;
            now->clear_mousse();
            cout << "���ο� ����" << endl;
            cout << ">>";
            getline(cin, mousse, '\n');
            getline(cin, mousse, '\n');
            mousse = rmspace(mousse);
            int s = 0;
            int e;
            while (1) { // add mousse
                e = mousse.find(',', s);
                if (e == -1) {
                    if (mousse.substr(s).length() == 0) break; // when there's no ingredient
                    if (now->add_mousse(mousse.substr(s))) { // last mousse
                        cout << "������ �ʹ� �����ϴ�." << endl;
                        exit(0);
                    }
                    break;
                }
                if (now->add_mousse(mousse.substr(s, e-s))) { // mousse which is not last
                    cout << "������ �ʹ� �����ϴ�." << endl;
                    exit(0);
                }
                s = e+1;
            }
        }

        // extra cost
        else if (type == 3) {
            int extracost;
            cout << "���ο� �߰����" << endl;
            cout << ">>";
            cin >> line;
            while (!is_int_float(line, 1)) { // determine string is int
                cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
                cout << ">>";
                cin >> line;
            }
            extracost = atoi(line.c_str());
            now->set_extracost(extracost);
        }

        // comment
        else if (type == 4) {
            string comment;
            cout << "���ο� �Ұ���" << endl;
            cout << ">>";
            getline(cin, comment, '\n');
            getline(cin, comment, '\n');
            now->set_comment(comment);
        }
    }
}
