#pragma once
#ifndef BOARD
#define BOARD

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
#include <random>
#include <iostream>

class Board
{
private:
	int OpenedTiles, TotalTiles, VideoRes = 0;
	std::vector<Tile> Tiles;
	void generatedBoard();
	void checkSurroundings(int);
	void handleClicks(const sf::Event& event);
	void flush(int);


public:
	Board(int, int);
	std::vector<int> generateBombLocations();
	int SideLength, Bombs = 0;
	void drawTiles();
};

#endif // !BOARD



