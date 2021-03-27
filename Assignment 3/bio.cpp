#include "bio.h"

// constructor
Bio::Bio() {

}

// destructor
Bio::~Bio() {

}

// boundary
QRectF Bio::boundingRect() const {
    return QRectF(0, 0, this->size, this->size);
}

// get size
float Bio::getSize() {
    return this->size;
}

// set size
void Bio::setSize(float x) {
    this->size = x;
}
