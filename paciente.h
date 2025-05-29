// Descripción: Declaración de funciones para gestionar pacientes

#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>

struct Paciente {
    std::string dui;
    std::string nombre;
    std::string fechaNacimiento;
    std::string comentarios;
};

bool existeId(const std::string& dui);
void registrarPaciente();
void mostrarPacientes();

#endif