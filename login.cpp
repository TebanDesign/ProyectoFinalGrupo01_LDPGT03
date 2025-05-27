#include <iostream>
#include <string>
#include <map>
#include <windows.h> // para Sleep
#include <conio.h>   // para _getch()
#include "login.h"

// Función para ocultar la contraseña mientras se escribe, mostrando '*'
std::string obtenerContrasena() {
    std::string pass;
    char ch;
    std::cout << "";

    while (true) {
        ch = _getch(); // lee un carácter sin eco

        if (ch == '\r') { // Enter
            std::cout << std::endl;
            break;
        } 
        else if (ch == '\b') { // Backspace
            if (!pass.empty()) {
                pass.pop_back();
                // Borra el '*' del cursor (retrocede 1 espacio)
                std::cout << "\b \b";
            }
        }
        else if (isprint(ch)) {
            pass.push_back(ch);
            std::cout << '*'; // muestra '*'
        }
        // Ignorar otros caracteres no imprimibles
    }

    return pass;
}

// Validar que usuario y contraseña solo contengan caracteres alfanuméricos (básico)
bool validarCadena(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isalnum(c)) return false;
    }
    return true;
}

bool login() {
    std::map<std::string, std::string> usuarios = {
        {"Hector", "Ortez"},
        {"Rafael", "Diego"},
        {"Luis", "Rivera"},
        {"Eileen", "Rodriguez"},
        {"Teban", "Perez"},
        {"Edwin", "Gonzalez"},
        {"UES", "2025"} // usuario admin
    };

    std::string usuario, contraseña;

    std::cout << "Usuario: ";
    std::getline(std::cin, usuario);

    if (!validarCadena(usuario)) {
        std::cout << "Usuario inválido (vacío o con caracteres no alfanuméricos).\n";
        return false;
    }

    std::cout << "Contraseña: ";
    contraseña = obtenerContrasena();

    if (!validarCadena(contraseña)) {
        std::cout << "Contraseña inválida (vacía o con caracteres no alfanuméricos).\n";
        return false;
    }

    auto it = usuarios.find(usuario);
    if (it != usuarios.end() && it->second == contraseña) {
        return true;
    }
    return false;
}
