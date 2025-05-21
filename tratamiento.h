// Descripción: Declaración de funciones y estructura para gestión de tratamientos

#ifndef TRATAMIENTO_H
#define TRATAMIENTO_H

#include <string>

struct Tratamiento {
    std::string duiPaciente;    // Identificador del paciente
    std::string medicamento;    // Nombre del medicamento
    std::string dosis;          // Ej: "2 tabletas"
    std::string periodo;        // Ej: "7 días"
};

void registrarTratamiento();
void mostrarTratamientos();
void editarTratamiento();

#endif