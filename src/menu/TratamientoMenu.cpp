#include <iostream>
#include <limits>
#include <string>

#include "menu/TratamientoMenu.h"
#include "modelos/tratamiento.h"
#include "menu/MenuUtils.h"

using namespace std;

void TratamientoMenu::ejecutar() {
    int opcion = -1;
    do {
        MenuUtils::limpiarPantalla();
        MenuUtils::mostrarTitulo("GESTIÓN DE TRATAMIENTOS", MenuUtils::MAGENTA);

        MenuUtils::mostrarOpcion(1, "Registrar tratamiento");
        MenuUtils::mostrarOpcion(2, "Editar tratamiento");
        MenuUtils::mostrarOpcion(3, "Eliminar tratamiento");
        MenuUtils::mostrarOpcion(4, "Buscar por DUI");
        MenuUtils::mostrarSeparador('-', 30, MenuUtils::GRIS);
        MenuUtils::mostrarOpcion(0, "Volver al menú principal");

        opcion = MenuUtils::leerOpcion(0, 4);
        MenuUtils::limpiarPantalla();

        switch (opcion) {
            case 1: registrar(); break;
            case 2: editar(); break;
            case 3: eliminar(); break;
            case 4: buscar(); break;
            case 0:
                MenuUtils::mostrarMensaje("Regresando al menú principal...", MenuUtils::AMARILLO);
                MenuUtils::pausar();
                break;
        }

    } while (opcion != 0);
}

void TratamientoMenu::registrar() {
    Tratamiento t;
    t.registrar();
    MenuUtils::pausar();
}

void TratamientoMenu::editar() {
    string dui, medicamento;
    // cin.ignore(...) eliminado porque MenuUtils::leerOpcion ya limpia el búfer
    cout << "DUI del paciente: "; getline(cin, dui);
    cout << "Medicamento a editar: "; getline(cin, medicamento);
    editarTratamientoEnArchivo(dui, medicamento);
    MenuUtils::pausar();
}

void TratamientoMenu::eliminar() {
    string dui, medicamento;
    // cin.ignore(...) eliminado porque MenuUtils::leerOpcion ya limpia el búfer
    cout << "DUI del paciente: "; getline(cin, dui);
    cout << "Medicamento a eliminar: "; getline(cin, medicamento);
    eliminarTratamientoEnArchivo(dui, medicamento);
    MenuUtils::pausar();
}

void TratamientoMenu::buscar() {
    string dui;
    // cin.ignore(...) eliminado porque MenuUtils::leerOpcion ya limpia el búfer
    cout << "DUI del paciente: "; getline(cin, dui);
    mostrarTratamientosPorDUI(dui);
    MenuUtils::pausar();
}

void TratamientoMenu::listarPorPaciente() {
    buscar();
}