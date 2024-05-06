#include "Menu.h"
#include <iostream>
#include "Board.h"

 void Menu::run()
{
    int choice = 0;
    while (choice != 4) {
        system("cls");
        std::cout << "¿Listo para el juego?\n";
        std::cout << "Selecciona tu nivel de dificultad:\n";
        std::cout << "1.- Nivel facil\n";
        std::cout << "2.- Nivel masomenos\n";
        std::cout << "3.- Nivel vergas\n";
        std::cout << "4.- Salir\n";
        std::cin >> choice;
        switch (choice) {
        case 1:
            playGayme(9, 9);
            break;
        case 2:
            playGayme(16, 40);
            break;
        case 3:
            playGayme(20, 80);
            break;
        case 4:
            std::cout << "Bye!\n";
            break;
        default:
            std::cout << "Opcion invalida, es nomas del 1-4 wey\n";
            system("pause");
            break;
        }
    }
}

 void Menu::playGayme(int sideLength, int bombs) {
     Board game(sideLength, bombs);
 }

