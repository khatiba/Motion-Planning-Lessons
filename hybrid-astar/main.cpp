#include <iostream>
#include <fstream>
#include <math.h>
#include <limits>
#include <vector>
#include "hybrid_breadth_first.h"

using namespace std;


int X = 1;
int _ = 0;

double SPEED = 1.45;
double LENGTH = 0.5;

vector<vector<int>> MAZE = {
    {_,X,X,_,_,_,_,_,_,_,X,X,_,_,_,_,},
    {_,X,X,_,_,_,_,_,_,X,X,_,_,_,_,_,},
    {_,X,X,_,_,_,_,_,X,X,_,_,_,_,_,_,},
    {_,X,X,_,_,_,_,X,X,_,_,_,X,X,X,_,},
    {_,X,X,_,_,_,X,X,_,_,_,X,X,X,_,_,},
    {_,X,X,_,_,X,X,_,_,_,X,X,X,_,_,_,},
    {_,X,X,_,X,X,_,_,_,X,X,X,_,_,_,_,},
    {_,X,X,X,X,_,_,_,X,X,X,_,_,_,_,_,},
    {_,X,X,X,_,_,_,X,X,X,_,_,_,_,_,_,},
    {_,X,X,_,_,_,X,X,X,_,_,X,X,X,X,X,},
    {_,X,_,_,_,X,X,X,_,_,X,X,X,X,X,X,},
    {_,_,_,_,X,X,X,_,_,X,X,X,X,X,X,X,},
    {_,_,_,X,X,X,_,_,X,X,X,X,X,X,X,X,},
    {_,_,X,X,X,_,_,X,X,X,X,X,X,X,X,X,},
    {_,X,X,X,_,_,_,_,_,_,_,_,_,_,_,_,},
    {X,X,X,_,_,_,_,_,_,_,_,_,_,_,_,_,},
};

vector<vector<int>> GRID = MAZE;
vector<vector<int>> HEURISTIC = GRID;

vector<double> START = {0.0,0.0,0.0};
vector<int> GOAL = {(int)GRID.size()-1, (int)GRID[0].size()-1};

int main() {

  cout << "Finding path through grid:" << endl;

  for (int i = 0; i < GRID.size(); i++) {
    cout << GRID[i][0];
    for (int j = 1; j < GRID[0].size(); j++) {
      cout << "," << GRID[i][j];
    }
    cout << endl;
  }

  for (int y = 0; y < GRID.size(); y++) {
    for (int x = 0; x < GRID[0].size(); x++) {
      HEURISTIC[y][x] = numeric_limits<int>::max();
    }
  }

  vector<vector<int>> nodes;
  vector<int> start_node = {GOAL[0], GOAL[1], 0};

  nodes.push_back(start_node);

  while (!nodes.empty()) {
    vector<int> node = nodes.back();
    nodes.pop_back();

    int y = node[0];
    int x = node[1];
    int c = node[2];

    HEURISTIC[y][x] = c;

    int ytop = y - 1;
    int ybot = y + 1;
    int xleft = x - 1;
    int xright = x + 1;
    int newc = c + 1;

    if (ytop >= 0 && newc < HEURISTIC[ytop][x]) { // up
      nodes.push_back({ytop, x, newc});
    }

    if (ybot < GRID.size() && newc < HEURISTIC[ybot][x]) { // down
      nodes.push_back({ybot, x, newc});
    }

    if (xleft >= 0 && newc < HEURISTIC[y][xleft]) { // left
      nodes.push_back({y, xleft, newc});
    }

    if (xright < GRID[0].size() && newc < HEURISTIC[y][xright]) { // right
      nodes.push_back({y, xright, newc});
    }
  }

  cout << "HEURISTIC" << endl;

  for (int i = 0; i < GRID.size(); i++) {
    cout << HEURISTIC[i][0];
    for (int j = 1; j < GRID[0].size(); j++) {
      cout << "," << HEURISTIC[i][j];
    }
    cout << endl;
  }

  HBF hbf = HBF();

  HBF::maze_path get_path = hbf.search(GRID,HEURISTIC,START,GOAL);

  vector<HBF::maze_s> show_path = hbf.reconstruct_path(get_path.came_from, START, get_path.final);

  cout << "show path from start to finish" << endl;

  for (int i = show_path.size()-1; i >= 0; i--) {
      HBF::maze_s step = show_path[i];
      cout << "##### step " << step.g << " #####" << endl;
      cout << "x " << step.x << endl;
      cout << "y " << step.y << endl;
      cout << "theta " << step.theta << endl;
  }

  return 0;
}

