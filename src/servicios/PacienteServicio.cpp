#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "PacienteServicio.h"

using namespace std;

PacienteServicio::PacienteServicio(const string& nombreArchivo) : nombreArchivo(nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::binary | ios::app);
    archivo.close();
}


bool PacienteServicio::agregarPaciente(const Paciente& paciente) {

    // verificar si el paciente ya existe, solo si hay datos en el archivo
    if (archivoTieneDatos()) {
        if (buscarPosicionPorDui(paciente.getDui()) != -1) {
            return false; // Paciente ya existe
        }
    }

    // abrir archivo en modo append binario
    std::fstream archivo(nombreArchivo, std::ios::binary | std::ios::out | std::ios::app);

    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el archivo para agregar paciente");
    }

    // escribir el paciente
    try {
        serializarPaciente(archivo, paciente);
    } catch (const std::runtime_error& e) {
        archivo.close();
        throw std::runtime_error("Error al serializar el paciente: " + std::string(e.what()));
    }

    archivo.close();
    return true;
}

bool PacienteServicio::editarPaciente(const string& dui, const Paciente& pacienteActualizado) {
    // abrir el archivo en modo lectura/escritura
    std::fstream archivo(nombreArchivo, std::ios::binary | std::ios::in | std::ios::out);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para lectura/escritura");
    }

    // buscar la posicion del paciente por DUI
    long posicion = buscarPosicionPorDui(dui);
    if (posicion == -1) {
        archivo.close();
        return false;
    }

    // verificar que el DUI del paciente actualizado coincida
    if (pacienteActualizado.getDui() != dui) {
        archivo.close();
        throw std::runtime_error("El DUI del paciente actualizado no coincide con el DUI proporcionado");
    }

    // posicionarse en el lugar correcto para escribir
    archivo.seekp(posicion, std::ios::beg);

    // escribir el paciente actualizado
    try {
        serializarPaciente(archivo, pacienteActualizado);
    } catch (const std::runtime_error& e) {
        archivo.close();
        throw std::runtime_error("Error al serializar el paciente: " + std::string(e.what()));
    }

    archivo.close();
    return true;
}

long PacienteServicio::buscarPosicionPorDui(const string& dui) {

    std::ifstream archivo(nombreArchivo, std::ios::binary);

    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para buscar paciente");
    }

    long posicion = 0;
    while (archivo) {
        try {
            posicion = archivo.tellg();
            Paciente paciente = deserializarPaciente(archivo);
            if (paciente.getDui() == dui) {
                return posicion;
            }
        } catch (const std::runtime_error& e) {
            if (!archivo.eof()) {
                std::cerr << "Error al leer datos: " << e.what() << std::endl;
            }
            break;
        }
    }

    archivo.close();
    return -1;
}

Paciente PacienteServicio::buscarPorDui(const string& duiPaciente) {

    std::ifstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el archivo para buscar paciente");
    }

    Paciente paciente;
    while (archivo) {
        try {
            Paciente paciente = deserializarPaciente(archivo);
            if (paciente.getDui() == duiPaciente) {
                return paciente;
            }
        } catch (const std::exception& e) {
            if (!archivo.eof()) {
                cout << "Error al leer datos: " << e.what() << endl;
            }
            break;
        }
    }

    archivo.close();
    return paciente;
}

void PacienteServicio::escribirString(fstream& archivo, string& texto) {

    size_t tam = texto.size();
    archivo.write(reinterpret_cast<char*>(&tam), sizeof(tam));
    archivo.write(texto.c_str(), tam);
}

std::string PacienteServicio::leerString(std::ifstream& archivo) {

    size_t tam;

    if (!archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam))) {
        if (archivo.eof()) {
            throw std::runtime_error("Fin de archivo alcanzado al intentar leer el tamaño del string");
        } else {
            throw std::runtime_error("Error al leer el tamaño del string");
        }
    }
    
    if (tam > 10000) {
        throw std::runtime_error("Tamaño de string inválido (demasiado grande)");
    }
    
    std::vector<char> buffer(tam + 1);
    if (!archivo.read(buffer.data(), tam)) {
        throw std::runtime_error("Error al leer el contenido del string");
    }
    buffer[tam] = '\0';
    
    return std::string(buffer.data());
}

vector<Paciente> PacienteServicio::obtenerTodosLosPacientes() {

    std::ifstream archivo(nombreArchivo, std::ios::binary);

    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el archivo para leer pacientes");
    }
    
    vector<Paciente> pacientes;
    while (archivo) {
        try {
            pacientes.push_back(deserializarPaciente(archivo));
        } catch (const std::exception& e) {
            if (!archivo.eof()) {
                cout << "Error al leer datos: " << e.what() << endl;
            }
            break;
        }
    }
    archivo.close();
    return pacientes;
}

bool PacienteServicio::serializarPaciente(std::fstream& archivo, const Paciente& paciente) {

    // obtener propiedades del paciente
    string nombrePaciente = paciente.getNombre();
    string duiPaciente = paciente.getDui();
    string generoPaciente = paciente.getGenero();
    string fechaNacPaciente = paciente.getFechaNacimiento();
    string comentSaludPaciente = paciente.getComentariosSalud();

    // escribir en el archivo
    escribirString(archivo,nombrePaciente);
    escribirString(archivo,duiPaciente);
    escribirString(archivo, generoPaciente);
    escribirString(archivo,fechaNacPaciente);
    escribirString(archivo,comentSaludPaciente);
    
    return true;
}

Paciente PacienteServicio::deserializarPaciente(ifstream& archivo) {

    string nombre = leerString(archivo);
    string dui = leerString(archivo);
    string genero = leerString(archivo);
    string fechaNacimiento = leerString(archivo);
    string comentarios = leerString(archivo);
    
    return Paciente(nombre, dui, genero, fechaNacimiento, comentarios);
}

bool PacienteServicio::archivoTieneDatos() {
    
    std::ifstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo.is_open()) {
        return false;
    }

    archivo.seekg(0, std::ios::end);
    return archivo.tellg() > 0;
}