#ifndef VECTOR_H
#define VECTOR_H
#include <QPair>

class Vector
{
public:
    Vector(double, double);
    Vector(Vector*);
    void setCoordinates(double, double);
    QPair<double, double> getCoordinates();
    Vector operator*(double);
    double operator*(Vector);
    Vector operator+(Vector);
    Vector operator-(Vector);
    double distance(Vector*);
    double module();


private:
    double x;
    double y;
};

#endif // VECTOR_H
