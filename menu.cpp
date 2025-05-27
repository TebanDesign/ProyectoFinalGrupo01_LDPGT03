// Descripción: Implementación del menú principal del sistema

#include <iostream>
#include "menu.h"
#include "cita.h"
#include "paciente.h"
#include "tratamiento.h"
using namespace std;

void mostrarMenu() {
    int opcion;
    do {
        cout << "\n===== GESTIÓN DE TRATAMIENTOS =====\n";
        cout << "1. Registrar tratamiento\n";
        cout << "2. Mostrar tratamientos por DUI\n";
        cout << "3. Editar tratamiento\n";
        cout << "4. Eliminar tratamiento\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

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

    // return 0;
}