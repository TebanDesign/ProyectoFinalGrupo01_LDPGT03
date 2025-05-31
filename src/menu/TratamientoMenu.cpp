#include <iostream>
#include <limits>
#include <iomanip>

#include "menu/TratamientoMenu.h"
#include "modelos/tratamiento.h"

using namespace std;

TratamientoMenu::TratamientoMenu(){}

void TratamientoMenu::ejecutar() {
    int opcion;
    do {
        cout << "\n====================================" << std::endl;
        cout << "\n===== MENÚ DE GESTIÓN DE TRATAMIENTO =====" << endl;
        cout << "\n====================================" << std::endl;
        cout << "1. Agregar nuevo tratamiento" << endl;
        cout << "2. Editar tratamiento" << endl;
        cout << "3. Listar Tratamientos" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

        switch (opcion) {
            case 1: {
                Tratamiento t;
                t.registrar();
                break;
            }
            case 2: {
                string dui;
                cin.ignore();
                cout << "Ingrese DUI del paciente: ";
                getline(cin, dui);
                mostrarTratamientosPorDUI(dui);
                break;
            }
            case 3: {
                string dui, med;
                cin.ignore();
                cout << "DUI del paciente: ";
                getline(cin, dui);
                cout << "Nombre del medicamento: ";
                getline(cin, med);
                editarTratamientoEnArchivo(dui, med);
                break;
            }
            case 4: {
                string dui, med;
                cin.ignore();
                cout << "DUI del paciente: ";
                getline(cin, dui);
                cout << "Nombre del medicamento: ";
                getline(cin, med);
                eliminarTratamientoEnArchivo(dui, med);
                break;
            }
            case 0:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}