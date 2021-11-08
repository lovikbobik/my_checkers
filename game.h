#ifndef STATE_H_
#define STATE_H_

#include <vector>
#include "motions.h"
#include "coord.h"

class Motion;


class Game {
public:
  const static int board_size = 8;
  const static int pawn_index = board_size * board_size;
  const static int data_len = pawn_index + 1 + 1;

  Game();
  ~Game() {}

  void createListOfValidMotion();
  void drawBoard() const;

  bool isCheckMathingValidMotion(Motion* turn) const;
  void shiftPawn(Motion* turn);
  void setNextPlayer();
  void setInvalidMotion();
  
  char get_player() const;
  int get_winner() const;

  char* data() { return data_; }

private:
  const static int to_lower = 'a' - 'A';
  const static char possible_space = '.';
  const static char impossible_space = ' ';
  const static char valid_playerW = 'w';
  const static char valid_playerB = 'b';
  const static char invalid_playerW = 'p';
  const static char invalid_playerB = 'y';
  const static char winning_playerW = 'W';
  const static char winning_playerB = 'B';

  void checkValidMotionJump(Coord* coord);
  bool checkValidJump(
    Coord* pre_coord, Coord* new_coord, std::vector<Coord*> coords, bool queen);
  void checkValidMotion(Coord* coord);

  void pushJump(const std::vector<Coord*> coords);
  void pushMove(Coord* pre_coord, Coord* new_coord);

  static bool isValidCoord(const Coord* coord) ;
  bool isOwnPawn(const Coord* coord) const;
  bool isOpponentPawn(const Coord* coord) const;
  bool isPossible(const Coord* coord) const;
  bool isQueen(const Coord* coord) const;

  bool isValidDirection(Coord* pre_coord, Coord* new_coord) const;
  bool isMoveable(Coord* pre_coord, Coord* new_coord) const;
  bool isJumpable(Coord* pre_coord, Coord* new_coord, bool queen) const;
  
  char getOpponent() const;

  void setPlayer(const char player);

  void setPawn(const Coord* coord, const char pawn);
  char getPawn(const Coord* coord) const;

  char data_[data_len]{};
  std::vector<Motion*> valid_motions_;
  bool forced_eating_{};
  int w_count_;
  int b_count_;
};

#endif    // STATE_H_
