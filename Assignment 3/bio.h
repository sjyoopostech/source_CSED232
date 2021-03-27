#ifndef BIO_H
#define BIO_H

// included header & libraries
#include <QGraphicsObject>
#include <QPainter>
#include <QTimer>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <time.h>

// direction enumerated type
enum dir {up=0, right=1, down=2, left=3};

class Bio : public QObject, public QGraphicsItem
{
    Q_OBJECT

private:
    // size of item
    float size;

public:
    // constructor & destructor
    Bio();
    virtual ~Bio();

    // functions for QGraphicsItem
    QRectF boundingRect() const;

    // functions for using size
    float getSize();
    void setSize(float x);

public slots:
    // move function
    virtual void move()=0;
};

#endif // BIO_H
