#ifndef MOVEMENTSETTINGS_H
#define MOVEMENTSETTINGS_H
class MovementSettings {
    public:
        double mouseFactor;
        double borderFactor;

        MovementSettings(double _mouseFactor, double _borderFactor) : mouseFactor(_mouseFactor), borderFactor(_borderFactor) {}
};
#endif // MOVEMENTSETTINGS_H
