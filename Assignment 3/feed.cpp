#include "feed.h"

// constructor
Feed::Feed() : Bio() {
	
	// set position
    do {
        this->setPos(rand()%800, rand()%800);
        QList <QGraphicsItem*> collided = collidingItems();
        if (collided.size() == 0) break;
    } while(1);

	// basic information
    this->setSize((rand() % 6) + 7);

	// timer
    QTimer* t1 = new QTimer();
    connect(t1, SIGNAL(timeout()), this, SLOT(move()));
    t1->start(50);
}

// destructor
Feed::~Feed() {

}

// paint function
void Feed::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter->drawRect(0, 0, this->getSize(), this->getSize());
}

// move function
void Feed::move() {
    return;
}
