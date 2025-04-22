#ifndef ORDEREDSTRATEGY_H
#define ORDEREDSTRATEGY_H

#include "Strategy.h"

class OrderedStrategy : public Strategy {
public:
    OrderedStrategy(uint64_t width, uint64_t height);
    virtual ~OrderedStrategy() {}
    std::pair<uint64_t, uint64_t> get_next_shot() override;
    void set_shot_result(const std::string& result) override;

private:
    uint64_t width_;
    uint64_t height_;
    uint64_t current_x_;
    uint64_t current_y_;
};

#endif
