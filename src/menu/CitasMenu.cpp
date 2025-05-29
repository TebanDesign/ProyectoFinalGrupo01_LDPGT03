#include <iostream>
#include <limits>
#include <iomanip>

#include "menu/CitasMenu.h"
#include "modelos/cita.h"

using namespace std;

CitasMenu::CitasMenu(){}

void CitasMenu::ejecutar() {
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

        switch(opcion) {
            case 1:
                agregarCita();
                break;
            case 2:
                editarCita();
                break;
            case 3:
                listarCitas();
            case 4:
                cout << "Saliendo del modulo Citas..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while(opcion != 5);
}

void CitasMenu::mostrarMenu() {
    cout << "\n====================================" << std::endl;
    cout << "\n===== MENÚ DE GESTIÓN DE CITAS =====" << endl;
    cout << "\n====================================" << std::endl;
    cout << "1. Agregar nueva cita" << endl;
    cout << "2. Editar cita" << endl;
    cout << "3. Listar citas" << endl;
    cout << "4. Salir" << endl;
    cout << "Seleccione una opción: ";
}

void CitasMenu::agregarCita(){
    agendarCita();
}

void CitasMenu::editarCita(){
    cout << "llamar metodos para editar citas..." << endl;
}

void CitasMenu::listarCitas(){
    mostrarCitas();
}
