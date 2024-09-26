// implementation file for the Board class

#include "Board.h"
#include <cstdlib>
#include <iostream>
#include <raylib.h>

// index for the array of tiles(board) = row * board width + column

// default board constructor
Board::Board() {
  board = new Tile[size];
  for (int i{0}; i < size; i++) {
    board[i] = Tile();
  }
  Board::place_mines();
  Board::update_counts();
  return;
};

// board constructor to change size and mine counts
Board::Board(int height, int width, int m_count) {
  board_width = width;
  board_height = height;
  mine_count = m_count;
  // size as an index so memory can be dynamically allocated using an array.
  size = board_height * board_width + board_width;

  board = new Tile[size];
  // setting each index i of the board as a tile
  for (int i{0}; i < size; i++) {
    board[i] = Tile();
  }
  place_mines();
  update_counts();
}

void Board::place_mines() {
  srand(time(NULL));
  // selects random row and column to place the mines at.
  for (int i{0}; i < mine_count; i++) {
    int rand_row;
    int rand_col;
    rand_row = rand() % (board_height - 1);
    rand_col = rand() % (board_width - 1);
    while (board[rand_row * board_width + rand_col].get_value() == 10) {
      rand_row = rand() % (board_height - 1);
      rand_col = rand() % (board_width - 1);
    }
    board[rand_row * board_width + rand_col].set_value(10);
  }
}

void Board::print() const {
  const int screenWidth = 1000;
  const int screenHeight = 800;
  int rectangle_width = screenWidth / board_width;
  int rectangle_height = screenHeight / board_height;
  int posX = rectangle_width;
  int posY = rectangle_height;
  int counter{0};
  for(int i{0};i < board_height;i ++){
    for(int j{0};j<board_width;j++){
      if(counter % 2 == 0)
        DrawRectangle(posX,posY, rectangle_width, rectangle_height, LIME);
      else
        DrawRectangle(posX,posY, rectangle_width, rectangle_height, DARKGREEN); 
      posX = posX + rectangle_width;
      counter++;
    }
    posY = posY + rectangle_height;
    counter++;
  }
  /* counter is used to mismatch the colors of squares between rows. Or else there would be 
  the same color tiles on top of eachother */ 

  std::cout << "  ";
  for (int i{0}; i < board_width; i++)
    std::cout << "  " << i << " ";
  std::cout << std::endl << "  ";
  for (int i{0}; i < board_width; i++)
    std::cout << "|---";
  std::cout << "|\n";

  for (int i{0}; i < board_height; i++) {
    std::cout << i << " | ";
    for (int j{0}; j < board_width; j++) {
      int idx = i * board_width + j;
      //  if (board[idx].get_value() >= 10)
      //  std::cout << 'M' << " | ";
      // else {
      board[idx].display();
      std::cout << " | ";
      //}
    }
    std::cout << "\n  ";
    for (int i{0}; i < board_width; i++)
      std::cout << "|---";
    std::cout << "|\n";
  }
}

// if tile at column 0 == 0
// then it reveals the tile at last column on the same row
// 3 * board_width + 0

// how to do bounds checking?
// if i == row(0) * board_width + 0
// don't update

