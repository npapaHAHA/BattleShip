#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include "Strategy.h"
#include <memory>
#include <string>

enum class Role {
    MASTER,
    SLAVE
};

enum class StrategyType {
    ORDERED,
    CUSTOM
};

class Player {
public:
    Player(Role role, uint64_t width, uint64_t height);
    bool set_strategy(StrategyType type);
    std::pair<uint64_t, uint64_t> get_next_shot();
    void set_shot_result(const std::string& result);
    Board& get_board();
    bool load_board(const std::string& path);
    bool dump_board(const std::string& path) const;

private:
    Role role_;
    Board board_;
    std::unique_ptr<Strategy> strategy_;
};

#endif
