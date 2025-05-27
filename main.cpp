#include <iostream>
#include <functional>
#include "menu.h"
#include "login.h"
#include <windows.h> // Para Sleep()
#include <limits>     // Para std::numeric_limits

int main() {
    // Necesario para mostrar caracteres UTF-8 en la consola de Windows
    SetConsoleOutputCP(65001);
    
    while (true) {
        std::cout << "=== Login ===\n";
        int intentos = 3;

        while (intentos > 0) {
            if (login()) {
                std::cout << "Login exitoso\n";
                bool continuar = mostrarMenu();
                if (!continuar) {
                    // Regresa al login
                    break;
                }
            } else {
                std::cout << "Usuario o contraseña incorrectos. Intentos restantes: " << --intentos << "\n";
            }
        }

        if (intentos == 0) {
            std::cout << "Demasiados intentos fallidos. Bloqueando sistema 3 segundos...\n";
            Sleep(3000);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpiar buffer
        }
    }

    return 0;
}
