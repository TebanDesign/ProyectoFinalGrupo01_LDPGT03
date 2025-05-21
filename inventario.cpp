// Descripción: Implementación de funciones para gestión de medicamentos

#include "inventario.h"
#include "tratamiento.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

void agregarMedicamento() {
    Medicamento m;
    cout << "\n=== Agregar Medicamento ===\n";
    cout << "Nombre: ";
    getline(cin, m.nombre);
    cout << "Cantidad: ";
    cin >> m.cantidad;
    cout << "Precio: ";
    cin >> m.precio;
    cin.ignore();

    ofstream archivo("medicamentos.dat", ios::binary | ios::app);
    if (archivo.is_open()) {
        size_t lenNombre = m.nombre.size();
        archivo.write((char*)&lenNombre, sizeof(size_t));
        archivo.write(m.nombre.c_str(), lenNombre);
        archivo.write((char*)&m.cantidad, sizeof(int));
        archivo.write((char*)&m.precio, sizeof(float));
        archivo.close();
        cout << "Medicamento agregado exitosamente.\n";
    } else {
        cerr << "Error al abrir el archivo de inventario.\n";
    }
}

void mostrarInventario() {
    ifstream archivo("medicamentos.dat", ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo de inventario.\n";
        return;
    }

    cout << "\n=== Inventario de Medicamentos ===\n";
    while (archivo.peek() != EOF) {
        size_t lenNombre;
        archivo.read((char*)&lenNombre, sizeof(size_t));
        if (archivo.eof()) break;
        string nombre(lenNombre, ' ');
        archivo.read(&nombre[0], lenNombre);

        int cantidad;
        float precio;
        archivo.read((char*)&cantidad, sizeof(int));
        archivo.read((char*)&precio, sizeof(float));

        cout << "Nombre: " << nombre
             << "\nCantidad: " << cantidad
             << "\nPrecio: $" << precio
             << "\n----------------------\n";
    }
    archivo.close();
}

void editarMedicamento() {
    cout << "\nFuncionalidad de edición de medicamentos pendiente de implementación.\n";
}

bool buscarMedicamento(const string& nombreBuscado, Medicamento& encontrado) {
    ifstream archivo("medicamentos.dat", ios::binary);
    if (!archivo.is_open()) return false;

    while (archivo.peek() != EOF) {
        size_t lenNombre;
        archivo.read((char*)&lenNombre, sizeof(size_t));
        if (archivo.eof()) break;
        string nombre(lenNombre, ' ');
        archivo.read(&nombre[0], lenNombre);

        archivo.read((char*)&encontrado.cantidad, sizeof(int));
        archivo.read((char*)&encontrado.precio, sizeof(float));

        if (nombre == nombreBuscado) {
            encontrado.nombre = nombre;
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

bool descontarMedicamento(const string& nombreBuscado, int cantidadSolicitada) {
    ifstream archivoLectura("medicamentos.dat", ios::binary);
    ofstream archivoTemporal("temp.dat", ios::binary);
    bool encontrado = false;

    if (!archivoLectura.is_open() || !archivoTemporal.is_open()) return false;

    while (archivoLectura.peek() != EOF) {
        size_t lenNombre;
        archivoLectura.read((char*)&lenNombre, sizeof(size_t));
        if (archivoLectura.eof()) break;
        string nombre(lenNombre, ' ');
        archivoLectura.read(&nombre[0], lenNombre);

        int cantidad;
        float precio;
        archivoLectura.read((char*)&cantidad, sizeof(int));
        archivoLectura.read((char*)&precio, sizeof(float));

        if (nombre == nombreBuscado) {
            encontrado = true;
            if (cantidad >= cantidadSolicitada) {
                cantidad -= cantidadSolicitada;
            } else {
                cout << "\nAdvertencia: no hay suficiente stock de " << nombre << ".\n";
            }
        }

        archivoTemporal.write((char*)&lenNombre, sizeof(size_t));
        archivoTemporal.write(nombre.c_str(), lenNombre);
        archivoTemporal.write((char*)&cantidad, sizeof(int));
        archivoTemporal.write((char*)&precio, sizeof(float));
    }

    archivoLectura.close();
    archivoTemporal.close();

    remove("medicamentos.dat");
    rename("temp.dat", "medicamentos.dat");

    return encontrado;
}