#include "cell.h"

// constructor
Cell::Cell() : Bio() {
	
	// basic information
    this->direction = dir(rand() % 4);
    this->boost = false;
    this->setSize(20);
    this->setPos(400, 400);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

	// timer
    QTimer* t1 = new QTimer();
    QTimer* t2 = new QTimer();
    QTimer* t3 = new QTimer();
    connect(t1, SIGNAL(timeout()), this, SLOT(move()));
    connect(t2, SIGNAL(timeout()), this, SLOT(shrink()));
    connect(t3, SIGNAL(timeout()), this, SLOT(addObject()));
    t1->start(50);
    t2->start(500);
    t3->start(15000);
}

// destructor
Cell::~Cell() {

}

// paint function
void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    painter->drawEllipse(0, 0, this->getSize(), this->getSize());
}

// keypressevent handler
void Cell::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Up) this->direction = up;
    if (event->key() == Qt::Key_Down) this->direction = down;
    if (event->key() == Qt::Key_Left) this->direction = left;
    if (event->key() == Qt::Key_Right) this->direction = right;
    if (event->key() == Qt::Key_Space) this->boost = true;
}

// operator + with other object
void Cell::operator +(QGraphicsItem* item){
    Bio* other = dynamic_cast<Bio*>(item);
	
	// enemy
    if (typeid(*other) == typeid(Enemy)) {
		
		// when cell > enemy
        if (*this > *other) {
            this->setSize(this->getSize() + 0.8*other->getSize());
            this->setPos(x()-other->getSize()/2.5, y()-other->getSize()/2.5);
            scene()->removeItem(item);
        }
		
		// when cell <= enemy
        else {
            exit(0);
        }
    }
	
	// virus
    else if (typeid(*other) == typeid(Virus)) {
        this->setSize(this->getSize() - 0.8*other->getSize());
        this->setPos(x()+other->getSize()/2.5, y()+other->getSize()/2.5);
        scene()->removeItem(item);

		// when cell < virus
        if (this->getSize() <= 0) {
            exit(0);
        }
    }
	
	// feed
    else if (typeid(*other) == typeid(Feed)) {
        this->setSize(this->getSize() + 0.8*other->getSize());
        this->setPos(x()-other->getSize()/2.5, y()-other->getSize()/2.5);
        scene()->removeItem(item);
    }
    return;
}

// operator > with other object
bool Cell::operator >(Bio& other) {
    return this->getSize() > other.getSize();
}

// move function
void Cell::move() {
    // when boost
    int speed = 2;
    if (this->boost) {
        speed = 3;
        this->boost = false;
    }

    // move
    if (this->direction == up) this->setPos(x(), y()-speed);
    if (this->direction == down) this->setPos(x(), y()+speed);
    if (this->direction == left) this->setPos(x()-speed, y());
    if (this->direction == right) this->setPos(x()+speed, y());

    // check collide
    QList <QGraphicsItem *> collided = collidingItems();
    for (int i = 0; i < collided.size(); i++) {
        *this + collided[i];
    }
}

// shrink function when boost
void Cell::shrink() {
    if (this->boost) {
        this->setSize(0.95*this->getSize());
    }
}

// add object function for every 15 seconds
void Cell::addObject() {
    Bio* object[5];
    int r, i;
    for (i = 0; i < 5; i++) {
        int r = rand() % 100;
        if (r < 70) {
            object[i] = new Feed();
        }
        else if (r < 85) {
            object[i] = new Virus();
        }
        else {
            object[i] = new Enemy();
        }
        scene()->addItem(object[i]);
    }
}

