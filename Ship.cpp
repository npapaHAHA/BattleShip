#include "Ship.h"

Ship::Ship(uint64_t size, Orientation orientation, Coordinate start)
    : size_(size), orientation_(orientation), start_(start), hits_(size, false) {}

bool Ship::contains(const Coordinate& coord) const {
    for (uint64_t i = 0; i < size_; ++i) {
        Coordinate current;
        if (orientation_ == Orientation::HORIZONTAL) {
            current = { start_.x + i, start_.y };
        } else {
            current = { start_.x, start_.y + i };
        }
        if (current.x == coord.x && current.y == coord.y) {
            return true;
        }
    }
    return false;
}

void Ship::hit(const Coordinate& coord) {
    for (uint64_t i = 0; i < size_; ++i) {
        Coordinate current;
        if (orientation_ == Orientation::HORIZONTAL) {
            current = { start_.x + i, start_.y };
        } else {
            current = { start_.x, start_.y + i };
        }
        if (current.x == coord.x && current.y == coord.y) {
            hits_[i] = true;
            break;
        }
    }
}

bool Ship::is_destroyed() const {
    for (bool part_hit : hits_) {
        if (!part_hit) return false;
    }
    return true;
}

std::vector<Coordinate> Ship::get_coordinates() const {
    std::vector<Coordinate> coords;
    for (uint64_t i = 0; i < size_; ++i) {
        if (orientation_ == Orientation::HORIZONTAL) {
            coords.push_back({ start_.x + i, start_.y });
        } else {
            coords.push_back({ start_.x, start_.y + i });
        }
    }
    return coords;
}

Orientation Ship::get_orientation() const {
    return orientation_;
}

uint64_t Ship::get_size() const {
    return size_;
}
