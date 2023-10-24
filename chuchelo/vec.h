#ifndef VEC_H
#define VEC_H
#include <QtMath>
#include <QDebug>
#include <QPoint>
#include <QSize>
class Vec2D {

    public:
        double x;
        double y;

        Vec2D(double _x, double _y) : x(_x), y(_y) {}
        Vec2D(int _x, int _y) : x(_x), y(_y) {}

        Vec2D() : x(0.0), y(0.0) {}
        Vec2D operator+(Vec2D other) const {
            return Vec2D{x + other.x, y + other.y};
        }
        Vec2D operator-(Vec2D other) const {
            return Vec2D{x - other.x, y - other.y};
        }

        Vec2D operator*(Vec2D other) const {
            return Vec2D{x * other.x, y * other.y};
        }

        Vec2D operator*(double n) const {
            return Vec2D{x * n, y * n};
        }

        Vec2D operator/(double n) const {
            return Vec2D{x / n, y / n};
        }

        static Vec2D fromSize(QSize size) {
            return Vec2D(size.width(), size.height());
        }

        QPoint toQPoint() {
            return QPoint{(int)x, (int)y};
        }
        QSize toQSize() {
            return QSize{(int)x, (int)y};
        }
        friend Vec2D operator/(double n, const Vec2D& vec) {

            double x, y;
            x = vec.x == 0 ? 1 : vec.x;
            y = vec.y == 0 ? 1 : vec.y;
            return Vec2D{n / x, n / y};
        }

        friend Vec2D operator*(int n, const Vec2D& vec) {

            return Vec2D{n * vec.x, n * vec.y};
        }

        friend Vec2D operator*(double n, const Vec2D& vec) {
            return vec * n;
        }

        friend Vec2D operator-(double n, const Vec2D& vec) {

            return Vec2D{n - vec.x, n - vec.y};
        }

        friend QDebug operator<<(QDebug d, const Vec2D& vec) {
            d << QString("(%0, %1)").arg(vec.x).arg(vec.y);
            return d;
        }

        double scal() {
            return qSqrt(x*x + y*y);
        }


        double distance(Vec2D other) {
            Vec2D prom = (*this-other) * (*this-other);
            return qSqrt(prom.x + prom.y);
        }


};
#endif // VEC_H
