#ifndef TARGETPHYSICS_H
#define TARGETPHYSICS_H
#include "vec.h"
#include "physsettings.h"
class TargetPhysics {
public:
    TargetPhysics(Vec2D _c0, Vec2D _v0, Vec2D _a, double _maxSpeed, Vec2D _Fm, Vec2D _Fo, double _m, double _u) : pos(_c0), vel(_v0), maxSpeed(_maxSpeed),accel(_a), Fm(_Fm), Fo(_Fo), m(_m), u(_u)  {}
    TargetPhysics(Vec2D _c0, double _maxSpeed) : pos(_c0), vel({0,0}), maxSpeed(_maxSpeed), accel({0,0}), Fm(Vec2D()), Fo(Vec2D()), m(10), u(550){}
    TargetPhysics(Vec2D _c0, PhysSettings ps) : pos(_c0), vel({0,0}), maxSpeed(ps.maxSpeed), accel({0,0}), Fm(Vec2D()), Fo(Vec2D()), m(ps.weight), u(ps.resistFactor){}

    void update(double t) {
        vel = vel + accel*t;
        if (vel.scal() > maxSpeed)
            vel = vel * (maxSpeed / vel.scal());
        pos = pos + vel*t;
    }


    void changeAcceleration(Vec2D _accel) {
        accel = _accel;
    }

    void updateF() {

        double FsScal = u * m;
        if (vel.scal() == 0.0) {
            Fs = Vec2D();
        } else {
            Fs = -1 * vel * (FsScal / vel.scal());
        }
        F = Fm + Fo + Fs;

        accel = F/m;
    }

    void changeFm(Vec2D _Fm) {
        Fm = _Fm;
        updateF();
    }

    void changeFo(Vec2D _Fo) {
        Fo = _Fo;
        updateF();
    }

    void changeVel(Vec2D _vel) {
        vel = _vel;
    }

    Vec2D getPos() {
        return pos;
    }

    Vec2D getVel() {
        return vel;
    }

    Vec2D getAccel() {
        return accel;
    }

    Vec2D getF() {
        return F;
    }
    Vec2D getFm() {
        return Fm;
    }
    Vec2D getFo() {
        return Fo;
    }
    Vec2D getFs() {
        return Fs;
    }

    friend QDebug operator<<(QDebug d, const TargetPhysics& p) {
        d << "TargetPhysics:\n" << "POS:\t" << p.pos << " px;\n" << "VEL:\t" <<p.vel << " px/s\n" << "ACC:\t" <<p.accel << " px/s^2\n" << "F:\t" << p.F;
        return d;
    }

private:
    Vec2D pos;
    Vec2D vel;
    double maxSpeed;
    Vec2D accel;
    Vec2D F;

    Vec2D Fm;
    Vec2D Fs;
    Vec2D Fo;

    double m;
    double u;


};
#endif // TARGETPHYSICS_H
