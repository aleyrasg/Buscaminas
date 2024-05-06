#pragma once
#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
class Tile
{
public:
    Tile();
    bool isFlagged = false;
    bool isClosed = true;
    sf::RectangleShape Square;
    int BombsAround = 0;
    bool hasBomb = false;
    void highlight();
    void unhighlight();
    void flag();
    void open();
    void click();
};
#endif // TILE_H



