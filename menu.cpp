// Descripción: Implementación del menú principal del sistema

#include <iostream>
#include "menu.h"
#include "cita.h"
#include "paciente.h"

#include <functional>
#include <windows.h>
using namespace std;

bool mostrarMenu() {
    int opcion;
    SetConsoleOutputCP(65001);
    do {
        cout << "\n====== Clínica Dental ======\n";
        cout << "1. Registrar paciente\n";
        cout << "2. Ver pacientes\n";
        cout << "3. Agendar cita\n";
        cout << "4. Ver citas\n";
        cout << "0. Cerrar Sesión\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarPaciente(); break;
            case 2: mostrarPacientes(); break;
            case 3: agendarCita(); break;
            case 4: mostrarCitas(); break;
            case 0: 
                cout << "Regresando al login...\n";
                return false;  // Para salir del menú y volver al login
            default: cout << "Opción inválida.\n";
        }
    } while (true);
}
