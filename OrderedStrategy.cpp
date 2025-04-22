#include "OrderedStrategy.h"

OrderedStrategy::OrderedStrategy(uint64_t width, uint64_t height)
    : width_(width), height_(height), current_x_(0), current_y_(0) {}

std::pair<uint64_t, uint64_t> OrderedStrategy::get_next_shot() {
    std::pair<uint64_t, uint64_t> shot = std::make_pair(current_x_, current_y_);
    if (current_x_ + 1 < width_) {
        current_x_++;
    } else {
        current_x_ = 0;
        current_y_++;
        if (current_y_ >= height_) {
            current_y_ = 0;
        }
    }
    return shot;
}

void OrderedStrategy::set_shot_result(const std::string& result) {}
