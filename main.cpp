#include "Board.h"
#include "Tile.h"
#include "raylib.h"
#include <iostream>

int main() {
  const int screenWidth = 1000;
  const int screenHeight = 800;
  InitWindow(screenWidth, screenHeight, "minesweeper");
  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(RAYWHITE);

    std::cout << "---WELCOME TO MINESWEEPER---\n";
    int rows{0};
    int columns{0};
    int mine_count{0};
    // prompt user to enter given numbers using raylib
    //  int unicode = GetCharPressed();
    while (rows <= 0) {
      DrawRectangle(500, 400, 100, 150, BLACK);
      DrawText("Enter board row count", 500, 400, 10, BLUE);
      rows = GetCharPressed();
      rows = rows - '0';}
      while(columns <= 0) {
      DrawRectangle(500, 400, 100, 150, BLACK);
      DrawText("Enter board column count", 500, 400, 10, BLUE);
      columns = GetCharPressed();
      columns = columns - '0';}
      while(mine_count<=0){
      DrawRectangle(500, 400, 100, 150, BLACK);
      DrawText("Enter mine count", 500, 400, 10, BLUE);
      mine_count = GetCharPressed();
      mine_count = mine_count - '0';
    }
    // Create the Board based on those parameters
    Board play_area2(rows, columns, mine_count);
    // Repeat until the user has either WON or LOST
    while (!play_area2.did_win() && !play_area2.did_lost()) {
      // Display the board (remember the Tile's keep track of whether they have
      // been revealed or not)
      play_area2.print(); // update print to do a background based on the board
                          // size. adjust pixels ratio based on the size(bigger
                          // squares for smaller boards)
      // display values in the layer above the background after updatecounts().
      // after this, cover with the squares the user will see.
      int incol;
      int inrow;
      // receive based on click location
      std::cout << "Enter a row and column to dig: ";
      std::cin >> inrow >> incol;
      // bust open square using raylib.
      // may just have to draw value and background on top of square as there is
      // no good way of removing.
      play_area2.reveal(inrow, incol);
    }
    // After the loop ends determine
    // if the user has won
    if (play_area2.did_win()) {
      std::cout
          << "------------------------------\nCONGRATULATIONS YOU HAVE WON "
             "MINESWEEPER\n------------------------------\nYour final "
             "board was:\n";
      play_area2.print();
    }
    // tell them
    // display the final board without revealing the mines
    // otherwise
    else {
      std::cout << "------------------------------\nOOPS YOU HAVE LOST "
                   "MINESWEEPER\n------------------------------\nYour final "
                   "board was:\n";
      play_area2.display_revealed();
    }
    // tell them they lost
    // display the whole board in a revealed state
    EndDrawing();
  }
  CloseWindow();
}

// raylib algorithm

// bottom layer - background
// layer in front - board background
// layer in front - board values & mines
// layer in front - covered board with colored tiles

// when user clicks a tile - set revealed and run functions
// if user clicks a mine - game over