#include "motions.h"
#include <sstream>
#include <string>


void Motion::inputCoords() {
  coords_.clear();

  std::istringstream iss(data_);
  std::string token;
  while (iss >> token) {
    auto* coord = new Coord(token[0] - x_min, token[1] - y_min);
    coords_.push_back(coord);
  }
}

bool Motion::isCompare(Motion* turn) const {
  turn->eating_ = eating_;
  std::string str1(data_);
  std::string str2(turn->data());
  return str1 == str2;
}

void Motion::fillData() {
  int coords_size = coords_.size();

  int index = 0;
  for (int i = 0; i < coords_size; ++i) {
    data_[index++] = coords_[i]->x + x_min;
    data_[index++] = coords_[i]->y + y_min;
    data_[index++] = ' ';
  }
  data_[--index] = '\0';
}
