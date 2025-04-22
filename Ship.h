#ifndef SHIP_H
#define SHIP_H

#include <cstdint>
#include <vector>

enum class Orientation {
    HORIZONTAL,
    VERTICAL
};

struct Coordinate {
    uint64_t x;
    uint64_t y;
};

class Ship {
public:
    Ship(uint64_t size, Orientation orientation, Coordinate start);
    bool contains(const Coordinate& coord) const;
    void hit(const Coordinate& coord);
    bool is_destroyed() const;
    std::vector<Coordinate> get_coordinates() const;
    Orientation get_orientation() const;
    uint64_t get_size() const;

private:
    uint64_t size_;
    Orientation orientation_;
    Coordinate start_;
    std::vector<bool> hits_;
};

#endif
