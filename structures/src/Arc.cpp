#include "Arc.h"

#include <cmath>

Arc::Arc(Site site) : site(site) {

}

Arc::Arc(Site site, Arc* previous, Arc* next) : previous(previous), next(next), site(site) {

}

// Get parabola point for x
Vector2 Arc::getPoint(double x, double sweep_line) {
    Vector2 focus = site.point;

    // Distance between the parabola's focus and its vertex
    // Or distance from the parabola's vertex to its directrix (the sweep line)
    double p = (focus.y - sweep_line) / 2;

    // x, y of parabola's vertex,
    double h = focus.x;
    double k = focus.y - p;

    double a = 1 / (4 * p);
    double b = -h / (2 * p);
    double c = (pow(h, 2) / (4 * p)) + k;

    double y = a * pow(x, 2) + b * x + c;

    return Vector2(x, y);
}

// Intersect two parabolas (left intersection)
Vector2 Arc::intersect(Arc arc, double sweep_line) {
    Vector2 g1 = site.point;
    Vector2 g2 = arc.site.point;

    // Half-point between site and sweep line
    double f1 = (g1.y + sweep_line) / 2.0;
    double f2 = (g2.y + sweep_line) / 2.0;

    // Quadratic formula
    double a = 1 / (4 * f1) - 1 / (4 * f2); // TODO: If a is 0, solve linear equation
    double b = -g1.x / (2 * f1) - (-g2.x / (2 * f2));
    double c = pow(g1.x, 2) / (4 * f1) + g1.y + f1 - (pow(g2.x, 2) / (4 * f2) + g2.y + f2);

    double x = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
    double y = (1 / (4 * f1)) * pow(x, 2) - (g1.x / (2 * f1)) * x + pow(g1.x, 2) / (4 * f1) + g1.y + f1;

    return Vector2(x, y);
}

// Intersect parabola with edge
Vector2 Arc::intersect(Edge edge, double sweep_line) {
    Vector2 focus = site.point;

    // Distance between the parabola's focus and its vertex
    // Or distance from the parabola's vertex to its directrix (the sweep line)
    double p = (focus.y - sweep_line) / 2;

    // x, y of parabola's vertex,
    double h = focus.x;
    double k = focus.y - p;

    double a = 1 / (4 * p);
    double b = (-h / (2 * p)) - edge.m;
    double c = ((pow(h, 2) / (4 * p)) + k) - edge.c;

    double delta = b * b - 4 * a * c;
    double x1 = (-b + sqrt(delta)) / (2 * a);
    double x2 = (-b - sqrt(delta)) / (2 * a);

    double min = x1 < x2 ? x1 : x2;
    double max = x1 > x2 ? x1 : x2;
    double x = edge.direction.x < 0 ? min : max;

    return getPoint(x, sweep_line);
}
