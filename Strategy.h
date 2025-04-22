#ifndef STRATEGY_H
#define STRATEGY_H

#include "Ship.h"
#include <utility>
#include <string>

class Strategy {
public:
    virtual ~Strategy() {}
    virtual std::pair<uint64_t, uint64_t> get_next_shot() = 0;
    virtual void set_shot_result(const std::string& result) = 0;
};

#endif
