// MazeSolver class implementation for solving mazes using depth first search traversal

#include "maze_solver.h"
#include "stack.h"
#include <fstream>
#include <iostream>

MazeSolver::MazeSolver() : _start(-1, -1), _end(-1, -1) {}

// Load maze from file into memory
bool MazeSolver::load_maze(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return false;
  }

  _maze.clear();
  std::string line;
  // Read maze line by line
  while (std::getline(file, line)) {
    _maze.push_back(line);
  }
  file.close();

  // Validate maze structure
  if (_maze.empty()) {
    std::cerr << "Error: Maze is empty" << std::endl;
    return false;
  }

  // Initialize visited grid
  _visited.assign(_maze.size(), std::vector<bool>(_maze[0].size(), false));

  // Find start and end points
  find_start_end();

  return true;
}

// Check if position is within maze boundaries
bool MazeSolver::is_valid(int row, int col) const {
  return row >= 0 && row < static_cast<int>(_maze.size()) &&
         col >= 0 && col < static_cast<int>(_maze[row].size());
}

// Check if position is a wall character
bool MazeSolver::is_wall(int row, int col) const {
  if (!is_valid(row, col)) return true;
  char cell = _maze[row][col];
  return cell == '+' || cell == '-' || cell == '|';
}

// Find start and end points by scanning maze edges
void MazeSolver::find_start_end() {
  // Scan top and bottom edges for openings
  for (int col = 0; col < static_cast<int>(_maze[0].size()); col++) {
    // Top edge
    if (is_valid(0, col) && !is_wall(0, col)) {
      if (_start.row == -1) {
        _start = Coordinate(0, col);
      } else {
        _end = Coordinate(0, col);
        return;
      }
    }
    // Bottom edge
    int last_row = _maze.size() - 1;
    if (is_valid(last_row, col) && !is_wall(last_row, col)) {
      if (_start.row == -1) {
        _start = Coordinate(last_row, col);
      } else {
        _end = Coordinate(last_row, col);
        return;
      }
    }
  }

  // Scan left and right edges for openings
  for (int row = 0; row < static_cast<int>(_maze.size()); row++) {
    // Left edge
    if (is_valid(row, 0) && !is_wall(row, 0)) {
      if (_start.row == -1) {
        _start = Coordinate(row, 0);
      } else {
        _end = Coordinate(row, 0);
        return;
      }
    }
    // Right edge
    int last_col = _maze[row].size() - 1;
    if (is_valid(row, last_col) && !is_wall(row, last_col)) {
      if (_start.row == -1) {
        _start = Coordinate(row, last_col);
      } else {
        _end = Coordinate(row, last_col);
        return;
      }
    }
  }
}

// Perform iterative Depth First Search using custom Stack to find path from start to end
bool MazeSolver::dfs_iterative() {
  // Initialize parent tracking grid
  _parent.assign(_maze.size(), std::vector<Coordinate>(_maze[0].size(), Coordinate(-1, -1)));

  // Create a stack for DFS traversal
  Stack<Coordinate> stack;
  stack.push(_start);
  _visited[_start.row][_start.col] = true;

  // Directions: up, down, left, right
  int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  // Perform iterative DFS using custom Stack
  while (!stack.empty()) {
    auto current_opt = stack.top();
    if (!current_opt.has_value()) break;

    Coordinate current = current_opt.value();
    stack.pop();

    // Check if we reached the end
    if (current == _end) {
      return true;
    }

    // Explore all four directions
    for (auto& dir : directions) {
      Coordinate next(current.row + dir[0], current.col + dir[1]);

      // Check if next position is valid and not visited
      if (is_valid(next.row, next.col) &&
          !_visited[next.row][next.col] &&
          !is_wall(next.row, next.col)) {

        _visited[next.row][next.col] = true;
        _parent[next.row][next.col] = current;
        stack.push(next);
      }
    }
  }

  return false;
}

// Solve the maze and mark the solution path
bool MazeSolver::solve() {
  if (_start.row == -1 || _end.row == -1) {
    std::cerr << "Error: Start or end point not found" << std::endl;
    return false;
  }

  // Run iterative DFS using custom Stack
  if (!dfs_iterative()) {
    std::cerr << "No path found!" << std::endl;
    return false;
  }

  // Reconstruct path from end to start using parent tracking
  std::vector<Coordinate> path;
  Coordinate current = _end;
  while (!(current == _start)) {
    path.push_back(current);
    current = _parent[current.row][current.col];

    // Prevent infinite loop
    if (current.row == -1 && current.col == -1) {
      std::cerr << "Error: Path reconstruction failed" << std::endl;
      return false;
    }
  }
  path.push_back(_start);

  // Mark the path in the maze with '#' (excluding start and end)
  for (const auto& coord : path) {
    _maze[coord.row][coord.col] = '#';
  }

  return true;
}

// Print the maze to console
void MazeSolver::print_maze() const {
  for (const auto& row : _maze) {
    std::cout << row << std::endl;
  }
}

// Save the solved maze to a file
bool MazeSolver::save_maze(const std::string& filename) const {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << filename << " for writing" << std::endl;
    return false;
  }

  for (const auto& row : _maze) {
    file << row << std::endl;
  }
  file.close();

  std::cout << "Maze saved to " << filename << std::endl;
  return true;
}