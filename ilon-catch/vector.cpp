#include "vector.h"
#include <QtMath>

Vector::Vector(double curx, double cury)
{
    x = curx;
    y = cury;
}

Vector::Vector(Vector* dop) {
    x = dop->x;
    y = dop->y;
    return;
}

void Vector::setCoordinates(double curx, double cury) {
    x = curx;
    y = cury;
    return;
}

QPair<double, double> Vector::getCoordinates() {
    QPair <double, double> dop = {x, y};
    return dop;
}

Vector Vector::operator*(double k) {
    return Vector(x*k, y*k);
}

Vector Vector::operator+(Vector rightVector) {
    return Vector(x + rightVector.getCoordinates().first, y + rightVector.getCoordinates().second);
}

Vector Vector::operator-(Vector rightVector) {
    return Vector(x - rightVector.getCoordinates().first, y - rightVector.getCoordinates().second);
}

double Vector::operator*(Vector vec) {
    return (x*vec.getCoordinates().first + y*vec.getCoordinates().second);
}

double Vector::distance(Vector* dop) {
    return qSqrt((dop->x-x)*(dop->x-x) + (dop->y-y)*(dop->y-y));
}

double Vector::module() {
    return qSqrt(x*x + y*y);
}
