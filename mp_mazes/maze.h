/* Your code here! */
#pragma once
#include "cs225/PNG.h"
#include <vector>

using namespace std;
using namespace cs225;

class SquareMaze {
    private:
    public:
        void makeMaze (int width, int height);
        bool canTravel (int x, int y, int dir) const;
        void setWall (int x, int y, int dir, bool exists);
        vector< int > solveMaze ();
        PNG * drawMaze ()const; 
        PNG * drawMazeWithSolution ();		
};