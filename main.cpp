// Descripción: Punto de entrada del sistema, contiene el menú principal.
#include "menu.h"

#include <locale> 
#ifdef _WIN32
#include <windows.h>  // Libreria necesaria para tildes
#endif

using namespace std;

void configurarConsola() {
    #ifdef _WIN32
        SetConsoleOutputCP(65001);  // setea UTF-8 en Windows
        SetConsoleCP(65001);
    #else
        setlocale(LC_ALL, "es_ES.UTF-8");  // Linux/Mac, Espero que funcione porque no tengo linux para probarlo xd
    #endif
}

int main() {
    configurarConsola(); 
    mostrarMenu();
    return 0;
}