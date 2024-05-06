#pragma once
#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile {
public:
    sf::RectangleShape Square;
    bool hasBomb = false;
    bool isClosed = true, isFlagged = false;
    int BombsAround = 0, posx, posy, row, column;

    void TileDesign();
    void highlight();
    void unhighlight();
    void flag();
    void open();
};

#endif /* TILE_H */




