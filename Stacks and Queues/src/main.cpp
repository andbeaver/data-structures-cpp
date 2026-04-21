#include <iostream>
#include "maze_solver.h"

int main() {
  MazeSolver solver;

  // Load the maze
  if (!solver.load_maze("tests/test3.txt")) {
    std::cerr << "Failed to load maze." << std::endl;
    return 1;
  }

 // Solve the maze
  if (!solver.solve()) {
    std::cerr << "Maze could not be solved." << std::endl;
    return 1;
  }

  // Print the solved maze
  std::cout << "Maze solved successfully!\n" << std::endl;
  solver.print_maze();

  // Save the solved maze to a file
  if (!solver.save_maze("solved/test3.txt")) {
    return 1;
  }

  return 0;
}