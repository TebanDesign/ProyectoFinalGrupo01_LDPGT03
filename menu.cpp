// Descripción: Implementación del menú principal del sistema

#include <iostream>
#include "menu.h"
#include "cita.h"
#include "paciente.h"

#include "inventario.h" // Incluyo el archivo de inventario.h

using namespace std;

// Menú del módulo de inventario
void mostrarMenuInventario() {
    int op;
    do {
        cout << "\n=== Inventario de Medicamentos ===\n";
        cout << "1. Agregar nuevo medicamento\n";
        cout << "2. Mostrar inventario\n";
        cout << "3. Editar medicamento\n";
        cout << "4. Agregar stock a un medicamento\n";
        cout << "5. Descontar stock de un medicamento\n";
        cout << "0. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> op;
        cin.ignore(); // Limpiar el buffer

        string nombre;
        int cantidad;
        switch(op) {
            case 1:
                agregarMedicamento();
                break;
            case 2:
                mostrarInventario();
                break;
            case 3:
                editarMedicamento();
                break;
            case 4:
                cout << "Ingrese el nombre del medicamento: ";
                getline(cin, nombre);
                cout << "Ingrese la cantidad a agregar: ";
                cin >> cantidad;
                cin.ignore();
                if(agregarStock(nombre, cantidad))
                    cout << "Stock agregado.\n";
                else
                    cout << "No se encontró el medicamento.\n";
                break;
            case 5:
                cout << "Ingrese el nombre del medicamento: ";
                getline(cin, nombre);
                cout << "Ingrese la cantidad a descontar: ";
                cin >> cantidad;
                cin.ignore();
                if(descontarMedicamento(nombre, cantidad))
                    cout << "Stock descontado.\n";
                else
                    cout << "No se encontró el medicamento o stock insuficiente.\n";
                break;
            case 0:
                cout << "Volviendo al menú principal...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while(op != 0);
}


// Menú principal del sistema
void mostrarMenu() {
    int opcion;
    do {
        cout << "\n====== Clínica Dental ======\n";
        cout << "1. Registrar paciente\n";
        cout << "2. Ver pacientes\n";
        cout << "3. Agendar cita\n";
        cout << "4. Ver citas\n";
        cout << "5. Módulo de Inventario\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarPaciente(); break;
            case 2: mostrarPacientes(); break;
            case 3: agendarCita(); break;
            case 4: mostrarCitas(); break;
            case 5: mostrarMenuInventario(); break; // Llamada al menú de inventario
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}