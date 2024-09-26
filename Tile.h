// header file for the Tile class
#ifndef _TILE_H
#define _TILE_H

class Tile {
private:
  int value;     // mine, count of mines nearby, or 0 if not touching
  bool revealed; // true if the tile has been revealed

public:
  void display(); // displays value of tile if revealed, or # if not
  void set_revealed(bool);
  int get_value();
  void set_value(int value);
  bool is_revealed() const;
  Tile();
};

#endif