void Board::update_counts() {
  for (int i{0}; i < size; i++) {
    if (board[i].get_value() >= 10) {
      if (i == 0) {
        // top left corner
        board[i + 1].set_value(board[i + 1].get_value() + 1);
        board[i + board_height].set_value(board[i + board_height].get_value() + 1);
        board[i + 1 + board_height].set_value(board[i + 1 + board_height].get_value() + 1);
      } else if (i == (board_width - 1)) {
        // top right corner
        board[i - 1].set_value(board[i - 1].get_value() + 1);
        board[i + board_height].set_value(board[i + board_height].get_value() + 1);
        board[i - 1 + board_height].set_value(board[i - 1 + board_height].get_value() + 1);
      } else if (i == (board_height * board_width - board_width)) {
        // bottom left corner
        board[i + 1].set_value(board[i + 1].get_value() + 1);
        board[i - board_height].set_value(board[i - board_height].get_value() +  1);
        board[i + 1 - board_height].set_value(board[i + 1 - board_height].get_value() + 1);
      } else if (i == (board_height * board_width - 1)) {
        // bottom right corner
        board[i - 1].set_value(board[i - 1].get_value() + 1);
        board[i - board_height].set_value(board[i - board_height].get_value() + 1);
        board[i - 1 - board_height].set_value(board[i - 1 - board_height].get_value() + 1);
      } else if ((i % board_width) == 0) {
        // left column
        board[i + 1].set_value(board[i + 1].get_value() + 1);
        board[i + board_height].set_value(board[i + board_height].get_value() +  1);
        board[i - board_height].set_value(board[i - board_height].get_value() + 1);
        board[i + 1 + board_height].set_value(board[i + 1 + board_height].get_value() + 1);
        board[i + 1 - board_height].set_value(board[i + 1 - board_height].get_value() + 1);
      } else if (i >= (board_height * (board_width - 1))) {
        // bottom row
        board[i + 1].set_value(board[i + 1].get_value() + 1);
        board[i - 1].set_value(board[i - 1].get_value() + 1);
        board[i - board_height].set_value(board[i - board_height].get_value() + 1);
        board[i - 1 - board_height].set_value(board[i - 1 - board_height].get_value() + 1);
        board[i + 1 - board_height].set_value(board[i + 1 - board_height].get_value() + 1);
      } else if (i < board_width) {
        // top row
        board[i + 1].set_value(board[i + 1].get_value() + 1);
        board[i - 1].set_value(board[i - 1].get_value() + 1);
        board[i + board_height].set_value(board[i + board_height].get_value() + 1);
        board[i + 1 + board_height].set_value(board[i + 1 + board_height].get_value() + 1);
        board[i - 1 + board_height].set_value(board[i - 1 + board_height].get_value() + 1);
      } else if (((i + 1) % board_width) == 0) {
        // right column
        board[i - 1].set_value(board[i - 1].get_value() + 1);
        board[i + board_height].set_value(board[i + board_height].get_value() + 1);
        board[i - board_height].set_value(board[i - board_height].get_value() + 1);
        board[i - 1 + board_height].set_value(board[i - 1 + board_height].get_value() + 1);
        board[i - 1 - board_height].set_value(board[i - 1 - board_height].get_value() + 1);
      } else {
        // directly adjacent
        board[i + 1].set_value(board[i + 1].get_value() + 1);
        board[i - 1].set_value(board[i - 1].get_value() + 1);
        board[i + board_height].set_value(board[i + board_height].get_value() + 1);
        board[i - board_height].set_value(board[i - board_height].get_value() + 1);
        // 4 more for diagonal
        board[i + 1 + board_height].set_value(board[i + 1 + board_height].get_value() + 1);
        board[i - 1 + board_height].set_value(board[i - 1 + board_height].get_value() + 1);
        board[i - 1 - board_height].set_value(board[i - 1 - board_height].get_value() + 1);
        board[i + 1 - board_height].set_value(board[i + 1 - board_height].get_value() + 1);
      }
    }
  }
}

bool Board::loc_valid(int row, int col) {
  if (row < board_height && col < board_width)
    return true;
  else
    return false;
}

// i think to reveal, will need to create a new function/edit my current function.

void Board::reveal(int row, int col) {
  if (loc_valid(row, col)) {
    int idx = row * board_width + col;
    if (board[idx].get_value() >= 10)
      has_lost = true;
    else {
      if (!board[idx].is_revealed()) {
        board[idx].set_revealed(true);
        revealed_count++;
        reveal_surrounding(idx);
      }
    }
    if (revealed_count == (board_height * board_width - mine_count)) {
      has_won = true;
    }
  }
}

