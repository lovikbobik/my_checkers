#include "game.h"
#include <iostream>


Game::Game() : w_count_(0), b_count_(0) {
    int index = 0;

    for (int y = 1; y <= board_size; ++y) {
        for (int x = 1; x <= board_size; ++x) {
            if ((x & 1) == (y & 1)) {             
                if (y <= 3) {                       
                    data_[index] = valid_playerW;
                    ++w_count_;
                } else if (y >= 6) {                  
                    data_[index] = valid_playerB;
                    ++b_count_;
                } else {                              
                    data_[index] = possible_space;
                }
            } else {                               
                data_[index] = impossible_space;
            }
            ++index;
        }
    }
    
    data_[index++] = valid_playerW;
    
    data_[index] = '\0';
}

void Game::createListOfValidMotion() {

    valid_motions_.clear();
    forced_eating_ = false;
    
    for (int y = 0; y < board_size; ++y) {
        for (int x = 0; x < board_size; ++x) {
            auto *coord = new Coord(x, y);
            if (isOwnPawn(coord)) {
                checkValidMotionJump(coord);
            }
        }
    }
    
    if (valid_motions_.empty()) {
        char opponent = getOpponent();
        setPlayer(opponent - to_lower);
    }
    
    if (forced_eating_) {
        auto iterator = valid_motions_.begin();
        while (iterator != valid_motions_.end()) {
            if ((*iterator)->eating()) {               
                ++iterator;
            } else {                                      
                iterator = valid_motions_.erase(iterator);
            }
        }
    }
}

void Game::drawBoard() const {
    const char letters[] = "  a b c d e f g h";
    std::cout << letters << "\n";
    int index = board_size * board_size - board_size;
    for (int y = board_size; y > 0; --y) {
        std::cout << y << " ";
        for (int x = 0; x < board_size; ++x) {
            std::cout << data_[index++] << " ";
        }
        std::cout << y << "\n";
        index -= (board_size << 1);
    }
    std::cout << letters << std::endl;
}

bool Game::isCheckMathingValidMotion(Motion *turn) const {
    for (auto valid_turn: valid_motions_) {
        if (valid_turn->isCompare(turn)) {
            return true;
        }
    }
    return false;
}

void Game::shiftPawn(Motion *turn) {
    std::vector<Coord *> coords = turn->coords();
    char player = get_player();
    char pawn = getPawn(coords[0]);
    bool queen = isQueen(coords[0]);
    int last_coord_index = coords.size() - 1;

    setPawn(coords[0], possible_space);

    if (turn->eating()) {
        for (int i = 0; i < last_coord_index; ++i) {
            Coord *mid_coord = coords[i]->Average(coords[i + 1]);
            setPawn(coords[i], possible_space);
            setPawn(mid_coord, possible_space);
        }
    }

    if (player == valid_playerW && coords[last_coord_index]->y == board_size - 1
        || player == valid_playerB && coords[last_coord_index]->y == 0) {
        if (!queen) {
            pawn -= to_lower;
        }
    }

    setPawn(coords[last_coord_index], pawn);
}

void Game::setNextPlayer() {
    if (get_player() == valid_playerW) {
        data_[pawn_index] = valid_playerB;
    } else {
        data_[pawn_index] = valid_playerW;
    }
}

void Game::setInvalidMotion() {
    if (get_player() == valid_playerW) {
        data_[pawn_index] = invalid_playerW;
    } else {
        data_[pawn_index] = invalid_playerB;
    }
}

char Game::get_player() const {
    if (data_[pawn_index] == valid_playerW
        || data_[pawn_index] == invalid_playerW
        || data_[pawn_index] == winning_playerW) {
        return valid_playerW;
    } else {
        return valid_playerB;
    }
}

int Game::get_winner() const {
    if (data_[pawn_index] == winning_playerW) {
        return 1;
    }
    if (data_[pawn_index] == winning_playerB) {
        return 2;
    }
    return 0;
}

void Game::checkValidMotionJump(Coord *coord) {
    std::vector<Coord *> coords;
    coords.push_back(coord);
    bool queen = isQueen(coord);
    Coord *new_coord;

    new_coord = new Coord(coord->x - 2, coord->y - 2);
    checkValidJump(coord, new_coord, coords, queen);
    new_coord = new Coord(coord->x + 2, coord->y - 2);
    checkValidJump(coord, new_coord, coords, queen);
    new_coord = new Coord(coord->x - 2, coord->y + 2);
    checkValidJump(coord, new_coord, coords, queen);
    new_coord = new Coord(coord->x + 2, coord->y + 2);
    checkValidJump(coord, new_coord, coords, queen);

    if (!forced_eating_) {
        checkValidMotion(coord);
    }
}

