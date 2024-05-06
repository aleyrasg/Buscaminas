#include "Board.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <algorithm>

Board::Board(int aux, int bombs) : TilesPerSide(aux), bombs(bombs) {
    videores = TilesPerSide * 50;
    TotalTiles = TilesPerSide * TilesPerSide;
    TileBoard.resize(TotalTiles);

    std::vector<int> AssignedBombs;
    assignBombs(TotalTiles, bombs, AssignedBombs);

    for (int i = 0; i < TilesPerSide; i++) {
        for (int j = 0; j < TilesPerSide; j++) {
            int counter = i * TilesPerSide + j;
            TileBoard[counter].column = j;
            TileBoard[counter].row = i;
            if (std::find(AssignedBombs.begin(), AssignedBombs.end(), counter) != AssignedBombs.end()) {
                TileBoard[counter].hasBomb = true;
            }
            TileBoard[counter].TileDesign();
        }
    }

    for (int i = 0; i < TotalTiles; i++) {
        checkAround(i);
    }
    drawTiles();
}

void Board::flush(int TileNumber) {
    for (int i = std::max(TileBoard[TileNumber].column - 1, 0); i < std::min(TileBoard[TileNumber].column + 2, TilesPerSide); i++) {
        for (int j = std::max(TileBoard[TileNumber].row - 1, 0); j < std::min(TileBoard[TileNumber].row + 2, TilesPerSide); j++) {
            int neighborIndex = j * TilesPerSide + i;
            if (TileBoard[neighborIndex].isClosed) {
                TileBoard[neighborIndex].open();
                if (TileBoard[neighborIndex].BombsAround == 0 && !TileBoard[neighborIndex].hasBomb)
                    flush(neighborIndex);
            }
        }
    }
}

void Board::drawTiles() {
    sf::RenderWindow window(sf::VideoMode(videores, videores), "Buscaminas :)");
    int TileUnderMouse = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            int mouseX = localPosition.x / 50;
            int mouseY = localPosition.y / 50;

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right && TileBoard[TileUnderMouse].isClosed) {
                    TileBoard[TileUnderMouse].isFlagged = !TileBoard[TileUnderMouse].isFlagged;
                    TileBoard[TileUnderMouse].flag();
                }
                else if (event.mouseButton.button == sf::Mouse::Left) {
                    if (!TileBoard[TileUnderMouse].isFlagged) {
                        TileBoard[TileUnderMouse].open();
                        if (TileBoard[TileUnderMouse].hasBomb) {
                            std::cout << "Perdiste Loser" << std::endl;
                            window.close();
                            return;
                        }
                        if (TileBoard[TileUnderMouse].BombsAround == 0 && !TileBoard[TileUnderMouse].hasBomb)
                            flush(TileUnderMouse);
                        openedTiles = std::count_if(TileBoard.begin(), TileBoard.end(), [](const Tile& t) { return !t.isClosed && !t.hasBomb; });

                        if (openedTiles == (TotalTiles - bombs)) {
                            std::cout << "¡Felicidades! " << std::endl;
                            window.close();
                        }
                    }
                }
            }

            for (int i = 0; i < TotalTiles; i++) {
                if (mouseY == TileBoard[i].row && mouseX == TileBoard[i].column) {
                    TileBoard[i].highlight();
                    TileUnderMouse = i;
                }
                else {
                    TileBoard[i].unhighlight();
                }
            }

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        for (int i = 0; i < TotalTiles; i++) {
            window.draw(TileBoard[i].Square);
        }
        window.display();
    }
}

void Board::checkAround(int TileNumber) {
    for (int i = std::max(TileBoard[TileNumber].column - 1, 0); i < std::min(TileBoard[TileNumber].column + 2, TilesPerSide); i++) {
        for (int j = std::max(TileBoard[TileNumber].row - 1, 0); j < std::min(TileBoard[TileNumber].row + 2, TilesPerSide); j++) {
            int neighborIndex = j * TilesPerSide + i;
            if (i != TileBoard[TileNumber].column || j != TileBoard[TileNumber].row) {
                if (TileBoard[neighborIndex].hasBomb) {
                    TileBoard[TileNumber].BombsAround++;
                }
            }
        }
    }
}

void Board::assignBombs(int TotalTiles, int bombs, std::vector<int>& AssignedBombs) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, TotalTiles - 1);

    for (int i = 0; i < bombs; i++) {
        int random_number;
        do {
            random_number = dis(gen);
        } while (std::find(AssignedBombs.begin(), AssignedBombs.end(), random_number) != AssignedBombs.end());
        AssignedBombs.push_back(random_number);
    }
    std::sort(AssignedBombs.begin(), AssignedBombs.end());
}