void Board::reveal_surrounding(int i) {

  if (board[i].get_value() == 0) {
    if (i == 0) {
      // top left corner
      if (!board[i + 1].is_revealed()) {
        board[i + 1].set_revealed(true);
        revealed_count++;
        if (board[i + 1].get_value() == 0) {
          reveal_surrounding((i + 1));
        }
      }
      if (!board[i + board_height].is_revealed()) {
        board[i + board_height].set_revealed(true);
        revealed_count++;
        if (board[i + board_height].get_value() == 0) {
          reveal_surrounding((i + board_height));
        }
      }
      if (!board[i + 1 + board_height].is_revealed()) {
        board[i + 1 + board_height].set_revealed(true);
        revealed_count++;
        if (board[i + 1 + board_height].get_value() == 0)
          reveal_surrounding((i + 1 + board_height));
      }
      return;

    }

    else if (i == (board_width - 1)) {
      // top right corner
      if (!board[i - 1].is_revealed()) {
        board[i - 1].set_revealed(true);
        revealed_count++;
        if (board[i - 1].get_value() == 0)
          reveal_surrounding((i - 1));
      }
      if (!board[i + board_height].is_revealed()) {
        board[i + board_height].set_revealed(true);
        revealed_count++;
        if (board[i + board_height].get_value() == 0)
          reveal_surrounding((i + board_height));
      }
      if (!board[i - 1 + board_height].is_revealed()) {
        board[i - 1 + board_height].set_revealed(true);
        revealed_count++;
        if (board[i - 1 + board_height].get_value() == 0)
          reveal_surrounding((i - 1 + board_height));
      }
      return;
    } else if (i == (board_height * board_width - board_width)) {
      // bottom left corner
      if (!board[i + 1].is_revealed()) {
        board[i + 1].set_revealed(true);
        revealed_count++;
        if (board[i + 1].get_value() == 0)
          reveal_surrounding((i + 1));
      }
      if (!board[i - board_height].is_revealed()) {
        board[i - board_height].set_revealed(true);
        revealed_count++;
        if (board[i - board_height].get_value() == 0)
          reveal_surrounding((i - board_height));
      }
      if (!board[i + 1 - board_height].is_revealed()) {
        board[i + 1 - board_height].set_revealed(true);
        revealed_count++;
        if (board[i + 1 - board_height].get_value() == 0)
          reveal_surrounding((i + 1 - board_height));
      }
      return;
    } else if (i == (board_height * board_width - 1)) {
      // bottom right corner
      if (!board[i - 1].is_revealed()) {
        board[i - 1].set_revealed(true);
        revealed_count++;
        if (board[i - 1].get_value() == 0)
          reveal_surrounding((i - 1));
      }
      if (!board[i - board_height].is_revealed()) {
        board[i - board_height].set_revealed(true);
        revealed_count++;
        if (board[i - board_height].get_value() == 0)
          reveal_surrounding((i - board_height));
      }
      if (!board[i - 1 - board_height].is_revealed()) {
        board[i - 1 - board_height].set_revealed(true);
        revealed_count++;
        if (board[i - 1 - board_height].get_value() == 0)
          reveal_surrounding((i - 1 - board_height));
      }
      return;
    } else if ((i % board_width) == 0) {
      // left column
      if (!board[i + 1].is_revealed()) {
        board[i + 1].set_revealed(true);
        revealed_count++;
        if (board[i + 1].get_value() == 0)
          reveal_surrounding((i + 1));
      }
      if (!board[i + board_height].is_revealed()) {
        board[i + board_height].set_revealed(true);
        revealed_count++;
        if (board[i + board_height].get_value() == 0)
          reveal_surrounding((i + board_height));
      }
      if (!board[i - board_height].is_revealed()) {
        board[i - board_height].set_revealed(true);
        revealed_count++;
        if (board[i - board_height].get_value() == 0)
          reveal_surrounding((i - board_height));
      }
      if (!board[i + 1 + board_height].is_revealed()) {
        board[i + 1 + board_height].set_revealed(true);
        revealed_count++;
        if (board[i + 1 + board_height].get_value() == 0)
          reveal_surrounding((i + 1 + board_height));
      }
      if (!board[i + 1 - board_height].is_revealed()) {
        board[i + 1 - board_height].set_revealed(true);
        revealed_count++;
        if (board[i + 1 - board_height].get_value() == 0)
          reveal_surrounding((i + 1 - board_height));
      }
      return;
    } else if (i >= (board_height * (board_width - 1))) {
      // bottom row
      if (!board[i + 1].is_revealed()) {
        board[i + 1].set_revealed(true);
        revealed_count++;
        if (board[i + 1].get_value() == 0)
          reveal_surrounding((i + 1));
      }
      if (!board[i - 1].is_revealed()) {
        board[i - 1].set_revealed(true);
        revealed_count++;
        if (board[i - 1].get_value() == 0)
          reveal_surrounding((i - 1));
      }
      if (!board[i - board_height].is_revealed()) {
        board[i - board_height].set_revealed(true);
        revealed_count++;
        if (board[i - board_height].get_value() == 0)
          reveal_surrounding((i - board_height));
      }
      if (!board[i - 1 - board_height].is_revealed()) {
        board[i - 1 - board_height].set_revealed(true);
        revealed_count++;
        if (board[i - 1 - board_height].get_value() == 0)
          reveal_surrounding((i - 1 - board_height));
      }
      if (!board[i + 1 - board_height].is_revealed()) {
        board[i + 1 - board_height].set_revealed(true);
        revealed_count++;
        if (board[i + 1 - board_height].get_value() == 0)
          reveal_surrounding((i + 1 - board_height));
      }
      return;
    } else if (i < board_width) {
      // top row
      if (!board[i + 1].is_revealed()) {
        board[i + 1].set_revealed(true);
        revealed_count++;
        if (board[i + 1].get_value() == 0)
          reveal_surrounding((i + 1));
      }
      if (!board[i - 1].is_revealed()) {
        board[i - 1].set_revealed(true);
        revealed_count++;
        if (board[i - 1].get_value() == 0)
          reveal_surrounding((i - 1));
      }
      if (!board[i + board_height].is_revealed()) {
        board[i + board_height].set_revealed(true);
        revealed_count++;
        if (board[i + board_height].get_value() == 0)
          reveal_surrounding((i + board_height));
      }
      if (!board[i + 1 + board_height].is_revealed()) {
        board[i + 1 + board_height].set_revealed(true);
        revealed_count++;
        if (board[i + 1 + board_height].get_value() == 0)
          reveal_surrounding((i + 1 + board_height));
      }
      if (!board[i - 1 + board_height].is_revealed()) {
        board[i - 1 + board_height].set_revealed(true);
        revealed_count++;
        if (board[i - 1 + board_height].get_value() == 0)
          reveal_surrounding((i - 1 + board_height));
      }
      return;
    } else if (((i + 1) % board_width) == 0) {
      // right column
      if (!board[i - 1].is_revealed()) {
        board[i - 1].set_revealed(true);
        revealed_count++;
        if (board[i - 1].get_value() == 0)
          reveal_surrounding((i - 1));
      }
      if (!board[i + board_height].is_revealed()) {
        board[i + board_height].set_revealed(true);
        revealed_count++;
        if (board[i + board_height].get_value() == 0)
          reveal_surrounding((i + board_height));
      }
      if (!board[i - board_height].is_revealed()) {
        board[i - board_height].set_revealed(true);
        revealed_count++;
        if (board[i - board_height].get_value() == 0)
          reveal_surrounding((i - board_height));
      }
      if (!board[i - 1 + board_height].is_revealed()) {
        board[i - 1 + board_height].set_revealed(true);
        revealed_count++;
        if (board[i - 1 + board_height].get_value() == 0)
          reveal_surrounding((i - 1 + board_height));
      }
      if (!board[i - 1 - board_height].is_revealed()) {
        board[i - 1 - board_height].set_revealed(true);
        revealed_count++;
        if (board[i - 1 - board_height].get_value() == 0)
          reveal_surrounding((i - 1 - board_height));
      }
      return;
    } else {
      if (!board[i + 1].is_revealed()) {
        board[i + 1].set_revealed(true);
        revealed_count++;
        if (board[i + 1].get_value() == 0)
          reveal_surrounding((i + 1));
      }
      if (!board[i - 1].is_revealed()) {
        board[i - 1].set_revealed(true);
        revealed_count++;
        if (board[i - 1].get_value() == 0)
          reveal_surrounding((i - 1));
      }
      if (!board[i + board_height].is_revealed()) {
        board[i + board_height].set_revealed(true);
        revealed_count++;
        if (board[i + board_height].get_value() == 0)
          reveal_surrounding((i + board_height));
      }
      if (!board[i - board_height].is_revealed()) {
        board[i - board_height].set_revealed(true);
        revealed_count++;
        if (board[i - board_height].get_value() == 0)
          reveal_surrounding((i - board_height));
      }
      if (!board[i + 1 + board_height].is_revealed()) {
        board[i + 1 + board_height].set_revealed(true);
        revealed_count++;
        if (board[i + 1 + board_height].get_value() == 0)
          reveal_surrounding((i + 1 + board_height));
      }
      if (!board[i - 1 + board_height].is_revealed()) {
        board[i - 1 + board_height].set_revealed(true);
        revealed_count++;
        if (board[i - 1 + board_height].get_value() == 0)
          reveal_surrounding((i - 1 + board_height));
      }
      if (!board[i - 1 - board_height].is_revealed()) {
        board[i - 1 - board_height].set_revealed(true);
        revealed_count++;
        if (board[i - 1 - board_height].get_value() == 0)
          reveal_surrounding((i - 1 - board_height));
      }
      if (!board[i + 1 - board_height].is_revealed()) {
        board[i + 1 - board_height].set_revealed(true);
        revealed_count++;
        if (board[i + 1 - board_height].get_value() == 0)
          reveal_surrounding((i + 1 - board_height));
      }
      return;
    }
    return;
  }
}

void Board::display_revealed() const {
  std::cout << "  ";
  for (int i{0}; i < board_width; i++)
    std::cout << "  " << i << " ";
  std::cout << std::endl << "  ";
  for (int i{0}; i < board_width; i++)
    std::cout << "|---";
  std::cout << "|\n";

  for (int i{0}; i < board_height; i++) {
    std::cout << i << " | ";
    for (int j{0}; j < board_width; j++) {
      int idx = i * board_width + j;
      if (board[idx].get_value() >= 10)
        std::cout << 'M' << " | ";
      else {
        board[idx].set_revealed(true);
        board[idx].display();
        std::cout << " | ";
      }
    }
    std::cout << "\n  ";
    for (int i{0}; i < board_width; i++)
      std::cout << "|---";
    std::cout << "|\n";
  }
}

bool Board::did_win() const { return has_won; }
bool Board::did_lost() const { return has_lost; }