bool Game::checkValidJump(
        Coord *pre_coord, Coord *new_coord, std::vector<Coord *> coords, bool queen) {
    if (isJumpable(pre_coord, new_coord, queen)) {
        coords.push_back(new_coord);
        bool child = false;
        Coord *next_coord;

        next_coord = new Coord(new_coord->x - 2, new_coord->y - 2);
        if (!pre_coord->Equal(next_coord)) {
            child = checkValidJump(new_coord, next_coord, coords, queen) || child;
        }
        next_coord = new Coord(new_coord->x + 2, new_coord->y - 2);
        if (!pre_coord->Equal(next_coord)) {
            child = checkValidJump(new_coord, next_coord, coords, queen) || child;
        }
        next_coord = new Coord(new_coord->x - 2, new_coord->y + 2);
        if (!pre_coord->Equal(next_coord)) {
            child = checkValidJump(new_coord, next_coord, coords, queen) || child;
        }
        next_coord = new Coord(new_coord->x + 2, new_coord->y + 2);
        if (!pre_coord->Equal(next_coord)) {
            child = checkValidJump(new_coord, next_coord, coords, queen) || child;
        }

        if (!child) {
            forced_eating_ = true;
            pushJump(coords);
        }
        return true;
    } else {
        return false;
    }
}

void Game::checkValidMotion(Coord *coord) {
    Coord *new_coord;

    new_coord = new Coord(coord->x - 1, coord->y - 1);
    if (isMoveable(coord, new_coord)) {
        pushMove(coord, new_coord);
    }
    new_coord = new Coord(coord->x + 1, coord->y - 1);
    if (isMoveable(coord, new_coord)) {
        pushMove(coord, new_coord);
    }
    new_coord = new Coord(coord->x - 1, coord->y + 1);
    if (isMoveable(coord, new_coord)) {
        pushMove(coord, new_coord);
    }
    new_coord = new Coord(coord->x + 1, coord->y + 1);
    if (isMoveable(coord, new_coord)) {
        pushMove(coord, new_coord);
    }
}

void Game::pushJump(const std::vector<Coord *> coords) {
    valid_motions_.push_back(new Motion(coords, true));
}

void Game::pushMove(Coord *pre_coord, Coord *new_coord) {
    std::vector<Coord *> coords;
    coords.push_back(pre_coord);
    coords.push_back(new_coord);
    valid_motions_.push_back(new Motion(coords, false));
}

bool Game::isValidCoord(const Coord *coord) {
    return (coord->x >= 0 && coord->x < board_size
            && coord->y >= 0 && coord->y < board_size);
}

bool Game::isOwnPawn(const Coord *coord) const {
    char player = get_player();
    char pawn = getPawn(coord);

    if (pawn == player || pawn == player - to_lower) {
        return true;
    } else {
        return false;
    }
}

bool Game::isOpponentPawn(const Coord *coord) const {
    char opponent = getOpponent();
    char pawn = getPawn(coord);

    if (pawn == opponent || pawn == opponent - to_lower) {
        return true;
    } else {
        return false;
    }
}

bool Game::isPossible(const Coord *coord) const {
    return getPawn(coord) == possible_space;
}

bool Game::isQueen(const Coord *coord) const {
    char pawn = getPawn(coord);
    return pawn >= 'A' && pawn <= 'Z';
}

bool Game::isValidDirection(Coord *pre_coord, Coord *new_coord) const {
    char player = get_player();
    int stepY = new_coord->y - pre_coord->y;
    if (player == valid_playerW && stepY > 0
        || player == valid_playerB && stepY < 0) {
        return true;
    }
    return false;
}

bool Game::isMoveable(Coord *pre_coord, Coord *new_coord) const {
    if (isValidCoord(new_coord) && isPossible(new_coord)
        && (isValidDirection(pre_coord, new_coord) || isQueen(pre_coord))) {
        return true;
    }
    return false;
}

bool Game::isJumpable(Coord *pre_coord, Coord *new_coord, bool queen) const {
    if (isValidCoord(new_coord) && isPossible(new_coord)
        && (isValidDirection(pre_coord, new_coord) || queen)) {
        Coord *between_coord = pre_coord->Average(new_coord);
        if (isOpponentPawn(between_coord)) {
            return true;
        }
    }
    return false;
}

char Game::getOpponent() const {
    char player = get_player();
    if (player == valid_playerW) {
        return valid_playerB;
    } else {
        return valid_playerW;
    }
}

void Game::setPlayer(const char player) {
    data_[pawn_index] = player;
}

void Game::setPawn(const Coord *coord, const char pawn) {
    data_[coord->y * board_size + coord->x] = pawn;
}

char Game::getPawn(const Coord *coord) const {
    return data_[coord->y * board_size + coord->x];
}
