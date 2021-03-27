#ifndef VIRUS_H
#define VIRUS_H

// included header & libraries
#include "bio.h"

class Virus : public Bio
{
    Q_OBJECT
private :
	// moving direction of object
    dir direction;
	
	// store shrink count
    int shrinked;
	
public:
	// constructor & destructor
    Virus();
	~Virus();
	
	// functions for QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

public slots:
	// move function
    void move();
	
	// shrink for every 4 seconds
    void shrink();
};

#endif // VIRUS_H
