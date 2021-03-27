#ifndef CELL_H
#define CELL_H

// included header & libraries
#include "bio.h"
#include "enemy.h"
#include <QKeyEvent>

class Cell : public Bio
{
    Q_OBJECT
private :
    // moving direction of object
    dir direction;

    // whether object is boosting now
    bool boost;

public:
    // constructor & destructor
    Cell();
    ~Cell();

    // functions for QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    // keyboard event handler
    void keyPressEvent(QKeyEvent* event);

    // operator overloading
    void operator +(QGraphicsItem* item);
    bool operator >(Bio& other);

public slots:
    // move function
    void move();

    // shrink when boost
    void shrink();

    // add object for every 15 seconds
    void addObject();
};

#endif // CELL_H
