#ifndef FEED_H
#define FEED_H

// included header & libraries
#include "bio.h"

class Feed : public Bio
{
    Q_OBJECT
public:
	// constructor & destructor
    Feed();
	~Feed();
	
	// functions for QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

public slots:
	// move function
    void move();
};

#endif // FEED_H
