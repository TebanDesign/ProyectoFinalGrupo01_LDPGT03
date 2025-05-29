// Descripción: Implementación de funciones para gestionar pacientes con DUI como ID

#include "paciente.h"
#include "encriptador.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

bool existeId(const string& dui) {
    ifstream archivo("pacientes.dat", ios::binary);
    if (!archivo.is_open()) return false;

    while (archivo.peek() != EOF) {
        size_t lenDui;
        archivo.read((char*)&lenDui, sizeof(size_t));
        if (archivo.eof()) break;
        string currentDui(lenDui, ' ');
        archivo.read(&currentDui[0], lenDui);

        size_t lenNombre, lenNacimiento, lenComentarios;
        archivo.read((char*)&lenNombre, sizeof(size_t));
        archivo.ignore(lenNombre);
        archivo.read((char*)&lenNacimiento, sizeof(size_t));
        archivo.ignore(lenNacimiento);
        archivo.read((char*)&lenComentarios, sizeof(size_t));
        archivo.ignore(lenComentarios);

        if (currentDui == dui) {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

void registrarPaciente() {
    Paciente p;
    cout << "\n=== Registro de Paciente ===\n";
    do {
        cout << "DUI: ";
        getline(cin, p.dui);
        if (existeId(p.dui)) {
            cout << "Ya existe un paciente con ese DUI. Intente otro.\n";
        }
    } while (existeId(p.dui));

    cout << "Nombre completo: ";
    getline(cin, p.nombre);
    cout << "Fecha de nacimiento (dd/mm/aaaa): ";
    getline(cin, p.fechaNacimiento);
    cout << "Comentarios de salud: ";
    getline(cin, p.comentarios);

    ofstream archivo("pacientes.dat", ios::binary | ios::app);
    if (archivo.is_open()) {
        string comentariosCifrado = encriptar(p.comentarios);

        size_t lenDui = p.dui.size();
        size_t lenNombre = p.nombre.size();
        size_t lenNacimiento = p.fechaNacimiento.size();
        size_t lenComentarios = comentariosCifrado.size();

        archivo.write((char*)&lenDui, sizeof(size_t));
        archivo.write(p.dui.c_str(), lenDui);
        archivo.write((char*)&lenNombre, sizeof(size_t));
        archivo.write(p.nombre.c_str(), lenNombre);
        archivo.write((char*)&lenNacimiento, sizeof(size_t));
        archivo.write(p.fechaNacimiento.c_str(), lenNacimiento);
        archivo.write((char*)&lenComentarios, sizeof(size_t));
        archivo.write(comentariosCifrado.c_str(), lenComentarios);

        archivo.close();
        cout << "Paciente registrado exitosamente.\n";
    } else {
        cerr << "Error al guardar paciente en archivo binario.\n";
    }
}

void mostrarPacientes() {
    ifstream archivo("pacientes.dat", ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo de pacientes.\n";
        return;
    }

    cout << "\n=== Lista de Pacientes ===\n";
    while (archivo.peek() != EOF) {
        size_t lenDui, lenNombre, lenNacimiento, lenComentarios;
        archivo.read((char*)&lenDui, sizeof(size_t));
        if (archivo.eof()) break;
        string dui(lenDui, ' ');
        archivo.read(&dui[0], lenDui);

        archivo.read((char*)&lenNombre, sizeof(size_t));
        string nombre(lenNombre, ' ');
        archivo.read(&nombre[0], lenNombre);

        archivo.read((char*)&lenNacimiento, sizeof(size_t));
        string nacimiento(lenNacimiento, ' ');
        archivo.read(&nacimiento[0], lenNacimiento);

        archivo.read((char*)&lenComentarios, sizeof(size_t));
        string comentarios(lenComentarios, ' ');
        archivo.read(&comentarios[0], lenComentarios);

        cout << "DUI: " << dui
             << "\nNombre: " << nombre
             << "\nFecha de Nacimiento: " << nacimiento
             << "\nComentarios de Salud: " << desencriptar(comentarios)
             << "\n----------------------\n";
    }
    archivo.close();
}