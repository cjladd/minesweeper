#include "Tile.h"
#include <iostream>

Tile::Tile(){
  revealed = false; 
  value = 0;


}

// displays tile value
void Tile::display() {
  if (revealed == true) {
    std::cout << value; // display value
  } else {
    std::cout << '#'; // display #
  }
}

// sets revealed to a bool
void Tile::set_revealed(bool x) { 
  


  revealed = x;
}

bool Tile::is_revealed() const {return revealed;}

// gets value
int Tile::get_value() { return value; }

// sets value to an int
void Tile::set_value(int val) { value = val; }

// Implementation file for the set_revealed and display methods of Tile