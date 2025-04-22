#include "Board.h"
#include <fstream>
#include <cmath>
#include <iostream>

Board::Board(uint64_t width, uint64_t height)
    : width_(width), height_(height) {}

bool Board::set_size(uint64_t width, uint64_t height) {
    if (width == 0 || height == 0) return false;
    width_ = width;
    height_ = height;
    ships_.clear();
    return true;
}

std::pair<uint64_t, uint64_t> Board::get_size() const {
    return std::pair<uint64_t, uint64_t>(width_, height_);
}

bool Board::add_ship(const Ship& ship) {
    std::vector<Coordinate> coords = ship.get_coordinates();  // Явно указываем тип
    for (std::size_t i = 0; i < coords.size(); ++i) {
        const Coordinate& coord = coords[i];
        if (coord.x >= width_ || coord.y >= height_) {
            return false;
        }
    }
    if (!can_place_ship(ship)) return false;
    ships_.emplace_back(ship);
    return true;
}

bool Board::can_place_ship(const Ship& ship) const {
    std::vector<Coordinate> new_coords = ship.get_coordinates();  // Явно указываем тип
    for (std::size_t i = 0; i < ships_.size(); ++i) {
        const Ship& existing_ship = ships_[i];
        std::vector<Coordinate> existing_coords = existing_ship.get_coordinates();  // Явно указываем тип
        for (std::size_t j = 0; j < new_coords.size(); ++j) {
            const Coordinate& nc = new_coords[j];
            for (std::size_t k = 0; k < existing_coords.size(); ++k) {
                const Coordinate& ec = existing_coords[k];
                if (nc.x == ec.x && nc.y == ec.y) return false;
                if (std::abs(static_cast<int>(nc.x) - static_cast<int>(ec.x)) <= 1 &&
                    std::abs(static_cast<int>(nc.y) - static_cast<int>(ec.y)) <= 1) {
                    return false;
                }
            }
        }
    }
    return true;
}

std::string Board::process_shot(const Coordinate& coord) {
    for (std::size_t i = 0; i < ships_.size(); ++i) {
        Ship& ship = ships_[i];
        if (ship.contains(coord)) {
            ship.hit(coord);
            if (ship.is_destroyed()) return "kill";
            else return "hit";
        }
    }
    return "miss";
}

void Board::reset() {
    ships_.clear();
}

bool Board::load(const std::string& path) {
    std::ifstream infile(path);
    if (!infile.is_open()) return false;

    uint64_t width, height;
    infile >> width >> height;
    if (width == 0 || height == 0) return false;
    set_size(width, height);

    ships_.clear();
    uint64_t size;
    char orientation_char;
    uint64_t x, y;
    while (infile >> size >> orientation_char >> x >> y) {
        Orientation orientation;
        if (orientation_char == 'h') {
            orientation = Orientation::HORIZONTAL;
        } else if (orientation_char == 'v') {
            orientation = Orientation::VERTICAL;
        } else {
            ships_.clear();
            return false;
        }

        Coordinate start = { x, y };
        Ship ship(size, orientation, start);
        if (!add_ship(ship)) {
            ships_.clear();
            return false;
        }
    }
    infile.close();
    return true;
}

bool Board::dump(const std::string& path) const {
    std::ofstream outfile(path);
    if (!outfile.is_open()) return false;

    outfile << width_ << " " << height_ << "\n";
    for (std::size_t i = 0; i < ships_.size(); ++i) {
        const Ship& ship = ships_[i];
        Orientation ori = ship.get_orientation();
        char ori_char = (ori == Orientation::HORIZONTAL) ? 'h' : 'v';
        std::vector<Coordinate> coords = ship.get_coordinates();  // Явно указываем тип
        Coordinate start = coords.front();
        outfile << ship.get_size() << " " << ori_char << " " << start.x << " " << start.y << "\n";
    }
    outfile.close();
    return true;
}

bool Board::all_ships_destroyed() const {
    for (std::size_t i = 0; i < ships_.size(); ++i) {
        const Ship& ship = ships_[i];
        if (!ship.is_destroyed()) return false;
    }
    return true;
}

bool Board::is_ship_at(uint64_t x, uint64_t y) const {
    if (x >= width_ || y >= height_) {
        return false;
    }
    for (std::size_t i = 0; i < ships_.size(); ++i) {
        const Ship& ship = ships_[i];
        if (ship.contains({x, y})) {
            return true;
        }
    }
    return false;
}

const std::vector<Ship>& Board::get_ships() const {
    return ships_;
}

bool Board::has_neighboring_ships(const Ship& ship) const {
    return false;
}
