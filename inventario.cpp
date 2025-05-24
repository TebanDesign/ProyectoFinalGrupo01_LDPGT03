// Descripción: Implementación de funciones para gestión de medicamentos

#include "inventario.h"
#include "tratamiento.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>


#include <cctype>
#include <algorithm>
#include <functional>

using namespace std;

// Tipo de callback para procesar un medicamento encontrado

using ProcesoMedicamento = function<void(string&, int&, float&, size_t)>;

bool procesarMedicamentoPorNombre(const string& nombreBuscado, ProcesoMedicamento accion) {
    fstream archivo("medicamentos.dat", ios::in | ios::out | ios::binary);
    if (!archivo.is_open()) return false;

    bool encontrado = false;
    streampos inicio;

    while (archivo.peek() != EOF) {
        inicio = archivo.tellg();
        size_t lenNombre;
        archivo.read((char*)&lenNombre, sizeof(size_t));
        if (archivo.eof()) break;

        string nombre(lenNombre, ' ');
        archivo.read(&nombre[0], lenNombre);

        int cantidad;
        float precio;
        archivo.read((char*)&cantidad, sizeof(int));
        archivo.read((char*)&precio, sizeof(float));

        if (nombre == nombreBuscado) {
            encontrado = true;
            // Posición del comienzo del registro
            archivo.seekp(inicio);
            accion(nombre, cantidad, precio, lenNombre);
            break;
        }
    }

    archivo.close();
    return encontrado;
}

// Versión EXTENDIDA faltante (la que usa fstream)
bool procesarMedicamentoPorNombre(const string& nombreBuscado, 
                                 function<void(fstream&, streampos, 
                                 string&, int&, float&, size_t)> accion) {
    fstream archivo("medicamentos.dat", ios::in | ios::out | ios::binary);
    if (!archivo.is_open()) return false;

    bool encontrado = false;

    while (archivo.peek() != EOF) {
        streampos pos = archivo.tellg();
        
        size_t lenNombre;
        archivo.read((char*)&lenNombre, sizeof(size_t));
        string nombre(lenNombre, ' ');
        archivo.read(&nombre[0], lenNombre);
        
        int cantidad;
        float precio;
        archivo.read((char*)&cantidad, sizeof(int));
        archivo.read((char*)&precio, sizeof(float));
        
        if (nombre == nombreBuscado) {
            encontrado = true;
            accion(archivo, pos, nombre, cantidad, precio, lenNombre);
            break;
        }
    }
    
    archivo.close();
    return encontrado;
}

bool validarNombre(const string& nombre) {
    return !nombre.empty() && all_of(nombre.begin(), nombre.end(), [](char c) {
        return isalnum(c) || isspace(c) || c == '-' || c == '_';
    });
}

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


/*

Este es el codigo original de agregarMedicamento, pero no se usa en el programa principal.
// Esta función agrega un nuevo medicamento al inventario

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
*/

