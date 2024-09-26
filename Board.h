#ifndef _BOARD_H
#define _BOARD_H

#include "Tile.h"
#include <array>

const int kMaxSize{8};

class Board {
private:
  int mine_count{10};
  void place_mines();
  void update_counts();
  int board_width{8};
  int board_height{8};
  int size = board_height * board_width + board_width;

  bool has_won{false};
  bool has_lost{false};
  int revealed_count{0}; 
  bool loc_valid(int row, int col);

  Tile* board;

public:
  void print() const;
  void reveal(int row, int col);
  void reveal_surrounding(int idx);
  Board();
  Board(int height, int width, int m_count);
  bool did_win() const;
  bool did_lost() const;
  void display_revealed() const;
};

#endif

// header file for the Board class