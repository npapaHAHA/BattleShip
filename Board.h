#ifndef BOARD_H
#define BOARD_H

#include "Ship.h"
#include <vector>
#include <string>

class Board {
public:
    Board(uint64_t width = 10, uint64_t height = 10);
    bool set_size(uint64_t width, uint64_t height);
    std::pair<uint64_t, uint64_t> get_size() const;
    bool add_ship(const Ship& ship);
    bool can_place_ship(const Ship& ship) const;
    std::string process_shot(const Coordinate& coord);
    void reset();
    bool load(const std::string& path);
    bool dump(const std::string& path) const;
    bool all_ships_destroyed() const;
    bool is_ship_at(uint64_t x, uint64_t y) const;
    const std::vector<Ship>& get_ships() const;

private:
    uint64_t width_;
    uint64_t height_;
    std::vector<Ship> ships_;
    std::vector<std::vector<Ship>> board_;
    bool has_neighboring_ships(const Ship& ship) const;
};

#endif
