#include "Coord.h"

#include <cmath>

const double DEG_TO_RAD = M_PI/180.0;
const double EARTH_RADIUS = 6371000.0;

Coord::Coord() : Vector2(){}
Coord::Coord(double lat, double lon): Vector2(lon, lat){}
Coord::Coord(const Vector2 &v): Vector2(v){}

static double haversine(const Coord &p1, const Coord &p2){
    double dLat = (p1.lat() - p2.lat()) * DEG_TO_RAD;
    double dLon = (p1.lon() - p2.lon()) * DEG_TO_RAD;

    double lat1_rad = p1.lat()*DEG_TO_RAD;
    double lat2_rad = p2.lat()*DEG_TO_RAD;

    double a = (pow(sin(dLat/2.0), 2) + 
                pow(sin(dLon/2.0), 2) *
                    cos(p1.lat()) * cos(p2.lat()));
    double c = 2.0 * asin(sqrt(a));
    return c;
}

double Coord::getDistanceArc(const Coord &p1, const Coord &p2){
    return haversine(p1, p2) * EARTH_RADIUS;
}

double &Coord::lat() { return y; }
double &Coord::lon() { return x; }

const double &Coord::lat() const { return y; }
const double &Coord::lon() const { return x; }

Coord& Coord::operator+=(const Coord& other){ Vector2::operator+=(other); return *this; }
Coord& Coord::operator-=(const Coord& other){ Vector2::operator-=(other); return *this; }
Coord& Coord::operator*=(double t){ Vector2::operator*=(t); return *this; }
Coord& Coord::operator/=(double t){ Vector2::operator/=(t); return *this; }

Coord Coord::operator+(const Coord &rhs) const { return Coord(Vector2::operator+(rhs)); }
Coord Coord::operator-(const Coord &rhs) const { return Coord(Vector2::operator-(rhs)); }
Coord Coord::operator*(double t) const { return Coord(Vector2::operator*(t)); }
Coord Coord::operator/(double t) const { return Coord(Vector2::operator/(t)); }

size_t std::hash<Coord>::operator()(const Coord& v) const { return hash<Vector2>()(v); }
