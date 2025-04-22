#include "Game.h"
#include "Utils.h"
#include "OrderedStrategy.h"
#include "CustomStrategy.h"
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>

Game::Game()
    : is_master_(false), game_started_(false), game_finished_(false),
      width_(10), height_(10), strategy_("custom"), current_player_(CurrentPlayer::USER),
      required_ship_sizes_{1, 2, 3, 4} {
    for (uint64_t size : required_ship_sizes_) {
        ship_counts_[size] = 0;
    }
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Game::print_board() const {
    std::cout << "current board:\n";
    std::pair<uint64_t, uint64_t> board_size = user_player_->get_board().get_size();
    uint64_t w = board_size.first;
    uint64_t h = board_size.second;

    for (uint64_t y = 0; y < h; ++y) {
        for (uint64_t x = 0; x < w; ++x) {
            char cell = '.';
            if (user_player_->get_board().is_ship_at(x, y)) {
                cell = 's';
            }
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::string Game::process_command(const std::string& command_line) {
    std::vector<std::string> tokens = Utils::split(command_line);
    if (tokens.empty()) return "failed\n";

    const std::string& cmd = tokens[0];

    if (cmd == "ping") {
        return "pong\n";
    }
    else if (cmd == "exit") {
        return "ok\n";
    }
    else if (cmd == "create") {
        if (tokens.size() != 2) return "failed\n";
        if (tokens[1] == "master") {
            if (user_player_ || computer_player_) return "failed\n";
            is_master_ = true;
            user_player_ = std::make_unique<Player>(Role::MASTER, width_, height_);
            computer_player_ = std::make_unique<Player>(Role::SLAVE, width_, height_);
            return "ok\n";
        }
        else if (tokens[1] == "slave") {
            if (user_player_ || computer_player_) return "failed\n";
            is_master_ = false;
            user_player_ = std::make_unique<Player>(Role::SLAVE, width_, height_);
            computer_player_ = std::make_unique<Player>(Role::MASTER, width_, height_);
            return "ok\n";
        }
        return "failed\n";
    }
    else if (cmd == "set") {
        if (tokens.size() < 3) return "failed\n";
        if (tokens[1] == "width") {
            if (tokens.size() != 3) return "failed\n";
            if (Utils::is_number(tokens[2])) {
                uint64_t width = std::stoull(tokens[2]);
                if (width == 0) return "failed\n";
                width_ = width;
                if (user_player_) {
                    user_player_->get_board().set_size(width_, user_player_->get_board().get_size().second);
                }
                if (computer_player_) {
                    computer_player_->get_board().set_size(width_, computer_player_->get_board().get_size().second);
                }
                return "ok\n";
            }
        }
        else if (tokens[1] == "height") {
            if (tokens.size() != 3) return "failed\n";
            if (Utils::is_number(tokens[2])) {
                uint64_t height = std::stoull(tokens[2]);
                if (height == 0) return "failed\n";
                height_ = height;
                if (user_player_) {
                    user_player_->get_board().set_size(user_player_->get_board().get_size().first, height_);
                }
                if (computer_player_) {
                    computer_player_->get_board().set_size(user_player_->get_board().get_size().first, height_);
                }
                return "ok\n";
            }
        }
        else if (tokens[1] == "count") {
            if (tokens.size() != 4) return "failed\n";
            if (!Utils::is_number(tokens[3])) return "failed\n";
            int size = std::stoi(tokens[2]);
            uint64_t count = std::stoull(tokens[3]);
            if (size < 1) return "failed\n";
            if (std::find(required_ship_sizes_.begin(), required_ship_sizes_.end(), size) != required_ship_sizes_.end()) {
                if (count < 1) return "failed\n";
            }
            ship_counts_[size] = count;
            return "ok\n";
        }
        else if (tokens[1] == "strategy") {
            if (tokens.size() != 3) return "failed\n";
            if (tokens[2] == "ordered") {
                strategy_ = "ordered";
                if (user_player_) {
                    user_player_->set_strategy(StrategyType::ORDERED);
                }
                if (computer_player_) {
                    computer_player_->set_strategy(StrategyType::ORDERED);
                }
                return "ok\n";
            }
            else if (tokens[2] == "custom") {
                strategy_ = "custom";
                if (user_player_) {
                    user_player_->set_strategy(StrategyType::CUSTOM);
                }
                if (computer_player_) {
                    computer_player_->set_strategy(StrategyType::CUSTOM);
                }
                return "ok\n";
            }
            else {
                return "failed\nsupported strategies: ordered, custom\n";
            }
        }
        return "failed\n";
    }
    else if (cmd == "add_ship") {
        if (tokens.size() != 5) return "failed\n";
        if (!Utils::is_number(tokens[1]) || !Utils::is_number(tokens[3]) || !Utils::is_number(tokens[4])) return "failed\n";
        uint64_t size = std::stoull(tokens[1]);
        char orientation_char = tokens[2][0];
        uint64_t x = std::stoull(tokens[3]);
        uint64_t y = std::stoull(tokens[4]);

        print_board();

        if (ship_counts_.find(size) == ship_counts_.end() || ship_counts_[size] == 0) {
            return "failed\n";
        }
        ship_counts_[size]--;

        Orientation orientation;
        if (orientation_char == 'h') {
            orientation = Orientation::HORIZONTAL;
        }
        else if (orientation_char == 'v') {
            orientation = Orientation::VERTICAL;
        }
        else {
            ship_counts_[size]++;
            return "failed\n";
        }

        Coordinate start = { x, y };
        Ship ship(size, orientation, start);

        if (!user_player_->get_board().can_place_ship(ship)) {
            ship_counts_[size]++;
            return "failed\n";
        }

        user_player_->get_board().add_ship(ship);
        print_board();
        return "ok\n";
    }
    else if (cmd == "start") {
        if (game_started_) return "failed\n";
        if (!user_player_ || !computer_player_) return "failed\n";

        bool user_ready = true;
        for (const uint64_t& size : required_ship_sizes_) {
            bool has_ship = false;
            for (const Ship& ship : user_player_->get_board().get_ships()) {
                if (ship.get_size() == size) {
                    has_ship = true;
                    break;
                }
            }
            if (!has_ship) {
                user_ready = false;
                break;
            }
        }
        if (!user_ready) return "failed\n";

        if (!initialize_ships()) return "failed\n";

        game_started_ = true;
        game_finished_ = false;
        current_player_ = CurrentPlayer::USER;
        return "ok\n";
    }
    else if (cmd == "stop") {
        if (!game_started_) return "failed\n";
        game_started_ = false;
        return "ok\n";
    }
    else if (cmd == "shot") {
        if (!game_started_ || game_finished_) return "failed\n";
        if (tokens.size() == 3) {
            if (!Utils::is_number(tokens[1]) || !Utils::is_number(tokens[2])) return "failed\n";
            uint64_t x = std::stoull(tokens[1]);
            uint64_t y = std::stoull(tokens[2]);
            if (x >= width_ || y >= height_) return "failed\n";
            if (current_player_ != CurrentPlayer::USER) return "failed\n";

            Coordinate coord = { x, y };
            std::string result = computer_player_->get_board().process_shot(coord);
            std::string response = result + "\n";

            if (result == "hit" || result == "kill") {
                if (computer_player_->get_board().all_ships_destroyed()) {
                    game_finished_ = true;
                }
            }
            else {
                current_player_ = CurrentPlayer::COMPUTER;
            }

            return response;
        }
        else if (tokens.size() == 1) {
            if (current_player_ != CurrentPlayer::COMPUTER) return "failed\n";

            std::pair<uint64_t, uint64_t> shot = computer_player_->get_next_shot();
            Coordinate coord = { shot.first, shot.second };
            std::string result = user_player_->get_board().process_shot(coord);
            std::string response = std::to_string(coord.x) + " " + std::to_string(coord.y) + "\n";

            if (result == "hit" || result == "kill") {
                if (user_player_->get_board().all_ships_destroyed()) {
                    game_finished_ = true;
                }
            }
            else {
                current_player_ = CurrentPlayer::USER;
            }

            return response;
        }
        else {
            return "failed\n";
        }
    }
    else if (cmd == "set_result") {
        if (tokens.size() != 3) return "failed\n";
        std::string result = tokens[2];
        if (result != "miss" && result != "hit" && result != "kill") return "failed\n";
        if (current_player_ == CurrentPlayer::USER) {
            computer_player_->set_shot_result(result);
        }
        else {
            user_player_->set_shot_result(result);
        }
        return "ok\n";
    }
    else if (cmd == "finished") {
        if (!game_started_) return "no\n";
        bool finished = check_victory();
        return (finished ? "yes\n" : "no\n");
    }
    else if (cmd == "win") {
        if (!game_started_) return "no\n";
        bool win = false;
        if (is_master_) {
            win = computer_player_->get_board().all_ships_destroyed();
        }
        else {
            win = computer_player_->get_board().all_ships_destroyed();
        }
        return (win ? "yes\n" : "no\n");
    }
    else if (cmd == "lose") {
        if (!game_started_) return "no\n";
        bool lose = false;
        if (is_master_) {
            lose = user_player_->get_board().all_ships_destroyed();
        }
        else {
            lose = user_player_->get_board().all_ships_destroyed();
        }
        return (lose ? "yes\n" : "no\n");
    }
    else if (cmd == "dump") {
        if (tokens.size() != 2) return "failed\n";
        std::string path = tokens[1];
        bool success = user_player_->dump_board(path);
        return (success ? "ok\n" : "failed\n");
    }
    else if (cmd == "load") {
        if (tokens.size() != 2) return "failed\n";
        std::string path = tokens[1];
        bool success = user_player_->load_board(path);
        return (success ? "ok\n" : "failed\n");
    }
    else if (cmd == "get") {
        if (tokens.size() < 2) return "failed\n";
        if (tokens[1] == "width") {
            return std::to_string(width_) + "\n";
        }
        else if (tokens[1] == "height") {
            return std::to_string(height_) + "\n";
        }
        else if (tokens[1] == "count") {
            if (tokens.size() != 3) return "failed\n";
            int size = std::stoi(tokens[2]);
            if (size < 1) return "failed\n";
            return std::to_string(ship_counts_[size]) + "\n";
        }
        return "failed\n";
    }

    return "failed\n";
}

bool Game::initialize_ships() {
    for (const uint64_t& size : required_ship_sizes_) {
        uint64_t count = ship_counts_[size];
        for (uint64_t i = 0; i < count; ++i) {
            bool placed = false;
            while (!placed) {
                Orientation ori = (std::rand() % 2 == 0) ? Orientation::HORIZONTAL : Orientation::VERTICAL;
                uint64_t x = std::rand() % width_;
                uint64_t y = std::rand() % height_;
                Coordinate start = { x, y };
                Ship ship(size, ori, start);
                if (computer_player_->get_board().can_place_ship(ship)) {
                    computer_player_->get_board().add_ship(ship);
                    placed = true;
                }
            }
        }
    }
    return true;
}

bool Game::check_victory() {
    if (computer_player_->get_board().all_ships_destroyed()) {
        return true;
    }
    if (user_player_->get_board().all_ships_destroyed()) {
        return true;
    }
    return false;
}