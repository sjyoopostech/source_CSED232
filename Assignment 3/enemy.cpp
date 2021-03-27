#include "enemy.h"

// constructor
Enemy::Enemy() : Bio() {
	
	// set position
    do {
        this->setPos(rand()%800, rand()%800);
        QList <QGraphicsItem*> collided = collidingItems();
        if (collided.size() == 0) break;
    } while(1);

	// basic information
    this->direction = dir(rand() % 4);
    this->setSize((rand() % 31) + 10);

	// timer
    QTimer* t1 = new QTimer();
    QTimer* t2 = new QTimer();
    connect(t1, SIGNAL(timeout()), this, SLOT(move()));
    connect(t2, SIGNAL(timeout()), this, SLOT(changeDir()));
    t1->start(50);
    t2->start(3000);
}

// destructor
Enemy::~Enemy() {

}

// paint function
void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter->drawEllipse(0, 0, this->getSize(), this->getSize());
}

// operator + with other object
void Enemy::operator +(QGraphicsItem* item) {
    Bio* other = dynamic_cast<Bio*>(item);
	
	// enemy
    if (typeid(*other) == typeid(Enemy)) {
		
		// when this > other
        if (*this > *other) {
            this->setSize(this->getSize() + 0.8*other->getSize());
            this->setPos(x()-other->getSize()/2.5, y()-other->getSize()/2.5);
            scene()->removeItem(item);
        }
    }
	
	// virus
    else if (typeid(*other) == typeid(Virus)) {
        this->setSize(this->getSize() - 0.8*other->getSize());
        this->setPos(x()+other->getSize()/2.5, y()+other->getSize()/2.5);
        scene()->removeItem(item);
		
		// when enemy < virus
        if (this->getSize() <= 0) {
            scene()->removeItem(this);
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
bool Enemy::operator >(Bio& other) {
    return this->getSize() > other.getSize();
}

// move function
void Enemy::move() {

    // move
    if (this->direction == up) this->setPos(x(), y()-1);
    if (this->direction == down) this->setPos(x(), y()+1);
    if (this->direction == left) this->setPos(x()-1, y());
    if (this->direction == right) this->setPos(x()+1, y());

    // check collide
    QList <QGraphicsItem*> collided = collidingItems();
    for (int i = 0; i < collided.size(); i++) {
        *this + collided[i];
    }
}

// chande direction function
void Enemy::changeDir() {
    this->direction = dir(rand() % 4);
}
