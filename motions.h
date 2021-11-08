
#ifndef TURN_H_
#define TURN_H_

#include <vector>

#include "motions.h"
#include "coord.h"

class Game;



class Motion {
public:
  const static int data_len = 30;

  Motion() {}
  Motion(const std::vector<Coord*> coords, const bool eating)
    : coords_(coords), eating_(eating) {
      fillData();
  }
  ~Motion() {}

  void inputCoords();

  bool isCompare(Motion* turn) const;

  char* data() { return data_; }
  std::vector<Coord*> coords() const { return coords_; }
  bool eating() const { return eating_; }

private:
  const char x_min = 'a';
  const char y_min = '1';

  void fillData();

  char data_[data_len];
  std::vector<Coord*> coords_;
  bool eating_;
};

#endif
