#ifndef CUSTOMSTRATEGY_H
#define CUSTOMSTRATEGY_H

#include "Strategy.h"

class CustomStrategy : public Strategy {
public:
    CustomStrategy(uint64_t width, uint64_t height);
    virtual ~CustomStrategy() {}
    std::pair<uint64_t, uint64_t> get_next_shot() override;
    void set_shot_result(const std::string& result) override;

private:
    uint64_t width_;
    uint64_t height_;
    uint64_t last_shot_x_;
    uint64_t last_shot_y_;
};

#endif
