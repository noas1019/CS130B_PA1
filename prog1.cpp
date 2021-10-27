#include <iostream>
#include <algorithm>
#include <set>
#include <math.h>
#include <vector>
#include <sstream>
#include <string>
#include "prog1.h"
using namespace std;

// Set of Points sorted counter-clockwise will be Convex Hull
set<Point, counterClockwise> ConvexHull;

// Find distance between C and the line joining A and B
double findDistance(Point A, Point B, Point C) {
    return fabs((B.x-A.x) * (C.y-A.y) - (C.x-A.x) * (B.y-A.y));
}

// See which side C is on of the line joining A and B
double whichSide(Point A, Point B, Point C) {
    int result;
    double line = (B.x-A.x) * (C.y-A.y) - (C.x-A.x) * (B.y-A.y);
    if (line >= 0) {
        result = 1;
    } else {
        result = -1;
    }
    return result;
}

// Recursive function to make hull
void recursive(vector<Point> points, Point A, Point B, int n, double line) {
    // Recursive function will find largest point from line A-B and draw a triangle
    // with three points, any point in triangle is disqualified from Conves Hull.
    // Recursion stops when there are no points left outside of the given line.
    double maxDistance = 0;
    int curr_index = -1;
    for (int i = 0; i < n; i++) {
        double distance = findDistance(A, B, points[i]);
        if (distance > maxDistance && whichSide(A, B, points[i]) == line) {
            maxDistance = distance;
            curr_index = i;
        }
    }
    // Base case (no larger distance in points)
    if (curr_index == -1) {
        ConvexHull.insert(A);
        ConvexHull.insert(B);
        return;
    } else {  // Continue recursions (not the largest distance in points)
        recursive(points, points[curr_index], A, n, -whichSide(points[curr_index], A, B));
        recursive(points, points[curr_index], B, n, -whichSide(points[curr_index], B, A));
    }
}
  
void quickHull(vector<Point> points, int n) {
    // Iterate through vector and find smallest and largest x-values
    int minXindex = 0;
    int maxXindex = 0;
    for (int i=1; i<n; i++) {
        if(points[i].x < points[minXindex].x) {
            minXindex = i;
        }
        if(points[maxXindex].x < points[i].x) {
            maxXindex = i;
        }
    }
    
    // Two separate recursions to find convex hull points on both sides of the line joining min x and max x
    recursive(points, points[minXindex], points[maxXindex], n, 1);
    recursive(points, points[minXindex], points[maxXindex], n, -1);

    // Prints hull and hull's size
    cout << ConvexHull.size() << endl;
    for (Point p : ConvexHull) {
        cout << p.index << ", " << p.x << ", " << p.y << endl;
    }
}

int main() {
    // Vector of points to feed into quickHull
    vector<Point> points;

    // Grab first integer and make it hull's size
    string line;
    int n;
    getline(cin, line);
    n = stoi(line);

    // Iterate and parse through inputs
    for(int i = 0; i < n; i++) {
        getline(cin, line);
        double x, y;
        char comma;
        istringstream iss(line);
        iss >> x;
        iss >> comma;
        iss >> y;
        Point point(x, y, i);
        points.push_back(point);
    }
    
    // Call quickHull, will create Convex Hull and display
    quickHull(points, n);

    return 0;
}
