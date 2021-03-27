#include "virus.h"

// constructor
Virus::Virus() : Bio() {
	
	// set position
    do {
        this->setPos(rand()%800, rand()%800);
        QList <QGraphicsItem*> collided = collidingItems();
        if (collided.size() == 0) break;
    } while(1);

	// basic information
    this->setSize((rand() % 6) + 15);
    this->direction = dir(rand() % 4);
    this->shrinked = 0;

	// timer
    QTimer* t1 = new QTimer();
    QTimer* t2 = new QTimer();
    connect(t1, SIGNAL(timeout()), this, SLOT(move()));
    connect(t2, SIGNAL(timeout()), this, SLOT(shrink()));
    t1->start(1000);
    t2->start(4000);
}

// destructor
Virus::~Virus() {

}

// paint function
void Virus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
    painter->drawRect(0, 0, this->getSize(), this->getSize());
}

// move function
void Virus::move() {
    if (this->direction == up) this->setPos(x(), y()-20);
    if (this->direction == down) this->setPos(x(), y()+20);
    if (this->direction == left) this->setPos(x()-20, y());
    if (this->direction == right) this->setPos(x()+20, y());
    if (this->direction == 0) this->direction = dir(3);
    else this->direction = dir(this->direction-1);
}

// shrink function for every 4 seconds
void Virus::shrink() {
    this->setSize(0.75*this->getSize());
    this->shrinked++;
    if (this->shrinked >= 4) {
        this->setSize(0);
    }
}
