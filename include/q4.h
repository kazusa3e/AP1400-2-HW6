#ifndef Q4_H
#define Q4_H

#include <algorithm>
#include <numeric>
#include <vector>

namespace q4 {

struct Vector2D {
    double x{};
    double y{};
};

struct Sensor {
    Vector2D pos;
    double accuracy;
};

inline Vector2D kalman_filter(const std::vector<Sensor> &sensors) {
    double totalWeight = 0.0;
    Vector2D ret = std::accumulate(sensors.begin(), sensors.end(), Vector2D{0.0, 0.0}, [&totalWeight](Vector2D acc, const Sensor &s) {
        double weight = s.accuracy;
        totalWeight += weight;
        return Vector2D{
            acc.x + weight * s.pos.x,
            acc.y + weight * s.pos.y};
    });
    ret.x /= totalWeight;
    ret.y /= totalWeight;
    return ret;
}

};  // namespace q4

#endif  // Q4_H