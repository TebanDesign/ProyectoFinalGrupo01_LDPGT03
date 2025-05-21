// Descripción: Implementación del menú principal del sistema

#include <iostream>
#include "menu.h"
#include "cita.h"
#include "paciente.h"
using namespace std;

void mostrarMenu() {
    int opcion;
    do {
        cout << "\n====== Clínica Dental ======\n";
        cout << "1. Registrar paciente\n";
        cout << "2. Ver pacientes\n";
        cout << "3. Agendar cita\n";
        cout << "4. Ver citas\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarPaciente(); break;
            case 2: mostrarPacientes(); break;
            case 3: agendarCita(); break;
            case 4: mostrarCitas(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}