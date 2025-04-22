#include "CustomStrategy.h"

CustomStrategy::CustomStrategy(uint64_t width, uint64_t height)
    : width_(width), height_(height), last_shot_x_(0), last_shot_y_(0) {}

std::pair<uint64_t, uint64_t> CustomStrategy::get_next_shot() {
    std::pair<uint64_t, uint64_t> shot = std::make_pair(last_shot_x_, last_shot_y_);
    if (last_shot_x_ + 1 < width_) {
        last_shot_x_++;
    } else {
        last_shot_x_ = 0;
        last_shot_y_++;
        if (last_shot_y_ >= height_) {
            last_shot_y_ = 0;
        }
    }
    return shot;
}

void CustomStrategy::set_shot_result(const std::string& result) {}
