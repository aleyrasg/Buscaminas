#include "Tile.h"

void Tile::TileDesign() {
    Square.setSize(sf::Vector2f(48, 48));
    posy = row * 50;
    posx = column * 50;
    Square.setPosition(posx, posy);
    Square.setFillColor(sf::Color::Blue);
    Square.setOutlineThickness(2);
    Square.setOutlineColor(sf::Color::Black);
}

void Tile::highlight() {
    if (isClosed && !isFlagged)
        Square.setFillColor(sf::Color::Green);
}

void Tile::unhighlight() {
    if (isClosed && !isFlagged)
        Square.setFillColor(sf::Color::Blue);
}

void Tile::flag() {
    if (isFlagged)
        Square.setFillColor(sf::Color::Yellow);
}

void Tile::open() {
    if (hasBomb) {
        Square.setFillColor(sf::Color::Red);
    }
    else {
        Square.setFillColor(sf::Color::White);
    }
    isClosed = false;
}
