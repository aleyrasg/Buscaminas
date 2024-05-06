#include "Board.h"

Board::Board(int sideLength, int bombs) : SideLength(sideLength), Bombs(bombs) {
    TotalTiles = SideLength * SideLength;
    VideoRes = SideLength * 50;
    Tiles.resize(TotalTiles);
    generatedBoard();
    drawTiles();
}

void Board::generatedBoard()
{
    std::vector<int> bombLocations = generateBombLocations();

    for (int i = 0; i < TotalTiles; ++i) {
        Tiles[i].hasBomb = std::binary_search(bombLocations.begin(), bombLocations.end(), i);
        checkSurroundings(i);
    }
}

std::vector<int> Board::generateBombLocations()
{
    std::vector<int> bombLocations(Bombs);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, TotalTiles - 1);

    for (int i = 0; i < Bombs; ++i) {
        int random_number;
        do {
            random_number = dis(gen);
        } while (std::find(bombLocations.begin(), bombLocations.end(), random_number) != bombLocations.end());
        bombLocations[i] = random_number;
    }
    std::sort(bombLocations.begin(), bombLocations.end());
    return bombLocations;
}

void Board::checkSurroundings(int tileNumber) {
    int row = tileNumber / SideLength;
    int column = tileNumber % SideLength;

    for (int i = std::max(column - 1, 0); i < std::min(column + 2, SideLength); ++i) {
        for (int j = std::max(row - 1, 0); j < std::min(row + 2, SideLength); ++j) {
            if (i == column && j == row)
                continue;

            int neighborIndex = j * SideLength + i;
            if (Tiles[neighborIndex].hasBomb)
                Tiles[tileNumber].BombsAround++;
        }
    }
}

void Board::drawTiles()
{
    sf::RenderWindow window(sf::VideoMode(VideoRes, VideoRes), "Buscaminas");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
                handleClicks(event);
        }

        window.clear();
        for (const auto& tile : Tiles)
            window.draw(tile.Square);
        window.display();
    }
}

void Board::handleClicks(const sf::Event& event) {
    sf::Vector2i localPosition = sf::Mouse::getPosition();
    int mouseX = localPosition.x / 50;
    int mouseY = localPosition.y / 50;
    int tileUnderMouse = mouseY * SideLength + mouseX;

    if (event.mouseButton.button == sf::Mouse::Right && Tiles[tileUnderMouse].isClosed) {
        Tiles[tileUnderMouse].isFlagged = !Tiles[tileUnderMouse].isFlagged;
        Tiles[tileUnderMouse].flag();
    }
    else if (event.mouseButton.button == sf::Mouse::Left && !Tiles[tileUnderMouse].isFlagged) {
        Tiles[tileUnderMouse].click();
        OpenedTiles++;
        if (Tiles[tileUnderMouse].BombsAround == 0 && !Tiles[tileUnderMouse].hasBomb)
            flush(tileUnderMouse);
        if (OpenedTiles == (TotalTiles - Bombs))
            std::cout << "¡Felicidades!" << std::endl;
    }
}
void Board::flush(int tileNumber) {
    int row = tileNumber / SideLength;
    int column = tileNumber % SideLength;

    for (int i = std::max(column - 1, 0); i < std::min(column + 2, SideLength); ++i) {
        for (int j = std::max(row - 1, 0); j < std::min(row + 2, SideLength); ++j) {
            int neighborIndex = j * SideLength + i;
            if (Tiles[neighborIndex].isClosed) {
                Tiles[neighborIndex].click();
                OpenedTiles++;
                if (Tiles[neighborIndex].BombsAround == 0 && !Tiles[neighborIndex].hasBomb)
                    flush(neighborIndex);
            }
        }
    }
}