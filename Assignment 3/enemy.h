#ifndef ENEMY_H
#define ENEMY_H

// included header & libraries
#include "bio.h"
#include "virus.h"
#include "feed.h"

class Enemy : public Bio
{
    Q_OBJECT
private:
	// moving direction of object
    dir direction;
	
public:
	// constructor & destructor
    Enemy();
	~Enemy();
	
	// functions for QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

	// operator overloading
    void operator +(QGraphicsItem* item);
    bool operator >(Bio& other);

public slots:
	// move function
    void move();
	
	// change direction
    void changeDir();
};

#endif // ENEMY_H
