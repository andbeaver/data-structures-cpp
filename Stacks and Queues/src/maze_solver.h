// MazeSolver class definition for solving a maze using Depth-First Search (DFS) with a stack.

#ifndef ASSIGNMENT_2_MAZE_SOLVER_H
#define ASSIGNMENT_2_MAZE_SOLVER_H

#include <vector>
#include <string>

// Represents a position in the maze
struct Coordinate {
  int row;
  int col;

  Coordinate(int r = -1, int c = -1) : row(r), col(c) {}

  bool operator==(const Coordinate& other) const {
    return row == other.row && col == other.col;
  }
};


class MazeSolver {
  std::vector<std::string> _maze;
  // Start and end points of the maze
  Coordinate _start;
  Coordinate _end;
  // Track visited positions
  std::vector<std::vector<bool>> _visited;
  // Track the path
  std::vector<std::vector<Coordinate>> _parent;

  // Helper methods
  bool is_valid(int row, int col) const;
  bool is_wall(int row, int col) const;
  void find_start_end();
  bool dfs_iterative();

public:
  MazeSolver();

  // Load maze from file
  bool load_maze(const std::string& filename);

  // Solve the maze using DFS with stack
  bool solve();

  // Output the solved maze
  void print_maze() const;
  bool save_maze(const std::string& filename) const;
};

#endif // ASSIGNMENT_2_MAZE_SOLVER_H