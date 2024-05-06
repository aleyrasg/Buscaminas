#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Tile.h"

class Board {
public:
    int TilesPerSide, bombs, TotalTiles, videores, openedTiles = 0;
    std::vector<Tile> TileBoard;

    Board(int aux, int bombs);
    void flush(int TileNumber);
    void drawTiles();
    void checkAround(int TileNumber);
    void assignBombs(int TotalTiles, int bombs, std::vector<int>& AssignedBombs);
};

#endif /* BOARD_H */
