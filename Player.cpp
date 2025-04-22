#include "Player.h"
#include "OrderedStrategy.h"
#include "CustomStrategy.h"

Player::Player(Role role, uint64_t width, uint64_t height)
    : role_(role), board_(width, height) {
    strategy_ = std::make_unique<CustomStrategy>(width, height);
}

bool Player::set_strategy(StrategyType type) {
    if (type == StrategyType::ORDERED) {
        strategy_ = std::make_unique<OrderedStrategy>(board_.get_size().first, board_.get_size().second);
    } else if (type == StrategyType::CUSTOM) {
        strategy_ = std::make_unique<CustomStrategy>(board_.get_size().first, board_.get_size().second);
    } else {
        return false;
    }
    return true;
}

std::pair<uint64_t, uint64_t> Player::get_next_shot() {
    return strategy_->get_next_shot();
}

void Player::set_shot_result(const std::string& result) {
    strategy_->set_shot_result(result);
}

Board& Player::get_board() {
    return board_;
}

bool Player::load_board(const std::string& path) {
    return board_.load(path);
}

bool Player::dump_board(const std::string& path) const {
    return board_.dump(path);
}
