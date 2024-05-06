#include "Menu.h"
#include "Board.h"
#include <iostream>

void Menu::run() {
    int choice = 0;
    while (choice != 4) {
        std::cout << "¿Listo para el juego?\n";
        std::cout << "1.- Nivel easy\n";
        std::cout << "2.- Nivel masomenos\n";
        std::cout << "3.- Nivel vergas\n";
        std::cout << "4.- Salir\n";
        std::cin >> choice;
        switch (choice) {
        case 1: {
            Board easy(9, 9);
            break;
        }
        case 2: {
            Board medium(16, 40);
            break;
        }
        case 3: {
            Board hard(20, 80);
            break;
        }
        case 4:
            std::cout << "Bye!\n";
            break;
        default:
            std::cout << "Opcion invalida, nomas del 1-4 \n";
            break;
        }
    }
}
