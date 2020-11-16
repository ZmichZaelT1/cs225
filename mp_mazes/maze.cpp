/* Your code here! */
#include "maze.h"
    void SquareMaze::makeMaze (int width, int height) {
        this->width = width;
        this->height = height;
        int area = width * height;

        dsets.addelements(area);
        maze.resize(area, 3);

        while (dsets.size(0) != area) {
            int cell = rand() % area;
            int path = rand() % 2;

            if (path == 0) {
                if ((cell + 1) % width == 0) {
                    continue;
                } else if (dsets.find(cell) == dsets.find(cell + 1)) {
                    continue;
                } else {
                    dsets.setunion(cell, cell + 1);
                    setWall(cell % width, cell / width , path, false);
                }
            } else if (path == 1) {
                if (cell + width >= area) {
                    continue;
                } else if (dsets.find(cell) == dsets.find(cell + width)) {
                    continue;
                } else {
                    dsets.setunion(cell, cell + width);
                    setWall(cell % width, cell / width , path, false);
                }
            }
        }
    }

    bool SquareMaze::canTravel (int x, int y, int dir) const {
        int i = x + y * width;
        
        switch (dir) {
            case 0:
                return (x < width - 1 && maze.at(i) != 1) && maze.at(i) != 3;
            case 1:
                return (y < height - 1 && maze.at(i) != 2) && maze.at(i) != 3;
            case 2:
                return (x != 0 && maze.at(i - 1) != 1) && maze.at(i - 1) != 3;
            case 3:
                return (y != 0 && maze.at(x + (y - 1) * width) != 2) && maze.at(x + (y - 1) * width) != 3;
        }
        return false;
    }

    void SquareMaze::setWall (int x, int y, int dir, bool exists) {
        int i = x + y * width;
        int cell = maze.at(i);

        if (((!exists && dir == 0) && cell == 1) || ((!exists && dir == 1) && cell == 2)) {
            maze.at(i) = 0;
        } else if (((exists && dir == 0) && cell == 0) || ((!exists && dir == 1) && cell == 3)) {
            maze.at(i) = 1;
        } else if (((exists && dir == 1) && cell == 0) || ((!exists && dir == 0) && cell == 3)) {
            maze.at(i) = 2;
        } else if (((exists && dir == 0) && cell == 2) || ((exists && dir == 1) && cell == 1)) {
            maze.at(i) = 3;
        }
    }

    vector<int> SquareMaze::solveMaze () {
        vector<int> a;
        return a;
    }

    PNG * SquareMaze::drawMaze () const {
        PNG *a = new PNG();
        return a;
    }

    PNG * SquareMaze::drawMazeWithSolution () {
        PNG *a = new PNG();
        return a;
    }