void agregarMedicamento() {
    Medicamento m;
    cout << "\n=== Agregar Medicamento ===\n";

    do {
        cout << "Nombre: ";
        getline(cin, m.nombre);
        if (!validarNombre(m.nombre)) {
            cout << "Nombre inválido. Use solo letras, números, espacios, guiones o guiones bajos.\n";
        }
    } while (!validarNombre(m.nombre));

    cout << "Cantidad: ";
    while (!(cin >> m.cantidad) || m.cantidad < 0) {
        cout << "Cantidad inválida. Ingrese un número entero no negativo: ";
        limpiarBuffer();
    }

    cout << "Precio: ";
    while (!(cin >> m.precio) || m.precio < 0.0f) {
        cout << "Precio inválido. Ingrese un número decimal no negativo: ";
        limpiarBuffer();
    }
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

/* Esta es la funcionalidad de mostrarInventario, pero no se usa en el programa principal.
// Esta función muestra el inventario de medicamentos almacenados en el archivo binario

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

*/

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


/* Esta es la funcionalidad de editarMedicamento, pero no se usa en el programa principal.


void editarMedicamento() {
    cout << "\nFuncionalidad de edición de medicamentos pendiente de implementación.\n";
}

*/
void editarMedicamento() {
    string nombre;
    cout << "\n=== Editar Medicamento ===\nNombre del medicamento a editar: ";
    getline(cin, nombre);

    bool resultado = procesarMedicamentoPorNombre(nombre, [&](fstream& archivo, streampos pos, string& nombre, int& cantidad, float& precio, size_t lenNombre) {
        cout << "\nMedicamento encontrado.\n";
        cout << "Nombre actual: " << nombre << "\nCantidad actual: " << cantidad << "\nPrecio actual: $" << precio << endl;

        cout << "\n--- Ingrese los nuevos valores ---\n";
        cout << "Nuevo nombre: ";
        getline(cin, nombre);
        cout << "Nueva cantidad: ";
        cin >> cantidad;
        cout << "Nuevo precio: ";
        cin >> precio;
        cin.ignore();

        // Actualiza el registro
        lenNombre = nombre.size();
        archivo.seekp(pos);
        archivo.write((char*)&lenNombre, sizeof(size_t));
        archivo.write(nombre.c_str(), lenNombre);
        archivo.write((char*)&cantidad, sizeof(int));
        archivo.write((char*)&precio, sizeof(float));
        cout << "\nMedicamento actualizado exitosamente.\n";
    });

    if (!resultado) {
        cout << "No se encontró el medicamento.\n";
    }
}



/* Esta es la funcionalidad de buscarMedicamento, pero no se usa en el programa principal.
// Esta función busca un medicamento por nombre y devuelve su información

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

*/

bool buscarMedicamento(const string& nombreBuscado, Medicamento& encontrado) {
    return procesarMedicamentoPorNombre(nombreBuscado, [&](string& nombre, int& cantidad, float& precio, size_t) {
        encontrado.nombre = nombre;
        encontrado.cantidad = cantidad;
        encontrado.precio = precio;
    });
}

/* Esta es la funcionalidad de descontarMedicamento, pero no se usa en el programa principal.
// Esta función descuenta una cantidad de un medicamento en el inventario


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
*/

bool descontarMedicamento(const string& nombreBuscado, int cantidadSolicitada) {
    return procesarMedicamentoPorNombre(nombreBuscado, [&](fstream& archivo, streampos pos, string& nombre, int& cantidad, float& precio, size_t lenNombre) {
        if (cantidad < cantidadSolicitada) {
            cout << "\nAdvertencia: no hay suficiente stock de " << nombre << ".\n";
            return;
        }

        cantidad -= cantidadSolicitada;

        // Reescribir los datos actualizados
        archivo.seekp(pos);
        archivo.write((char*)&lenNombre, sizeof(size_t));
        archivo.write(nombre.c_str(), lenNombre);
        archivo.write((char*)&cantidad, sizeof(int));
        archivo.write((char*)&precio, sizeof(float));
    });
}

// Esta función agrega una cantidad a un medicamento en el inventario
// Se usa para aumentar el stock de un medicamento, no pienso que sea redundante con la función editarMedicamento() porque está es para evitar que el usuario tenga que editar el medicamento completo
// y solo le interesa agregar stock, mientras que la de edición es para cambiar el nombre, precio y cantidad de un medicamento
bool agregarStock(const string& nombreBuscado, int cantidadAgregar) {
    return procesarMedicamentoPorNombre(nombreBuscado, [&](fstream& archivo, streampos pos, string& nombre, int& cantidad, float& precio, size_t lenNombre) {
        cantidad += cantidadAgregar;

        archivo.seekp(pos);
        archivo.write((char*)&lenNombre, sizeof(size_t));
        archivo.write(nombre.c_str(), lenNombre);
        archivo.write((char*)&cantidad, sizeof(int));
        archivo.write((char*)&precio, sizeof(float));

        cout << "\nSe agregó exitosamente " << cantidadAgregar << " unidades a '" << nombre << "'.\n";
    });
}
