#ifndef PACIENTE_SERVICE_H
#define PACIENTE_SERVICE_H

#include "Paciente.h"
#include <vector>
#include <string>
#include <fstream>

class PacienteServicio {
private:
    std::string nombreArchivo;  //nombre del archivo binario
    std::string rutaArchivo; // para almacenar la ruta completa del archivo a utilizar

    long buscarPosicionPorDui(const std::string& dui);
    bool serializarPaciente(std::fstream& archivo, const Paciente& paciente);
    Paciente deserializarPaciente(std::ifstream& archivo);
    std::string leerString(std::ifstream& archivo);
    void escribirString(std::fstream& archivo, std::string& texto);


public:
    // constructor que recibe el nombre del archivo a utilizar
    PacienteServicio(const std::string& nombreArchivo);
    
    bool agregarPaciente(const Paciente& paciente);
    bool editarPaciente(const std::string& duiOriginal, const Paciente& pacienteActualizado);
    Paciente buscarPorDui(const std::string& duiPaciente);
    std::vector<Paciente> obtenerTodosLosPacientes();
    bool archivoTieneDatos(); 
};

#endif
