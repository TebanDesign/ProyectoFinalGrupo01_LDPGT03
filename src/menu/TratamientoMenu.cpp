#include <iostream>
#include <limits>
#include <string>

#include "menu/TratamientoMenu.h"
#include "modelos/tratamiento.h"
#include "menu/MenuUtils.h"

using namespace std;

// Método principal que muestra el menú de tratamientos y gestiona las opciones
void TratamientoMenu::ejecutar() {
    int opcion = -1;
    do {
        // Limpia pantalla y muestra el título del módulo
        MenuUtils::limpiarPantalla();
        MenuUtils::mostrarTitulo("GESTIÓN DE TRATAMIENTOS", MenuUtils::MAGENTA);

        // Opciones disponibles
        MenuUtils::mostrarOpcion(1, "Registrar tratamiento");
        MenuUtils::mostrarOpcion(2, "Editar tratamiento");
        MenuUtils::mostrarOpcion(3, "Buscar por DUI");
        MenuUtils::mostrarSeparador('-', 30, MenuUtils::GRIS);
        MenuUtils::mostrarOpcion(0, "Volver al menú principal");

        // Leer la opción ingresada por el usuario
        opcion = MenuUtils::leerOpcion(0, 3);
        // Limpia pantalla antes de ejecutar la acción correspondiente
        MenuUtils::limpiarPantalla();

        // Ejecuta la opción seleccionada
        switch (opcion) {
            case 1: registrar(); break;
            case 2: editar(); break;
            case 3: buscar(); break;
            case 0:
                MenuUtils::mostrarMensaje("Regresando al menú principal...", MenuUtils::AMARILLO);
                MenuUtils::pausar();
                break;
        }

    } while (opcion != 0); // Repite hasta que el usuario elija salir
}

// Registro de nuevo tratamiento
void TratamientoMenu::registrar() {
    Tratamiento t;
    t.registrar();
    MenuUtils::pausar();
}

// Edición de tratamiento existente
void TratamientoMenu::editar() {
    string dui, medicamento;
    cout << "DUI del paciente: "; getline(cin, dui);
    cout << "Medicamento a editar: "; getline(cin, medicamento);
    editarTratamientoEnArchivo(dui, medicamento);
    MenuUtils::pausar();
}

// Buscar y mostrar tratamientos por DUI
void TratamientoMenu::buscar() {
    string dui;
    cout << "DUI del paciente: "; getline(cin, dui);
    mostrarTratamientosPorDUI(dui);
    MenuUtils::pausar();
}