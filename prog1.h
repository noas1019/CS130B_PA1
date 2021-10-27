#ifndef PROG1_H
#define PROG1_H
#include <vector>
#include <cmath>

// Custom Point struct for ease of use
struct Point
{
    public:
        // Custom comparator between Points
        static bool hullcmp(Point &a, Point &b) {
            return a.x < b.x;
        }
        double x, y;
        int index;
        Point() : x(0.0), y(0.0), index(0) {};
        Point(double x, double y, int index) : x(x), y(y), index(index) {};
};

// Custom comparator class for set of Points
struct counterClockwise {
    double getCounterClockwiseAngle(Point point) {
        // Find counter clockwise angle 
        double angle = -1 * atan2(point.x, point.y);
        return angle;
    }
    // Sort with smallest counter clockwise angle -> largest counter clockwise angle
    bool operator() (const Point &lhs, const Point &rhs) {
        return getCounterClockwiseAngle(lhs) < getCounterClockwiseAngle(rhs);
    }
};

#endif
