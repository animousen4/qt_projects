#ifndef PHYSSETTINGS_H
#define PHYSSETTINGS_H
class PhysSettings{
    public:
        double maxSpeed;
        double resistFactor;
        double weight;

        PhysSettings(double _maxSpeed, double _resistFactor, double _weight) : maxSpeed(_maxSpeed), resistFactor(_resistFactor), weight(_weight) {

        }

        PhysSettings(double speedFactor) : maxSpeed(speedFactor * 600), resistFactor(750), weight(10) {}


};

/*

    int mouseFactor;
    int borderFactor;

*/
#endif // PHYSSETTINGS_H
