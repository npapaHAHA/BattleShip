#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

enum class CurrentPlayer {
    USER,
    COMPUTER
};

class Game {
public:
    Game();
    std::string process_command(const std::string& command_line);

private:
    bool is_master_;
    bool game_started_;
    bool game_finished_;
    std::unique_ptr<Player> user_player_;
    std::unique_ptr<Player> computer_player_;
    uint64_t width_;
    uint64_t height_;
    std::unordered_map<int, uint64_t> ship_counts_;
    std::string strategy_;
    CurrentPlayer current_player_;
    std::vector<int> required_ship_sizes_;

    std::string user_shot(uint64_t x, uint64_t y);
    std::string computer_shot();
    bool check_victory();
    bool initialize_ships();
    std::string add_user_ship(uint64_t size, char orientation_char, uint64_t x, uint64_t y);
    void print_board() const;
};

#endif // GAME_H
