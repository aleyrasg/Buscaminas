#include "Menu.h"
#include "Board.h"
#include <iostream>

void Menu::run() {
    int choice = 0;
    while (choice != 4) {
        std::cout << "Bienvenido al buscaminas\n";
        std::cout << "1.- Nivel facil\n";
        std::cout << "2.- Nivel Intermedio\n";
        std::cout << "3.- Nivel experto\n";
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
            std::cout << "Hasta pronto :)\n";
            break;
        default:
            std::cout << "Opcion no valida\n";
            break;
        }
    }
}
