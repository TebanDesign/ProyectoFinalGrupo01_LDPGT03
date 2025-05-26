#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm> 

#include "PacienteMenu.h"
#include "Validaciones.h"

using namespace std;

PacienteMenu::PacienteMenu(PacienteServicio& servicio) : servicio(servicio) {}

void PacienteMenu::ejecutar() {
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpiar buffer

        switch(opcion) {
            case 1:
                agregarPaciente();
                break;
            case 2:
                editarPaciente();
                break;
            case 3:
                buscarPaciente();
                break;
            case 4:
                listarPacientes();
                break;
            case 5:
                cout << "Saliendo del modulo Pacientes..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while(opcion != 5);
}

void PacienteMenu::mostrarMenu() {
    cout << "\n====================================" << std::endl;
    cout << "\n=== MENÚ DE GESTIÓN DE PACIENTES ===" << endl;
    cout << "\n====================================" << std::endl;
    cout << "1. Agregar nuevo paciente" << endl;
    
    if(servicio.archivoTieneDatos()){
        cout << "2. Editar paciente existente" << endl;
        cout << "3. Buscar paciente por DUI" << endl;
        cout << "4. Listar todos los pacientes" << endl;
    }

    cout << "5. Salir" << endl;
    cout << "Seleccione una opción: ";
}

void PacienteMenu::agregarPaciente() {
    cout << "\n--- AGREGAR NUEVO PACIENTE ---" << endl;

    string nombre, dui, fechaNacimiento, genero, comentarios;

    cout << "Nombre completo: ";
    getline(cin, nombre);

    cout << "DUI (00000000-0): ";
    getline(cin, dui);

    bool esDuiValido = Validaciones::validarDUI(dui);

    while (!esDuiValido) {
        cout << "Por favor ingrese un DUI valido";
        cout << "DUI: (00000000-0): ";

        getline(cin, dui);

        esDuiValido = Validaciones::validarDUI(dui);
    }


    do {
        cout << "Género (M/F): ";
        getline(cin, genero);
        
        if (!genero.empty()) {
            string generoLower = genero;
            transform(generoLower.begin(), generoLower.end(), generoLower.begin(), ::tolower);
            
            if (generoLower == "m" || generoLower == "f") {
                genero = generoLower;
                break;
            } else {
                cout << "Entrada inválida. Ingrese 'M' o 'F'\n";
            }
        }
    } while (!genero.empty());


    do {
        cout << "Fecha de nacimiento (DD/MM/AAAA): ";
        getline(cin, fechaNacimiento);
        
        if (fechaNacimiento.empty()) {
            cout << "\nLa fecha de nacimiento es obligatoria.\n";
        } else if (!Validaciones::validarFecha(fechaNacimiento)) {
            cout << "\nFecha inválida. Por favor ingrese en formato DD/MM/AAAA\n";
        }
    } while (fechaNacimiento.empty() || !Validaciones::validarFecha(fechaNacimiento));
    
    cout << "Comentarios sobre salud: ";
    getline(cin, comentarios);

    Paciente nuevo(nombre, dui, genero, fechaNacimiento, comentarios);

    if (servicio.agregarPaciente(nuevo)) {
        cout << "\nPaciente agregado exitosamente!" << endl;
    } else {
        cout << "\nError: Ya existe un paciente con ese DUI." << endl;
    }
}

void PacienteMenu::editarPaciente() {
    cout << "\n--- EDITAR PACIENTE ---" << endl;

    string duiOriginal;
    Paciente actual;

    try {

        while(actual.getDui().empty()){
            cout << "Ingrese el DUI del paciente a editar: ";
            getline(cin, duiOriginal);
            actual = servicio.buscarPorDui(duiOriginal);

            if(!actual.getDui().empty()){
                break;
            }
        }

        mostrarPaciente(actual);

        string nombre, genero, fechaNacimiento, comentarios;

        cout << "\nNuevo nombre (dejar vacío para no cambiar): ";
        getline(cin, nombre);
        if (!nombre.empty()) actual.setNombre(nombre);

        cout << "\nNuevo genero M/F (dejar vacío para no cambiar): ";
        getline(cin, genero);

        if (!genero.empty()) 
        {
            string generoLower = genero;
            transform(generoLower.begin(), generoLower.end(), generoLower.begin(), ::tolower);

            while (generoLower != "m" && generoLower != "f") {
                cout << "Por favor ingrese 'M' o 'F' (o dejar vacío para no cambiar): ";
                getline(cin, genero);
                
                if (genero.empty()) {
                    break;
                }
                
                generoLower = genero;
                transform(generoLower.begin(), generoLower.end(), generoLower.begin(), ::tolower);
            }

            if (!genero.empty()) {
                actual.setGenero(generoLower);
            }
        }

        cout << "Nueva fecha de nacimiento (dejar vacío para no cambiar): ";
        getline(cin, fechaNacimiento);

        if (!fechaNacimiento.empty())
        {
            bool esFechaValida = Validaciones::validarFecha(fechaNacimiento);
            
            while (!esFechaValida) {
                cout << "Por favor ingrese una fecha valida" << endl;
                cout << "Fecha de nacimiento (DD/MM/AAAA) (o dejar vacío para no cambiar): ";
                getline(cin, fechaNacimiento);
                
                if (fechaNacimiento.empty()) {
                    break;
                }
                
                esFechaValida = Validaciones::validarFecha(fechaNacimiento);
            }
            
            if (!fechaNacimiento.empty()) {
                actual.setFechaNacimiento(fechaNacimiento);
            }
        }

        cout << "Nuevos comentarios sobre salud (dejar vacío para no cambiar): ";
        getline(cin, comentarios);
        if (!comentarios.empty()) actual.setComentariosSalud(comentarios);

        if (servicio.editarPaciente(duiOriginal, actual)) {
            cout << "\nPaciente actualizado exitosamente!" << endl;
        } else {
            cout << "\nError al actualizar el paciente." << endl;
        }
    } catch (const exception& e) {
        cout << "\nError: " << e.what() << endl;
    }
}

void PacienteMenu::buscarPaciente() {
    cout << "\n--- BUSCAR PACIENTE ---" << endl;

    string dui;
    cout << "Ingrese el DUI del paciente a buscar: ";
    getline(cin, dui);

    try {
        Paciente encontrado = servicio.buscarPorDui(dui);
        cout << "\n=== PACIENTE ENCONTRADO ===" << endl;
        mostrarPaciente(encontrado);
    } catch (const exception& e) {
        cout << "\nError: " << e.what() << endl;
    }
}

void PacienteMenu::listarPacientes() {
    cout << "\n--- LISTADO DE PACIENTES ---" << endl;

    try {
        vector<Paciente> pacientes = servicio.obtenerTodosLosPacientes();
        
        if (pacientes.empty()) {
            cout << "No hay pacientes registrados." << endl;
            return;
        }

        cout << left << setw(30) << "NOMBRE" << setw(15) << "DUI" << setw(15) << "GENERO" 
             << setw(15) << "FECHA NAC." << setw(15) << "EDAD"  << "COMENTARIOS" << endl;
        cout << string(100, '-') << endl;

        for (const auto& paciente : pacientes) {
            cout << left << setw(30) << paciente.getNombre().substr(0, 27) + "..."
                 << setw(15) << paciente.getDui()
                 << setw(15) << (paciente.getGenero() == "m" ? "Masculino" : "Femenino")
                 << setw(15) << paciente.getFechaNacimiento()
                 << setw(15) << paciente.getEdad()
                 << paciente.getComentariosSalud().substr(0, 20) + "..." << endl;
        }
    } catch (const exception& e) {
        cout << "\nError: " << e.what() << endl;
    }
}

void PacienteMenu::mostrarPaciente(const Paciente& paciente) {
    cout << left << setw(15) << "Nombre:" << paciente.getNombre() << endl;
    cout << left << setw(15) << "DUI:" << paciente.getDui() << endl;
    cout << left << setw(15) << "Género:" << (paciente.getGenero() == "m" ? "Masculino" : "Femenino") << endl;
    cout << left << setw(15) << "Fecha Nac.:" << paciente.getFechaNacimiento() << endl;
    cout << left << setw(15) << "Edad:" << paciente.getEdad() << endl;
    cout << left << setw(15) << "Comentarios:" << paciente.getComentariosSalud() << endl;
}
